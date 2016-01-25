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

#include "../include/logic.h"
#include "../include/engine.h"
#include "../include/funcs.h"

Logic::Logic() :
		objectMapping(NULL) {
	//level.setMap("");
	//resizeObjectMap();
}

void Logic::resizeObjectMap() {
	if ( objectMapping != NULL ) {
		delete objectMapping;
	}
	objectMapping = new QuadTree( makePoint2d(0,0), makePoint2d(level.getWidth(), level.getHeight()), 0 );
}

Logic::~Logic() {

}

void Logic::loadLevel(string levelName) {
	level.setMap(levelName);
	
	resizeObjectMap();
}
