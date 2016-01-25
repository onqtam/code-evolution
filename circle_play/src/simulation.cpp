#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "types.h"
#include "list.h"
#include "util.h"
#include "config.h"

extern double g_AngleStep;
extern Vector2D g_A, g_B;
extern unsigned int g_N, g_K;
extern List<Circle> g_Circles;

extern List<IntersectionList> g_Intersections;
extern List<IntersectionList> g_Results;

bool FindRangeUnion(List<AngleRange>& rangeUnion);
bool BinarySearch(const IntersectionList& First,
				  const IntersectionList& Second,
				  const Vector2D& ProjectionFirst,
				  const Vector2D& ProjectionSecond,
				  const Ray& RayFirst,
				  const Ray& RaySecond,
				  IntersectionList& Result,
				  unsigned int Depth);

bool Raycast(const Ray& ray, IntersectionInfo& closestInfo)
{
	closestInfo.distance = INF;
	closestInfo.circle = NULL;
	
	//finds the nearest circle with which the ray collides
	for (List<Circle>::iterator it = g_Circles.begin(); it != g_Circles.end(); ++it)
	{
		IntersectionInfo info;
		if(it->intersect(ray, info))
		{
			if (info.distance < closestInfo.distance)
			{
				closestInfo = info;
			}
		}
	}
	
	return closestInfo.circle != NULL;
}

Vector2D Raytrace(const Ray& ray, IntersectionList& intersections)
{
	IntersectionInfo closestInfo;
	
	if(Raycast(ray, closestInfo) && ray.depth < g_K)
	{
		Vector2D n = Faceforward(closestInfo.norm, ray.dir);
		Vector2D r = Reflect(ray.dir, n);
		
		//gather info for this reflection
		intersections.infos[intersections.numReflections++] = closestInfo;
		
		Ray newRay;
		newRay.dir = r;
		//offset the new ray's starting point a bit so that it does not collide with the same circle again
		newRay.start = closestInfo.ip + n * 1e-6;
		newRay.depth = ray.depth + 1;
		
		//accumulate tangens for adaptive sampling where rays reflect with a high angle.
		//we dont need to normalize the normal and the ray because the normal
		//gets normalized in the intersect method of the geometry (currently circles)
		//and the ray direction is generated normalized and reflected without much error
		intersections.accumulatedTangens += Abs(Cross(newRay.dir, n) / Dot(newRay.dir, n));
		
		//raytrace recursively
		return Raytrace(newRay, intersections);
	}
	
	//return the direction of the ray after a few reflections (maximum K) or none...
	return ray.dir;
}

