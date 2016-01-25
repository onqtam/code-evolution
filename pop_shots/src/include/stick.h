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

#ifndef STICK
#define STICK

#include "physicalobject.h"
#include "velocity.h"
#include "texture.h"

#include <string>

using namespace std;

/**
 * Sample animated class.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 21 Dec 2009
 */
class Stick : public PhysicalObject {
private:

	/**
	 * static filename for file(image) of the texture of this class
	 */
	static string filename;
	
public:

private:

public:

	/**
	 * Constructor with parameters
	 * @param posX position X of the object
	 * @param posY position Y of the object
	 * @param delay delay between frames of animation
	 * @param vel the initial velocity
	 */
	Stick(int posX, int posY, int delay, Velocity vel = Velocity(0,0));
	
	/**
	 * Default Destructor
	 */
	~Stick();
	
};

#endif
