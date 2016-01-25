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

#include "../include/wind.h"

#include "../include/debug.h"

int Wind::updateInterval = UPDATE_INTERVAL;

int Wind::maxWind = MAXWIND;

int Wind::wind = 0;

Uint32 Wind::updateWind(Uint32 interval, void *param) {
	SDL_mutexP( ((Wind*)param)->mutex );
	
	int polarity = rand() % 2;
	
	if ( polarity == 0 ) {
		Wind::wind++;
		
		if ( Wind::wind > Wind::maxWind ) {
			Wind::wind = Wind::maxWind;
		}
	} else {
		Wind::wind--;
		
		if ( Wind::wind < -Wind::maxWind ) {
			Wind::wind = -Wind::maxWind;
		}
	}
	
	SDL_mutexV( ((Wind*)param)->mutex );
	
	return interval;
}

Uint32 Wind::printWind(Uint32 interval, void *param) {
	//fprintf(stderr, "Wind: %3d from maximum (absolute) %2i\n", wind, maxWind);
	
	return interval;
}

Wind::Wind() :
		timerId(0),
		debugTimerId(0),
		mutex(SDL_CreateMutex()) {
	timerId = SDL_AddTimer(Wind::updateInterval,updateWind,this);
	
	debugTimerId = SDL_AddTimer(2000, printWind, this);
}

Wind::~Wind() {
	if ( timerId != 0 ) {
		SDL_RemoveTimer(timerId);
		timerId = 0;
	}
	
	if ( debugTimerId != 0 ) {
		SDL_RemoveTimer(debugTimerId);
		debugTimerId = 0;
	}
}

void Wind::pause() {
	if ( timerId != 0 ) {
		SDL_RemoveTimer(timerId);
		timerId = 0;
	}
}

void Wind::resume() {
	if ( timerId == 0 ) {
		timerId = SDL_AddTimer(Wind::updateInterval,updateWind,this);
	}
}

int Wind::getWindDirection() {
	int temp;
	
	SDL_mutexP(mutex);
	
	temp = Wind::wind;
	
	SDL_mutexV(mutex);
	
	return temp;
}