void RaytraceAll()
{
	g_Intersections.clear();
	g_Results.clear();
	
	//this constructs a union of angle intervals
	//all sampling is done with rays with starting
	//angle from that union (initial dir is 
	//constructed with sin and cos of that angle)
	List<AngleRange> rangeUnion;
	if(!FindRangeUnion(rangeUnion))
	{
		return;
	}
	
	//for each separate interval from the union
	for(List<AngleRange>::iterator it = rangeUnion.begin(); it != rangeUnion.end(); ++it)
	{
#if USE_BINARY_SEARCH
		//vars for the last raytrace in the current interval of the union (for the binary search)
		Ray rayLast;
		Vector2D projectionPointLast;
		IntersectionList last(g_K);
		IntersectionInfo closestInfoLast;
#endif // USE_BINARY_SEARCH
		
		double tangCoef = 1.0;
		
		//sampling the current interval with a step multiplied by a coefficien
		//this coefficient is 1 / (sum of all tangs from last ray's intersections)
		//the point is to sample more dense where rays hit surfaces with bigger angles
		//(each intersection accumulates this value in IntersectionList)
		for(double currentAngle = it->angles[0] + 1e-8;
			currentAngle <= it->angles[1] - 1e-8;
			currentAngle += g_AngleStep / tangCoef)
		{
			//initialization of vars regarding the current ray
			IntersectionList curr(g_K, currentAngle);
			IntersectionInfo closestInfoCurr;
			bool isCurrHit = false;
			
			//make a random color for displaying the ray and all its reflections
			curr.color.Randomize();
			
			//initial direction of the ray
			Vector2D initialDir = Vector2D(
				cos(currentAngle),
				sin(currentAngle));
			
			//trace the current ray
			curr.lastDir = Raytrace(Ray(g_A, initialDir), curr);
			
			//clamp the accumulated adaptivity coef in some reasonable range
			tangCoef = CLAMP(curr.accumulatedTangens, 1.0, ADAPTIVITY_MAX_COEF);
			
			Ray rayCurr(
				curr.infos[curr.numReflections - 1].ip + curr.infos[curr.numReflections - 1].norm * 1e-6, 
				curr.lastDir);
			Vector2D projectionPointCurr;
#if !USE_BINARY_SEARCH
			//if point B's projection is on the ray after K reflections
			if(curr.numReflections == g_K && GetPointProjectionOntoRay(rayCurr, g_B, projectionPointCurr))
			{
				//if the distance to the ray is less than some threshold
				if((g_B - projectionPointCurr).LengthSqr() < DISTANCE_EPSILON * DISTANCE_EPSILON)
				{
					//see if the ray after K reflections hits something
					//and see if the projection of point B is closer to
					//that hit point (if yes ===> we have found a path)
					//if no hitpoiny ==> yes ===> we have found a path
					if(Raycast(rayCurr, closestInfoCurr))
					{
						if((closestInfoCurr.distance * closestInfoCurr.distance) > (projectionPointCurr - rayCurr.start).LengthSqr())
						{
							isCurrHit = true;
						}
					}
					else
					{
						isCurrHit = true;
					}
					
					if(isCurrHit)
					{
						//filter results - if there is a previous result
						//and it has K times reflected from the same
						//geometry the current one has, dont add the current one
						if(g_Results.size() > 0 && curr.HasHitSameGeometry(g_Results.back()))
						{
							isCurrHit = false;
						}
						
						if(isCurrHit)
						{
							g_Results.push_back(curr);
						}
					}
				}
			}
#else
			//see if point B lies between the reflections of the current and last ray
			//both rays need to be K times reflected
			//both rays have gone through the same geometry
			//check if the projections of B onto both rays is on them and not outside (before their start)
			//check if the point is inside the area between the 2 rays (see IsPointBetweenRays for ASCII art)
			//check if there is some geometry along the way before the point of projection (on both rays)
			//if there is, discard (aka get false ===> don't do binary search)
			//this will eliminate the problem when the point is on the other side of the current last geometry
			bool shouldUseBinarySearch =
				curr.numReflections == g_K &&
				last.numReflections == g_K &&
				curr.HasHitSameGeometry(last) &&
				GetPointProjectionOntoRay(rayCurr, g_B, projectionPointCurr) &&
				GetPointProjectionOntoRay(rayLast, g_B, projectionPointLast) &&
				IsPointBetweenRays(g_B, projectionPointCurr, projectionPointLast) &&
				!(Raycast(rayCurr, closestInfoCurr) && (closestInfoCurr.distance * closestInfoCurr.distance) < (projectionPointCurr - rayCurr.start).LengthSqr()) &&
				!(Raycast(rayLast, closestInfoLast) && (closestInfoLast.distance * closestInfoLast.distance) < (projectionPointLast - rayLast.start).LengthSqr());
			
			if(shouldUseBinarySearch)
			{
				IntersectionList result(g_K);
				if(BinarySearch(curr, last, projectionPointCurr, projectionPointLast, rayCurr, rayLast, result, 0))
				{
					g_Results.push_back(result);
				}
			}
			
			//save the current as last for next iteration
			rayLast = rayCurr;
			projectionPointLast = projectionPointCurr;
			last = curr;
#endif // USE_BINARY_SEARCH
#if COLLECT_ALL_RAYS
			g_Intersections.push_back(curr);
#endif // COLLECT_ALL_RAYS
		}
	}
	
	printf("Paths found: %d\n", g_Results.size());
}

