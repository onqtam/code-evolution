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

#ifndef EXPLOSIONMANAGER
#define EXPLOSIONMANAGER

#include "texture.h"

#include <vector>
#include <string>

using namespace std;

/**
 * a struct for holding an explosion
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 21 Dec 2009
 */
struct explosionEntry {
	float radius;
	Texture* texture;
};

/**
 * Class for managing explosions
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 21 Dec 2009
 */
class ExplosionManager {
private:

	/**
	 * the name of the text file, holding all the names of the explosions
	 */
	static string textfile;
	
	/**
	 * holds all explosions
	 */
	vector<explosionEntry> explosions;
	
public:

private:

public:

	/**
	 * defauld constructor
	 */
	ExplosionManager();
	
	/**
	 * defauld destructor
	 */
	~ExplosionManager();
	
	/**
	 * gets a requested explosion
	 * @param radius the radius of the desired explosion
	 * @return a texture pointer to an explosion
	 */
	Texture* getExplosion(float radius);
	
};

#endif
