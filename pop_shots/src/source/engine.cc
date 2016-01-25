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

#include "../include/engine.h"
#include "../include/debug.h"

#include <SDL.h>

Engine* Engine::engine = NULL;

Engine* Engine::Instance() {
	if ( engine == NULL) {
		/*
		 * only way to actually create an instance of the Engine
		 */
		Engine::engine = new Engine();
		atexit(Engine::freeEngine);
		atexit(SDL_Quit);
	}
	return Engine::engine;
}

void Engine::freeEngine() {
	Engine* temp = engine;
	engine = NULL;
	delete temp;
}

Engine::Engine() :
		core(),
		texturemanager(),
		video(),
		logic(),
		input(),
		drawingengine(),
		fontmanager(),
		windowsystem(),
		teammanager() {
}

Engine::~Engine() {

}
