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

#include "../include/point2d.h"

Point2d::Point2d() :
		x(0),
		y(0) {
		
}

Point2d::Point2d(int X, int Y) :
		x(X),
		y(Y) {
		
}

Point2d::~Point2d() {

}

Point2d Point2d::operator*(float scale) const {
	return Point2d(x * scale, y * scale);
}

Point2d Point2d::operator/(float scale) const {
	return Point2d(x / scale, y / scale);
}

Point2d Point2d::operator+(const Point2d &other) const {
	return Point2d(x + other.x, y + other.y);
}

Point2d Point2d::operator-(const Point2d &other) const {
	return Point2d(x - other.x, y - other.y);
}

Point2d Point2d::operator-() const {
	return Point2d(-x, -y);
}
