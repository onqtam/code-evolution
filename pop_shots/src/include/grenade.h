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

#ifndef GRENADE
#define GRENADE

#include "physicalobject.h"
#include "velocity.h"
#include "texture.h"

#include <string>

using namespace std;

/**
 * Sample animated class, representing grenades.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 22 March 2010
 */
class Grenade : public PhysicalObject {
private:

	/**
	 * static filename for file(image) of the texture of this class
	 */
	static string filename;
	
	/**
	 * static filename for file(image) of the texture of this class
	 */
	static string collision_filename;
	
public:

private:

public:

	/**
	 * Constructor with parameters
	 * @param posX position X of the object
	 * @param posY position Y of the object
	 * @param delay delay between frames of animation
	 * @param vel the velocity of the object
	 */
	Grenade(int posX, int posY, Uint32 time_before_explosion, int delay, Velocity vel = Velocity(0,0));
	
	/**
	 * Default Destructor
	 */
	~Grenade();
	
};

#endif
