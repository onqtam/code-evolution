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

#include "../include/core.h"
#include "../include/engine.h"

using namespace Keys;

Core::Core() :
		running(false),
		last_loop_time(0) {
		
}

Core::~Core() {

}

void Core::clearEvents() {
	events.clear();
}

void Core::addEvent(SDL_Event ev) {
	SDL_PushEvent(&ev);
}

void Core::handleEvents(void) {
	/*
	 * while there are events in the SDL queue
	 */
	while (SDL_PollEvent(&currEvent)) {
		events.push_back(currEvent);
		switch (currEvent.type) {
		case SDL_KEYDOWN:
		case SDL_KEYUP:
		
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEMOTION:
		
			Engine::engine->input.Update(currEvent);
			
			if ( Engine::engine->input.WasKeyPressed(Escape) ) {
				running = false;
			}
			
			break;
			
		case SDL_USEREVENT:
			break;
			
		case SDL_VIDEORESIZE:
			Engine::engine->video.camera.adjustSize(Engine::engine->video.GetWidth(), Engine::engine->video.GetHeight());
			break;
			
		case SDL_QUIT:
			running = false;
			break;
		}
	}
}

void Core::loop() {
	/*
	 * for fps
	 */
	int counter=0;
	int timesPrinted=0;
	
	
	
	Uint32 tempTime = SDL_GetTicks();
	
	running=true;
	
	while (running) {
		/*
		 * calculating how much ms the last loop took
		 */
		last_loop_time = SDL_GetTicks() - tempTime;
		tempTime = SDL_GetTicks();
		
		/*
		 * input & events
		 */
		handleEvents();
		
		/*
		 * update logic
		 */
		Engine::engine->logic.physicsEngine.updateObjects();
		
		/*
		 * redraw
		 */
		Engine::engine->video.camera.updatePosition();
		Engine::engine->drawingengine.redraw();
		
		/*
		 * cleanup
		 */
		Engine::engine->input.KeyStatesToNextPhase();
		Engine::engine->video.camera.reset();
		clearEvents();
		
		/*
		 * for fps
		 */
		counter++;
		
		if ((SDL_GetTicks()/1000 - timesPrinted)>0) {
			printf("%6d loops per sec. Number of objects: %3d\n",counter/((SDL_GetTicks()/1000) - timesPrinted ), (int)ObjectManager::objects.size());
			timesPrinted++;
			counter=0;
		}
	}
}

