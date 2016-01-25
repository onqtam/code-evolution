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

#ifndef VELOCITY
#define VELOCITY

/**
 * Class for 2D velocities.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 22 Match 2010
 */
class Velocity {
private:

public:

	/**
	 * the x value of the velocity
	 */
	float x;
	
	/**
	 * the y value of the velocity
	 */
	float y;
	
private:

public:

	/**
	 * the default constructor
	 */
	Velocity();
	
	/**
	 * the constructor with arguments
	 * @param angle the angle of the velocity
	 */
	Velocity(float angle);
	
	/**
	 * constructor with parameters
	 * @param X the x value of the velocity
	 * @param Y the y value of the velocity
	 */
	Velocity(float X, float Y);
	
	/**
	 * default destructor
	 */
	~Velocity();
	
	/**
	 * gets the distance of the vector
	 * @return the calculated distance
	 */
	float getDistance();
	
	/**
	 * the overloaded operator*
	 * @param scale the value to multiply by
	 * @return the resulting velocity
	 */
	Velocity operator*(float scale) const ;
	
	/**
	 * the overloaded operator/
	 * @param scale the value to divide by
	 * @return the resulting velocity
	 */
	Velocity operator/(float scale) const;
	
	/**
	 * the overloaded operator+
	 * @param other the velocity to add to
	 * @return the resulting velocity
	 */
	Velocity operator+(const Velocity &other) const ;
	
	/**
	 * the overloaded operator-
	 * @param other the velocity to substract
	 * @return the resulting velocity
	 */
	Velocity operator-(const Velocity &other) const ;
	
};

#endif
