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

#ifndef PHYSICALOBJECT
#define PHYSICALOBJECT

#include "animation.h"
#include "velocity.h"
#include "collision.h"
#include "types.h"

#include <string>
#include <vector>

using namespace std;

class PhysicalObject : public Animation {
	/**
	 * For access to everything.
	 */
	friend class Physics;
	
private:

	/**
	 * the angle at which the object is looking at
	 */
	float lookingAngle;
	
	/**
	 * represents the ratio at which physics apply to the object
	 */
	float physicalInterferenceRatio;
	
	/**
	 * a flag telling if the object is flying
	 */
	bool flying;
	
	/**
	 * tells what kind of an explosive the object is
	 */
	explosive_type explosive;
	
	/**
	 * tells the radius of the explosion the object should create when exploding
	 */
	float radius_of_explosion;
	
	/**
	 * the walking speed of the object
	 */
	float walkingSpeed;
	
	/**
	 * the walking direction
	 */
	direction walkingDirection;
	
	/**
	 * the looking direction
	 */
	direction lookingDirection;
	
	/**
	 * the seconds left to live
	 */
	int ttl;
	
	/**
	 * the current velocity
	 */
	Velocity velocity;
	
	/**
	 * the filename of the collision file
	 */
	string collision_filename;
	
	/**
	 * the index of the collision
	 */
	unsigned int collisionIndex;
	
	/**
	 * all collisions
	 */
	vector<Collision*>* collisions;
	
	/**
	 * tells if the object's sprite and collision should be dependent of the velocity
	 */
	bool representedByVelocity;
	
	/**
	 * the health points of the object
	 */
	int health;
	
	/**
	 * the type of bouncing
	 */
	bouncing_type bouncing;
	
public:

private:

public:

	/**
	 * Constructor with parameters
	 * @param filename the name of the animation file
	 * @param posX the x pos of the object
	 * @param posY the y pos of the object
	 * @param delay the delay between each frame
	 * @param width the width
	 * @param height the height
	 * @param layer the layer to which the object belongs to
	 * @param represented_by_velocity tells if the object is represented (logically and graphycally) by velocity
	 * @param walk_speed the walking speed
	 * @param time_to_live the seconds life left for the object
	 * @param exp the type of the object as far as exploding is concerned
	 * @param radius the radius of explosion
	 * @param vel the initial velocity
	 * @param makeCollision tells if a collision should be made or not
	 * @param collision_filename the filename for the collision file
	 * @param hp the health
	 * @param b the type of bouncyness for the object
	 */
	PhysicalObject(string filename, int posX, int posY, int delay, int width, int height, int layer = raster_object, bool represented_by_velocity = false, int walk_speed = 0.0, int time_to_live = -1, explosive_type exp = non_explosive, float radius = 100, Velocity vel = Velocity(0,0), bool makeCollision = false, string collision_filename = "", int hp = -1, bouncing_type b = bounce_any_direction);
	
	/**
	 * Default Destructor
	 */
	~PhysicalObject();
	
	/**
	 * updates the sprite and collision according to the current velocity
	 */
	void updateRepresentationFromVelocity();
	
	/**
	 * gets the looking angle
	 * @return the angle
	 */
	float getAngle();
	
	/**
	 * gets the current health
	 * @return the health
	 */
	int getHealth();
	
	/**
	 * gets the current looking direction
	 * @return the looking direction
	 */
	direction getLookingDirection();
	
	/**
	 * makes the object to jump
	 * @param power the power of the jump
	 * @param angle the angle at which the object should jump
	 */
	void jump(float power = 100, float angle = -90);
	
	/**
	 * turns the object to a direction
	 * @param dir the desired direction
	 */
	void turnTo(direction dir);
	
	/**
	 * returns the walking direction
	 * @return the walking direction
	 */
	direction getWalkingDirection();
	
	/**
	 * increases the looking angle
	 * @param value the value to be increased with
	 */
	void increaseAngle(float value);
};

#endif
