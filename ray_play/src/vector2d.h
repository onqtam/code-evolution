#ifndef __VECTOR2D_H__
#define __VECTOR2D_H__

#include <math.h>

struct Vector2D
{
	double x, y;
	
	Vector2D()
		: x(0)
		, y(0)
	{}
	
	Vector2D(double X, double Y)
		: x(X)
		, y(Y)
	{}
	
	void Set(double X, double Y)
	{
		x = X;
		y = Y;
	}
	
	double Length() const
	{
		return sqrt(x * x + y * y);
	}
	
	double LengthSqr() const
	{
		return (x * x + y * y);
	}
	
	void Scale(double Multiplier)
	{
		x *= Multiplier;
		y *= Multiplier;
	}
	
	double& operator[](int i)
	{
		return (&x)[i];
	}
	
	const double& operator[](int i) const
	{
		return (&x)[i];
	}
	
	void operator *=(double Multiplier)
	{
		Scale(Multiplier);
	}
	
	void operator /=(double Divider)
	{
		Scale(1.0 / Divider);
	}
	
	Vector2D& Normalize()
	{
		double lSqr = LengthSqr();
		if(!(lSqr >= 0.9999999 && lSqr < 1.0000001))
		{
			Scale(1.0 / sqrt(lSqr));
		}
		
		return *this;
	}
	
	void SetLength(double NewLength)
	{
		Scale(NewLength / Length());
	}
	
	void operator +=(const Vector2D& Rhs)
	{
		x += Rhs.x;
		y += Rhs.y;
	}
	
	void operator -=(const Vector2D& Rhs)
	{
		x -= Rhs.x;
		y -= Rhs.y;
	}
};

inline Vector2D operator +(const Vector2D& A, const Vector2D& B)
{
	return Vector2D(A.x + B.x, A.y + B.y);
}

inline Vector2D operator -(const Vector2D& A, const Vector2D& B)
{
	return Vector2D(A.x - B.x, A.y -B.y);
}

inline Vector2D operator -(const Vector2D& A)
{
	return Vector2D(-A.x, -A.y);
}

inline double operator *(const Vector2D& A, const Vector2D& B)
{
	return A.x * B.x + A.y * B.y;
}

inline double Dot(const Vector2D& A, const Vector2D& B)
{
	return A.x * B.x + A.y * B.y;
}

inline double Cross(const Vector2D& A, const Vector2D& B)
{
	return A.x * B.y - A.y * B.x;
}

inline Vector2D operator *(const Vector2D& A, double Multiplier)
{
	return Vector2D(A.x * Multiplier, A.y * Multiplier);
}

inline Vector2D operator *(double Multiplier, const Vector2D& A)
{
	return Vector2D(A.x * Multiplier, A.y * Multiplier);
}

inline Vector2D operator /(const Vector2D& A, double Divider)
{
	double multiplier = 1.0 / Divider;
	return Vector2D(A.x * multiplier, A.y * multiplier);
}

inline Vector2D Reflect(const Vector2D& ToBeReflected, const Vector2D& Normal)
{
	return ToBeReflected + 2 *(Dot(Normal, -ToBeReflected)) * Normal;
}

inline Vector2D Faceforward(const Vector2D& V, const Vector2D& Right)
{
	if(Dot(Right, V) < 0)
	{
		return V;
	}
	else 
	{
		return -V;
	}
}

#endif // __VECTOR2D_H__
