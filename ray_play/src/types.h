#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdlib.h>

#include "vector2d.h"
#include "list.h"
#include "array.h"
#include "constants.h"

struct Color
{
	float r,g,b;
	
	Color()
		: r(0)
		, g(0)
		, b(0)
	{
	}
	
	void Randomize()
	{
		Set(float(rand()) / RAND_MAX,
			float(rand()) / RAND_MAX,
			float(rand()) / RAND_MAX);
	}
	
	void Set(float R, float G, float B)
	{
		r = R;
		g = G;
		b = B;
	}
};

struct Ray
{
	Vector2D start, dir;
	unsigned int depth;
	
	Ray()
		: depth(0)
	{}
	
	Ray(const Vector2D& Start, const Vector2D& Dir)
		: start(Start)
		, dir(Dir)
		, depth(0)
	{}
};

struct Circle;
struct IntersectionInfo 
{
	Vector2D ip; //intersection point in the world-space
	double distance; //the distance to the intersection point along the ray
	Vector2D norm; //the normal of the geometry at the intersection point
	const Circle* circle; //the last circle that was hit
};

struct Circle 
{
	Vector2D o; //center of the circle
	double r; //radius of the circle
	
	Circle(Vector2D O = Vector2D(0, 0), double R = 1)
		: o(O)
		, r(R)
	{}
	
	bool isInside(const Vector2D& P) const
	{
		return (P - o).LengthSqr() < r * r;
	}
	
	bool intersect(const Ray& ray, IntersectionInfo& info) const;
};

struct IntersectionList
{
	Array<IntersectionInfo> infos;
	size_t numReflections;
	double accumulatedTangens;
	double startingAngle;
	
	Vector2D lastDir;
	
	Color color;
	
	IntersectionList(size_t MaxReflections, double Angle = 0.0)
		: infos(MaxReflections)
		, numReflections(0)
		, accumulatedTangens(0.0)
		, startingAngle(Angle)
		, lastDir(0,0)
	{}
	
	IntersectionList(const IntersectionList& other)
		: infos(other.infos)
		, numReflections(other.numReflections)
		, accumulatedTangens(other.accumulatedTangens)
		, startingAngle(other.startingAngle)
		, lastDir(other.lastDir)
		, color(other.color)
	{}
	
	bool HasHitSameGeometry(const IntersectionList& other)
	{
		for(size_t i = 0; i < numReflections && i < other.numReflections; ++i)
		{
			if(infos[i].circle != other.infos[i].circle)
			{
				return false;
			}
		}
		return numReflections == other.numReflections;
	}
};

struct AngleRange
{
	double angles[2];
	
	AngleRange()
	{}
	
	AngleRange(double A, double B)
	{
		angles[0] = A;
		angles[1] = B;
	}
};

inline bool operator <(AngleRange &Left, AngleRange &Right)
{
	return Left.angles[0] < Right.angles[0];
}

#endif // __TYPES_H__
