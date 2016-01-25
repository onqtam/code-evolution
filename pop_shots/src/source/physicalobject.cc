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

#include "../include/physicalobject.h"
#include "../include/collisionmanager.h"
#include "../include/engine.h"
#include "../include/funcs.h"
#include "../include/math.h"

PhysicalObject::PhysicalObject( string filename, int posX, int posY, int delay, int width, int height, int layer,
                                bool represented_by_velocity, int walk_speed, int time_to_live, explosive_type exp,
                                float radius, Velocity vel, bool makeCollision, string coll_filename, int hp, bouncing_type b) :
		Animation(filename, delay, posX, posY, width, height, layer),
		lookingAngle(0.1),
		physicalInterferenceRatio(1),
		flying(true),
		explosive(exp),
		radius_of_explosion(radius),
		walkingSpeed(walk_speed),
		walkingDirection(none),
		lookingDirection(right),
		ttl(time_to_live),
		velocity(vel),
		collisionIndex(0),
		collisions(NULL),
		representedByVelocity(represented_by_velocity),
		health(hp),
		bouncing(b) {
	if ( makeCollision ) {
		if ( coll_filename != "" ) {
			collision_filename = coll_filename;
		} else {
			collision_filename = filename;
		}
		
		collisions = CollisionManager::getCollisions(collision_filename, width, height);
	}
}

PhysicalObject::~PhysicalObject() {
	if ( collisions != NULL ) {
		CollisionManager::ungetCollisions(collision_filename);
	}
}

float PhysicalObject::getAngle() {
	return lookingAngle;
}

int PhysicalObject::getHealth() {
	return health;
}

direction PhysicalObject::getLookingDirection() {
	return lookingDirection;
}

void PhysicalObject::updateRepresentationFromVelocity() {
	if ( representedByVelocity ) {
		float step;
		
		if ( collisions != NULL ) {
			step = 360 / collisions->size();
		} else {
			step = 360 / frames.size();
		}
		
		float angle = asin( velocity.y / sqrt(velocity.x*velocity.x + velocity.y*velocity.y)) * 57.3;
		
		if ( velocity.x < 0 ) {
			angle = 180 - angle;
		} else {
			if ( velocity.y < 0 ) {
				angle = 360 + angle;
			}
		}
		
		unsigned int temp;
		
		if ( collisions != NULL ) {
			temp = (unsigned int) (collisions->size() - angle / step + 1);
			
			if ( temp == collisions->size() ) {
				temp = 0;
			}
		} else {
			temp = (unsigned int) (frames.size() - angle / step + 1);
			
			if ( temp == frames.size() ) {
				temp = 0;
			}
		}
		
		if ( collisions != NULL ) {
			if ( temp != collisionIndex ) {
				collisionIndex = temp;
				
				if ( frames.size() > temp ) {
					currentIndex = temp;
				}
				
				if ( visible ) {
					if ( Engine::engine != NULL ) {
						Engine::engine->drawingengine.addToList((int)x, (int)y, (int)width, (int)height );
					}
				}
			}
		} else {
			if ( temp != (unsigned int)currentIndex ) {
				currentIndex = temp;
				
				if ( visible ) {
					if ( Engine::engine != NULL ) {
						Engine::engine->drawingengine.addToList((int)x, (int)y, (int)width, (int)height );
					}
				}
			}
		}
	}
}

void PhysicalObject::jump(float power, float angle) {
	if ( !(flying) ) {
		if ( angle == -90 ) {
			angle = lookingAngle;
		}
		
		flying = true;
		velocity = Velocity(angle) * power;
		
		if ( lookingDirection == left ) {
			velocity.x *= -1;
		}
	}
}

void PhysicalObject::turnTo(direction dir) {
	if ( dir == left || dir == right ) {
		walkingDirection = dir;
		lookingDirection = dir;
	}
	
	if ( dir == none ) {
		walkingDirection = none;
	}
}

direction PhysicalObject::getWalkingDirection() {
	return walkingDirection;
}

void PhysicalObject::increaseAngle(float value) {
	lookingAngle += value;
	if ( lookingAngle > 90 ) {
		lookingAngle = 90;
	}
	
	if ( lookingAngle < -90 ) {
		lookingAngle = -90;
	}
}
