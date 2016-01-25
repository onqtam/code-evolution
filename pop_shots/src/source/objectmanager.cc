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

#include "../include/objectmanager.h"
#include "../include/funcs.h"
#include "../include/engine.h"

list<Object*> ObjectManager::objects;
list<Object*> ObjectManager::physicalObjects;
list<Object*> ObjectManager::visibleObjects;

ObjectManager::ObjectManager() {

}

ObjectManager::~ObjectManager() {
	for ( list<Object*>::iterator it = objects.begin(); it != objects.end(); it++ ) {
		delete (*it);
	}
}

Object* ObjectManager::newObject(Object* obj) {
	Engine::engine->logic.objectMapping->add(obj);
	objects.push_back(obj);
	return obj;
}

void ObjectManager::deleteObject(Object* obj) {
	list<Object*>::iterator it = findItemInList<Object>(objects, obj);
	
	if (it != objects.end()) {
		Engine::engine->logic.objectMapping->remove(obj);
		delete obj;
		objects.erase(it);
	}
}
