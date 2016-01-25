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

#include "../include/sight.h"
#include "../include/engine.h"

#include <math.h>

string Sight::filename = "resources/sprites/sights.bmp";

Sight::Sight(Object* obj, int dist, float ang) :
		PhysicalObject( filename, 0, 0, 0, 50, 50, gadget_object, true, 0, -1, non_explosive),
		object(obj),
		distance(dist) {
	if ( ang == 0 ) {
		ang = ((PhysicalObject*)obj)->getAngle();
	}
	
	changeAngle(ang);
	
	toggleVisibility();
}

Sight::~Sight() {

}

void Sight::changeAngle(float angle) {
	/*
	 * every time the angle is changed   the position is changed respectively
	 * last and current positions are registered for redrwaing if sight is visible
	 */
	if ( visible ) {
		if ( Engine::engine != NULL ) {
			Engine::engine->drawingengine.addToList((int)x, (int)y, (int)width, (int)height );
		}
	}
	
	offsetFromMainObject.y = sin(angle/57.295) * distance;
	offsetFromMainObject.x = cos(angle/57.295) * distance;
	
	y = object->getY() + object->getHeight()/2 + offsetFromMainObject.y - getHeight()/2;
	
	if ( ((PhysicalObject*)object)->getLookingDirection() == right ) {
		x = object->getX() + object->getWidth()/2 + offsetFromMainObject.x - getWidth()/2;
	} else {
		x = object->getX() + object->getWidth()/2 - offsetFromMainObject.x - getWidth()/2;
	}
	
	if ( visible ) {
		if ( Engine::engine != NULL ) {
			Engine::engine->drawingengine.addToList((int)x, (int)y, (int)width, (int)height );
		}
	}
	
	/*
	 * the correct sprite is being chosen by the angle
	 */
	float step = 360 / frames.size();
	
	if ( ((PhysicalObject*)object)->getLookingDirection() == left ) {
		angle = 180 - angle;
	} else {
		if ( offsetFromMainObject.y < 0 ) {
			angle = 360 + angle;
		}
	}
	
	unsigned int temp = (unsigned int) (frames.size() - angle / step + 1);
	
	if ( temp == frames.size() ) {
		temp = 0;
	}
	
	currentIndex = temp;
}
