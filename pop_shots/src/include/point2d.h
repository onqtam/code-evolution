/******************************************************************************
 *                                                                            *
 *  POP SHOTS.                                                                *
 *                                                                            *
 *  Technological School Electronic Systems                                   *
 *  Technical University of Sofia                                             *
 *                                                                            *
 *  Copyright (C) 2009-2010 Viktor Kirilov ( n1ntendo@abv.bg )                *
 *                                                                            *
 ******************************************************************************/

#ifndef POINT2D
#define POINT2D

/**
 * Class for 2D points.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 22 Match 2010
 */
class Point2d {
private:

public:

	/**
	 * the x pos of the point
	 */
	int x;
	
	/**
	 * the y pos of the point
	 */
	int y;
	
private:

public:

	/**
	 * default constructor
	 */
	Point2d();
	
	/**
	 * constructor with parameters
	 * @param X the x of the point
	 * @param Y the y of the point
	 */
	Point2d(int X, int Y);
	
	/**
	 * default destructor
	 */
	~Point2d();
	
	/**
	 * the overloaded operator*
	 * @param scale the number to multiply by
	 * @return the resulting point
	 */
	Point2d operator*(float scale) const ;
	
	/**
	 * the overloaded operator/
	 * @param scale the number to divide by
	 * @return the resulting point
	 */
	Point2d operator/(float scale) const ;
	
	/**
	 * the overloaded operator+
	 * @param other the other point to sum to
	 * @return the resulting point
	 */
	Point2d operator+(const Point2d &other) const ;
	
	/**
	 * the overloaded operator-
	 * @param other the other point to substract
	 * @return the resulting point
	 */
	Point2d operator-(const Point2d &other) const ;
	
	/**
	 * the overloaded operator-
	 * @return the resulting point
	 */
	Point2d operator-() const ;
};

#endif
