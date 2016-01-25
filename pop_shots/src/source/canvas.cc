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

#include "../include/canvas.h"

void Canvas::convertCanvas(void) {
	Surface = SDL_DisplayFormat(SDL_GetVideoSurface());
}

Canvas::Canvas() {
	Surface=NULL;
}

Canvas::~Canvas() {
	Surface=NULL;
}

void Canvas::setCanvas(SDL_Surface* newSurface) {
	SDL_FreeSurface(Surface);
	Surface = newSurface;
	convertCanvas();
}
