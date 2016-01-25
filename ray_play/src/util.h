#ifndef __UTIL_H__
#define __UTIL_H__

#include <math.h>
#include "types.h"
#include "vector2d.h"
#include "constants.h"

#define MIN(A,B) (((A) < (B)) ? (A) : (B))
#define MAX(A,B) (((A) > (B)) ? (A) : (B))

#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

template <typename T>
inline void Swap(T& a, T& b) { T c(a); a = b; b = c; }

template <typename T>
inline T Abs(T a) { return a < 0 ? -a : a; }

inline double SignOf(double x) { return x > 0 ? +1 : -1; }

double Get2DAngleOfLineSegment(Vector2D A, Vector2D B);

bool GetIntersectionPointsBetweenCircles(const Circle& A, const Circle& B, Vector2D& P1, Vector2D& P2);

bool GetPointProjectionOntoRay(const Ray& ray, const Vector2D& point, Vector2D& out);

bool IsPointBetweenRays(const Vector2D& Point,
						const Vector2D& ProjectionFirst,
						const Vector2D& ProjectionSecond);

template <typename T>
void SiftDown(T *A, int Start, int End)
{
	int root = Start;
	
	while(root * 2 + 1 < End)
	{
		int child = 2 * root + 1;
		if ((child + 1 < End) && (A[child] < A[child + 1]))
		{
			child += 1;
		}
		if(A[root] < A[child])
		{
			Swap(A[child], A[root]);
			root = child;
		}
		else
		{
			return;
		}
	}
}

template <typename T>
void Heapsort(T *A, int Count)
{
	int start, end;
	
	//heapify
	for(start = (Count - 2) / 2; start >= 0; --start)
	{
		SiftDown(A, start, Count);
	}
	
	//heapsort
	for(end = Count - 1; end > 0; --end)
	{
		Swap(A[end], A[0]);
		SiftDown(A, 0, end);
	}
}

#endif // __UTIL_H__
