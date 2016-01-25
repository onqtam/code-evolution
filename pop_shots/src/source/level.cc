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

#include "../include/level.h"
#include "../include/engine.h"
#include "../include/camera.h"

Level::Level() :
		map(NULL),
		destructive(true) {
	map = NULL;
}

Level::~Level() {
	if ( map != NULL) {
		SDL_FreeSurface(map);
	}
}

bool Level::setMap(string arg_mapName) {
	if ( map != NULL ) {
		SDL_FreeSurface(map);
	}
	
	map = SDL_DisplayFormat(IMG_Load(arg_mapName.c_str()));
	
	SDL_SetColorKey(map, SDL_SRCCOLORKEY, SDL_MapRGB(map->format, 240, 240, 240));
	
	collision.set(map);
	
	return true;
}

void Level::toggleLevelDestruction() {
	destructive = !destructive;
}

void Level::makeCollisionOnSides(vector<Side::side>& sides, int thickness) {
	for ( unsigned int i = 0; i < sides.size(); i++ ) {
		switch (sides[i]) {
		case Side::left:
			Engine::engine->logic.level.collision.setRect(0, 0, thickness, getHeight(), 1);
			break;
			
		case Side::right:
			Engine::engine->logic.level.collision.setRect(getWidth() - thickness, 0, thickness, getHeight(), 1);
			break;
			
		case Side::top:
			collision.setRect(0,0,getWidth(),thickness,1);
			break;
			
		case Side::bottom:
			Engine::engine->logic.level.collision.setRect(0, getHeight() - thickness, getWidth(), thickness,1);
			break;
		};
	}
}

void Level::drawSides(vector<Side::side>& sides, Uint32 col, int thickness) {
	SDL_Rect area;
	
	for ( unsigned int i = 0; i < sides.size(); i++ ) {
		switch (sides[i]) {
		case Side::left:
			area.x = 0;
			area.y = 0;
			area.w = thickness;
			area.h = getHeight();
			
			SDL_FillRect(map, &area, col);
			
			break;
			
		case Side::right:
			area.x = getWidth() - thickness;
			area.y = 0;
			area.w = thickness;
			area.h = getHeight();
			
			SDL_FillRect(map, &area, col);
			
			break;
			
		case Side::top:
			area.x = 0;
			area.y = 0;
			area.w = getWidth();
			area.h = thickness;
			
			SDL_FillRect(map, &area, col);
			
			break;
			
		case Side::bottom:
			area.x = 0;
			area.y = getHeight() - thickness;
			area.w = getWidth();
			area.h = thickness;
			
			SDL_FillRect(map, &area, col);
			
			break;
		};
	}
}
