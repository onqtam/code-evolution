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

#include "../include/grenade.h"

string Grenade::filename = "resources/sprites/grenades.bmp";

string Grenade::collision_filename = "resources/sprite_collisions/grenades_collision.bmp";

Grenade::Grenade(int posX, int posY, Uint32 time_before_explosion, int delay, Velocity vel) :
		PhysicalObject( filename, posX, posY, delay, 55, 55, projectile_object, false, 100, time_before_explosion, explosive_on_timeout, 100, vel, true, Grenade::collision_filename, -1, bounce_any_direction) {
	toggleVisibility();
	togglePhysics();
}

Grenade::~Grenade() {

}
