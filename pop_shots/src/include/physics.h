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

#ifndef PHYSICS
#define PHYSICS

#include "physicalobject.h"
#include "object.h"
#include "types.h"

#include <list>

#define GRAVITY 700
#define ALLOWEDDISTANCE 1000
#define THRESHOLD 4
#define BOUNCERATIO (float)4/10
#define MINIMUMBOUNCEVELOCITY 10

using namespace std;

/**
 * Class for physics.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 21 Dec 2009
 */
class Physics {
private:

	/**
	 * holds the explosions in the last update
	 */
	list<Explosion> explosions;
	
public:

	/**
	 * the max distance between the object and the level
	 */
	static int allowedDistance;
	
	/**
	 * the maximum number of pixels a walking boundry should be overcomed
	 */
	static int threshold;
	
	/**
	 * the gravity
	 */
	static float gravity;
	
	/**
	 * the bounce ratio   (rate at which objects stop to bounce)
	 */
	static float bounceRatio;
	
	/**
	 * the minimum bounce velocity required for bouncing to continue
	 */
	static float minimumBounceVelocity;
	
private:

	/**
	 * apples gravity to an object
	 * @param obj the object gravity should be applied to
	 */
	void applyGravity(Object* obj);
	
	/**
	 * apples wind to an object
	 * @param obj the object wind should be applied to
	 */
	void applyWindEffect(PhysicalObject* obj);
	
public:

	/**
	 * constructor
	 * @param G the gravity
	 */
	Physics(float G = GRAVITY);
	
	/**
	 * default destructor
	 */
	~Physics();
	
	/**
	 * checks if an object is colliding with anything
	 * @param obj the object to be checked
	 * @param offX the offset of the object in the horizontal direction
	 * @param offY the offset of the object in the vertical direction
	 */
	bool checkForCollision(PhysicalObject* obj, float offX, float offY);
	
	/**
	 * moves an object
	 * @param obj the object to move
	 * @param offX the ammount of distance to move horizontally
	 * @param offY the ammount of distance to move vertically
	 */
	void moveObject(Object* obj, float offX, float offY);
	
	/**
	 * updates al objects (including walking, flying, exploding...)
	 */
	void updateObjects();
};

#endif
