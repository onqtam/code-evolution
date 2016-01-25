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

#include "../include/shell.h"
#include "../include/engine.h"
#include "../include/funcs.h"
#include "../include/types.h"

#include "../include/debug.h"

string Shell::filename = "resources/sprites/shells.bmp";

Shell::Shell(int posX, int posY, Velocity vel) :
		PhysicalObject( filename, posX, posY, 0, 50, 50, projectile_object, true, 0, -1, explosive_on_contact, 150, vel, true) {
	toggleVisibility();
	togglePhysics();
	updateRepresentationFromVelocity();
}

Shell::~Shell() {

}
