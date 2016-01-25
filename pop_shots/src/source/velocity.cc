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

#include "../include/velocity.h"

#include <math.h>

#include "../include/debug.h"

Velocity::Velocity() :
		x(0),
		y(0) {
		
}

Velocity::Velocity(float angle) {
	/*
	 * 57.3 is the proportion between 1 radian and 1 degree
	 */
	x = cos(angle/57.3);
	y = sin(angle/57.3);
}

Velocity::Velocity(float X, float Y) :
		x(X),
		y(Y) {
		
}

Velocity::~Velocity() {

}

float Velocity::getDistance() {
	return sqrt(pow(x,2) + pow(y,2));
}

Velocity Velocity::operator*(float scale) const {
	return Velocity(x * scale, y * scale);
}

Velocity Velocity::operator/(float scale) const {
	return Velocity(x / scale, y / scale);
}

Velocity Velocity::operator+(const Velocity &other) const {
	return Velocity(x + other.x, y + other.y);
}

Velocity Velocity::operator-(const Velocity &other) const {
	return Velocity(x - other.x, y - other.y);
}
