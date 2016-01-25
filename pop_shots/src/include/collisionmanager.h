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

#ifndef COLLISIONMANAGER
#define COLLISIONMANAGER

#include "collision.h"
#include "texture.h"
#include "types.h"

#include <vector>
#include <string>
#include <map>

#include "debug.h"

using namespace std;

/**
 * a struct for holding collision entries
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 22 Match 2010
 */
struct collisionMapEntry {
	/**
	 * the references to the collisions for a certain file
	 */
	unsigned int referenceCount;
	
	/**
	 * the collisions for a certain file
	 */
	vector<Collision*> collisions;
};

/**
 * Class for managing collisions
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 22 Match 2010
 */
class CollisionManager {
private:

	/**
	 * holds all collisions
	 */
	static map<string, collisionMapEntry> collisionData;
	
public:

private:

	/**
	 * calculates the areas for each collision for a iven texture and fills the container
	 * @param collisions the container to fill
	 * @param texture the texture to extract the collisions from
	 * @param width the width of each collision
	 * @param height the height of each colision
	 * @return true on success
	 */
	static bool calculateFrames(vector<Collision*>* collisions, Texture* texture, int width, int height);
	
public:

	/**
	 * gets a pointer to a vector with references for a given collision file
	 * @param collisionFilename the file
	 * @param width the desired width for each collision
	 * @param height the desired height for each collision
	 * @return a pointer to a vector, full of collisions for the given collision file
	 */
	static vector<Collision*>* getCollisions(string collisionFilename, int width, int height);
	
	/**
	 * used for notifying that a certain set of collisions for a given collision file is needed by minus one more objects
	 * @param collisionFilename the collision file
	 */
	static void ungetCollisions(string collisionFilename);
};

#endif
