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

#ifndef SIGHT
#define SIGHT

#include "physicalobject.h"

#include "velocity.h"

using namespace std;

/**
 * Sample animated class, representing sights.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 22 March 2010
 */
class Sight : public PhysicalObject {
private:

	/**
	 * static filename for file(image) of the texture of this class
	 */
	static string filename;
	
	/**
	 * the object the sight is associated with
	 */
	Object* object;
	
	/**
	 * the distance from the object
	 */
	float distance;
	
	/**
	 * the offset from the object
	 */
	Velocity offsetFromMainObject;
	
public:

private:

public:

	/**
	 * Constructor with parameters
	 * @param obj the object the sight should be attached to
	 * @param dist the distance from that object
	 * @param ang the angle of the sight
	 */
	Sight(Object* obj, int dist = 100, float ang = 0);
	
	/**
	 * Default Destructor
	 */
	~Sight();
	
	/**
	 * changes the angle
	 * @param angle the new angle
	 */
	void changeAngle(float angle = 0);
};

#endif
