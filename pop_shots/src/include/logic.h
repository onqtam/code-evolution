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

#ifndef LOGIC
#define LOGIC

#include <vector>
#include <string>

#include "objectmanager.h"
#include "explosionmanager.h"
#include "quadtree.h"
#include "physics.h"
#include "level.h"
#include "wind.h"

using namespace std;

/**
 * Class for the logical module.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 21 Dec 2009
 */
class Logic {
private:

public:

	/**
	 * the physics engine
	 */
	Physics physicsEngine;
	
	/**
	 * the explosion manager
	 */
	ExplosionManager explosionManager;
	
	/**
	 * the object manager
	 */
	ObjectManager objectManager;
	
	/**
	 * the object mapping quadtree
	 */
	QuadTree* objectMapping;
	
	/**
	 * the level
	 */
	Level level;
	
	/**
	 * the wind
	 */
	Wind wind;
	
private:

public:

	/**
	 * loads a level
	 * @param levelName the filename of the level
	 */
	void loadLevel(string);
	
	/**
	 * resizes the Quadtree
	 */
	void resizeObjectMap();
	
	/**
	 * default constructor
	 */
	Logic();
	
	/**
	 * default destructor
	 */
	~Logic();
	
};

#endif