bool BinarySearch(const IntersectionList& First,
				  const IntersectionList& Second,
				  const Vector2D& ProjectionFirst,
				  const Vector2D& ProjectionSecond,
				  const Ray& RayFirst,
				  const Ray& RaySecond,
				  IntersectionList& Result,
				  unsigned int Depth)
{
	if(Depth > MAX_BINARY_SEARCH_DEPTH)
	{
		return false;
	}
	
	//we calculate the average angle
	//trace a ray with direction calculated from that angle
	double midAngle = (First.startingAngle + Second.startingAngle) / 2;
	IntersectionList mid(g_K, midAngle);
	Vector2D dir = Vector2D(
		cos(midAngle),
		sin(midAngle));
	
	mid.lastDir = Raytrace(Ray(g_A, dir), mid);
	
	Ray rayMid(
		mid.infos[mid.numReflections - 1].ip + mid.infos[mid.numReflections - 1].norm * 1e-6, 
		mid.lastDir);
	Vector2D projectionPointMid;
	IntersectionInfo closestInfoMid;
	
	//if mid ray has been reflected K times (actually it would be impossible not to be, but just to be sure...)
	//if mid ray has hit the same geometry its bounding rays have (just for safety too...)
	//check if the projection of B onto the mid ray is on it and not outside (before it's start)
	//check if there is some geometry along the way before the point of projection (on both rays)
	//if there is, discard (aka get false ===> don't continue binary search)
	if( mid.numReflections == g_K &&
		mid.HasHitSameGeometry(First) && //doesn't matter with which (first or second) we check - should be the same
		GetPointProjectionOntoRay(rayMid, g_B, projectionPointMid) &&
		!(Raycast(rayMid, closestInfoMid) && (closestInfoMid.distance * closestInfoMid.distance) < (projectionPointMid - rayMid.start).LengthSqr()))
	{
		//if the distance to the ray is less than some threshold
		if((g_B - projectionPointMid).LengthSqr() < DISTANCE_EPSILON * DISTANCE_EPSILON)
		{
			//filter results - if there is a previous result
			//and it has K times reflected from the same
			//geometry the current one has, dont add the current one
			bool hit = true;
			if(g_Results.size() > 0 && mid.HasHitSameGeometry(g_Results.back()))
			{
				hit = false;
			}
			
			if(hit)
			{
				mid.color.Randomize();
				Result = mid;
				return true;
			}
		}
		else
		{
			//if mid ray not close enough to point, continue binary search in the appropriate range (one out of two possible)
			if(IsPointBetweenRays(g_B, ProjectionFirst, projectionPointMid))
			{
				return BinarySearch(First, mid, ProjectionFirst, ProjectionFirst, RayFirst, rayMid, Result, Depth + 1);
			}
			else //if(IsPointBetweenRays(g_B, RaySecond, rayMid, ProjectionSecond, projectionPointMid))
			{
				return BinarySearch(Second, mid, ProjectionSecond, ProjectionSecond, RaySecond, rayMid, Result, Depth + 1);
			}
		}
	}

	return false;
}

