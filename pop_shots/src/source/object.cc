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

#include "../include/object.h"
#include "../include/objectmanager.h"
#include "../include/funcs.h"
#include "../include/engine.h"

Object::Object(float X, float Y, int layer)
		: x(X), y(Y), visible(false), physical(false), layerId(layer) {
		
}

Object::~Object() {
	for ( unsigned int i = 0; i < attached.size(); i++ ) {
		delete attached[i];
	}
	
	if ( visible ) {
		ObjectManager::visibleObjects.erase(findItemInList<Object>(ObjectManager::visibleObjects, this));
		
		if ( Engine::engine != NULL) {
			Engine::engine->drawingengine.addToList((int)getX(), (int)getY(), (int)width, (int)height );
		}
	}
}

int Object::getWidth() {
	return width;
}

int Object::getHeight() {
	return height;
}

int Object::getLayerId() {
	return layerId;
}

bool Object::isVisible() {
	return visible;
}

bool Object::isPhysical() {
	return physical;
}

bool Object::togglePhysics() {
	physical = !physical;
	
	if ( !physical ) {
		ObjectManager::physicalObjects.erase(findItemInList<Object>(ObjectManager::physicalObjects, this));
	} else {
		ObjectManager::physicalObjects.push_back(this);
	}
	
	return physical;
}


bool Object::toggleVisibility() {
	visible = !visible;
	
	if ( !visible ) {
		ObjectManager::visibleObjects.erase(findItemInList<Object>(ObjectManager::visibleObjects, this));
		
		Engine::engine->drawingengine.addToList((int)getX(), (int)getY(), (int)width, (int)height );
	} else {
		ObjectManager::visibleObjects.push_back(this);
		
		Engine::engine->drawingengine.addToList((int)getX(), (int)getY(), (int)width, (int)height );
	}
	
	return visible;
}

void Object::move(float X, float Y) {
	x += X;
	y += Y;
	
	for ( unsigned int i = 0; i < attached.size(); i++ ) {
		attached[i]->move(X, Y);
	}
	
	if ( visible ) {
		if ( (int)(x - X) != (int)x || (int)(y - Y) != (int)y ) {
			Engine::engine->drawingengine.addToList((int)x, (int)y, width, height );
			Engine::engine->drawingengine.addToList((int)(x - X), (int)(y - Y), width, height );
		}
	}
}

void Object::goTo(float X, float Y) {
	move(X - x, Y - y);
}
