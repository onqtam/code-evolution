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

#ifndef LEVEL
#define LEVEL

#include <SDL.h>
#include <string>
#include <SDL_image.h>

#include "collision.h"
#include "funcs.h"
#include "types.h"

/**
 * Class for levels.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 21 Dec 2009
 */
class Level {
	/**
	 * for access to everything
	 */
	friend class Logic;
	
	/**
	 * for access to everything
	 */
	friend class Physics;
	
private:

	/**
	 * a surface to the map
	 */
	SDL_Surface* map;
	
	/**
	 * the collision of the map
	 */
	Collision collision;
	
public:

	/**
	 * a flag for being destructive(the level)
	 */
	bool destructive;
	
public:

	/**
	 * Default constructor
	 */
	Level();
	
	/**
	 * Default destructor
	 */
	~Level();
	
	/**
	 * Sets the map
	 * @param arg_mapName the filename of the map
	 * @return whether map setting was successful or not
	 */
	bool setMap(string arg_mapName);
	
	/**
	 * Gets the width of the level
	 * @return width
	 */
	int getWidth() {
		return map->w;
	}
	
	/**
	 * Gets the height of the level
	 * @return height
	 */
	int getHeight() {
		return map->h;
	}
	
	/**
	 * Gets a pointer to the surface of the map
	 * @return pointer to surface
	 */
	SDL_Surface* getSurface() {
		return map;
	}
	
	/**
	 * toggles whether the level is destructive or not
	 */
	void toggleLevelDestruction();
	
	/**
	 * makes the collision with ones on some given sides
	 * @param sides the sides to modify
	 * @param thickness the thickness of the collision on each ide
	 */
	void makeCollisionOnSides(vector<Side::side>& sides, int thickness = 1);
	
	/**
	 * draws some given sides with a given color and thickness
	 * @param sides the sides to draw
	 * @param col the color
	 * @param thickness the thickness of each side
	 */
	void drawSides(vector<Side::side>& sides, Uint32 col, int thickness = 1);
};

#endif
