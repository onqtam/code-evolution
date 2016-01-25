#include "types.h"

bool Circle::intersect(const Ray& ray, IntersectionInfo& info) const
{
	//compute the circle intersection using a quadratic equation:
	Vector2D H = ray.start - o;
	double A = ray.dir.LengthSqr();
	double B = 2 * Dot(H, ray.dir);
	double C = H.LengthSqr() - r * r;
	double Dscr = B * B - 4 * A * C;
	if (Dscr < 0)
	{
		return false; //no solutions to the quadratic equation - then we don't have an intersection.
	}
	
	double x1, x2;
	x1 = (-B + sqrt(Dscr)) / (2 * A);
	x2 = (-B - sqrt(Dscr)) / (2 * A);
	double sol = x2; //get the closer of the two solutions...
	if (sol < 0)
	{
		sol = x1; //... but if it's behind us, opt for the other one
	}
	if (sol < 0)
	{
		return false; //... still behind? Then the whole circle is behind us - no intersection.
	}
	
	info.distance = sol;
	info.ip = ray.start + ray.dir * sol;
	info.circle = this;
	info.norm = info.ip - o; //generate the normal by getting the direction from the center to the ip
	info.norm.Normalize();
	
	return true;
}
