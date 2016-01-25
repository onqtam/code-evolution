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

#include "../include/windowsystem.h"

#include "../include/debug.h"

WindowSystem::WindowSystem() {

}

WindowSystem::~WindowSystem() {
	for ( vector<Window*>::iterator it = windows.begin(); it != windows.end(); it++ ) {
		delete *it;
	}
}

Window* WindowSystem::registerWindow(Window* wnd) {
	windows.push_back(wnd);
	return wnd;
}
