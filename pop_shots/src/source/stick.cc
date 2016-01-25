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

#include "../include/stick.h"
#include "../include/engine.h"
#include "../include/funcs.h"
#include "../include/types.h"

string Stick::filename = "resources/sprites/stick.bmp";

Stick::Stick(int posX, int posY, int delay, Velocity vel) :
		PhysicalObject( filename, posX, posY, delay, 50, 50, projectile_object, false, 100, 10000, explosive_on_timeout, 75, vel, true, "", -1, bounce_any_direction) {
	toggleVisibility();
	togglePhysics();
}

Stick::~Stick() {

}