bool FindRangeUnion(List<AngleRange>& rangeUnion)
{
	size_t currentRange = 0;
	size_t numRanges = g_Circles.size();
	
	if(numRanges == 0)
	{
		return false;
	}
	
	AngleRange* ranges = new AngleRange[numRanges];
	
	//we sometimes need to split an angular interval because it spans
	//through first to fourth quadrant (> PI), and instead it should span
	//through fourth to first quadrant (< PI)
	//(counter clockwise ...)
	List<AngleRange> rangesFromSplit2ndPart;
	
	for(List<Circle>::iterator it = g_Circles.begin(); it != g_Circles.end(); ++it, ++currentRange)
	{
		//construct a circle with a center the midpoint
		//between the starting point A and the current circle's center
		//(used to find the tangents from A to the current circle,
		// which in their turn are used to define an angular range
		// of visibility from A to the current circle)
		Circle& B = (*it);
		Vector2D midPoint((g_A + B.o) / 2.0f);
		Circle A(midPoint, (midPoint - g_A).Length());
		
		if(B.isInside(g_A) || B.isInside(g_B))
		{
			printf("Warning! Point A or B in circle! Aborting...\n");
			return false;
		}
		
		//find the intersection points of the circles
		Vector2D intersectionPoint1;
		Vector2D intersectionPoint2;
		GetIntersectionPointsBetweenCircles(A, B, intersectionPoint1, intersectionPoint2);
		
		//calculate angle boundry for casting rays from A to this circle
		double angle1 = Get2DAngleOfLineSegment(g_A, intersectionPoint1);
		double angle2 = Get2DAngleOfLineSegment(g_A, intersectionPoint2);
		
		double min = MIN(angle1, angle2);
		double max = MAX(angle1, angle2);
		
		//if angle interval spans from first to fourth quadrant - split it in 2 intervals.
		//this would mean that we have chosen the wrong angle for begining of the interval
		//and the wrong one for the end of the interval
		//(if one of these is wrong, both are wrong actually :D)
		//it is guaranteed that if point A is outside the current circle, the angle between
		//the two tangets is <= PI
		if(max - min > PI)
		{
			ranges[currentRange].angles[0] = max;
			ranges[currentRange].angles[1] = 2 * PI;
			
			rangesFromSplit2ndPart.push_back(AngleRange(0.0, min));
		}
		else
		{
			//add the anglular range for the current circle in a container for later sorting and union
			ranges[currentRange].angles[0] = min;
			ranges[currentRange].angles[1] = max;
		}
	}
	
	//enlarge the ranges array and append the second part of the results from the interval splits
	size_t appendSize = rangesFromSplit2ndPart.size();
	if(appendSize > 0)
	{
		AngleRange* rangesTemp = new AngleRange[numRanges + appendSize];
		memcpy(rangesTemp, ranges, numRanges * sizeof(AngleRange));
		
		size_t appendIndex = numRanges;
		for(List<AngleRange>::iterator it = rangesFromSplit2ndPart.begin();
			it != rangesFromSplit2ndPart.end();
			++it, ++appendIndex)
		{
			rangesTemp[appendIndex] = *it;
		}
		
		Swap(ranges, rangesTemp);
		delete [] rangesTemp;
		numRanges += appendSize;
	}
	
	//sort the ranges so we can line scan them and make a union
	Heapsort(ranges, numRanges);
	
	//for(int i = 0; i < numRanges; ++i)
	//	printf("%lf %lf\n", ranges[i].angles[0] * RAD_TO_DEG, ranges[i].angles[1] * RAD_TO_DEG);
	//printf("\n");
	
	//init the first range
	double start =	ranges[0].angles[0];
	double end =	ranges[0].angles[1];
	
	//make the union of the ranges with a linear sweep
	for(size_t i = 1; i < numRanges; ++i)
	{
		if(end < ranges[i].angles[0])
		{
			rangeUnion.push_back(AngleRange(start, end));
			
			start = ranges[i].angles[0];
			end = ranges[i].angles[1];
		}
		else
		{
			end = MAX(end, ranges[i].angles[1]);
		}
	}
	
	//insert the last unified range (gets left out from the loop)
	rangeUnion.push_back(AngleRange(start, end));
	
	delete [] ranges;
	
	//for(List<AngleRange>::iterator it = rangeUnion.begin(); it != rangeUnion.end(); ++it)
	//	printf("%lf %lf\n", it->angles[0] * RAD_TO_DEG, it->angles[1] * RAD_TO_DEG);
	//printf("\n");
	
	return true;
}

void Cleanup()
{
	g_Circles.clear();
	g_N = 0;
	
	g_Intersections.clear();
	g_Results.clear();
}

bool ReadInput(const char* file)
{
	FILE* data = fopen(file, "r");
	if(!data)
	{
		return false;
	}
	
	fscanf(data, "%lf%lf%lf%lf%d%d", &g_A.x, &g_A.y, &g_B.x, &g_B.y, &g_K, &g_N);
	
	double x,y,r;
	for(size_t i = 0; i < g_N; ++i)
	{
		fscanf(data, "%lf%lf%lf", &x, &y, &r);
		g_Circles.push_back(Circle(Vector2D(x,y), r));
	}
	fclose(data);
	
	return true;
}
