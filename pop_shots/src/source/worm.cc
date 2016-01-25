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

#include "../include/worm.h"
#include "../include/engine.h"
#include "../include/shell.h"
#include "../include/grenade.h"
#include "../include/velocity.h"
#include "../include/team.h"
#include "../include/types.h"

string Worm::filename = "resources/sprites/worms.bmp";

string Worm::collision_filename = "resources/sprite_collisions/worms_collision.bmp";

Worm::Worm(int posX, int posY, int health) :
		PhysicalObject( filename, posX, posY, 30, 80, 80, character_object, false, 200, -1, non_explosive, 0, Velocity(0,0), true, Worm::collision_filename, health, bounce_none),
		firePower(0),
		firing(false),
		lastFired(0),
		weaponColumn(1),
		wep(0) {
	toggleVisibility();
	togglePhysics();
}

Worm::~Worm() {

}

void Worm::increaseFirePower(float value) {
	firePower += value;
}

void Worm::fire(weapon w, float power) {
	Velocity vel = Velocity( getAngle() )*power ;
	if ( getLookingDirection() == left ) {
		vel.x *= -1;
	}
	
	Velocity vel_max = Velocity( getAngle() )*Team::maxFirePower ;
	if ( getLookingDirection() == left ) {
		vel_max.x *= -1;
	}
	
	switch (w) {
	case blank:
	
		break;
		
	case shell:
	
		Engine::engine->logic.objectManager.newObject( new Shell(x + getWidth()/2, y + getHeight()*2 , vel) );
		
		break;
		
	case power_shell:
	
		Engine::engine->logic.objectManager.newObject( new Shell(x + getWidth()/2, y + getHeight()*2 , vel_max) );
		
		break;
		
	case grenade:
	
		Engine::engine->logic.objectManager.newObject( new Grenade(x + getWidth()/2, y + getHeight()*2, 5000, ((float)Team::maxFirePower * 2) / vel.getDistance()  , vel) );
		
		break;
		
	case power_grenade:
	
		Engine::engine->logic.objectManager.newObject( new Grenade(x + getWidth()/2, y + getHeight()*2, 5000, ((float)Team::maxFirePower * 2) / vel_max.getDistance() , vel_max) );
		
		break;
	}
}
