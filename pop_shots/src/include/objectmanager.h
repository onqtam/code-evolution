/******************************************************************************
 *                                                                            *
 *  POP SHOTS.                                                                *s
 *                                                                            *
 *  Technological School Electronic Systems                                   *
 *  Technical University of Sofia                                             *
 *                                                                            *
 *  Copyright (C) 2009-2010 Viktor Kirilov ( n1ntendo@abv.bg )                *
 *                                                                            *
 ******************************************************************************/

#ifndef OBJECTMANAGER
#define OBJECTMANAGER

#include <list>
#include <map>

#include "object.h"
#include "texture.h"

using namespace std;

/**
 * Class for managing objects.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 21 Dec 2009
 */
class ObjectManager {

	/**
	 * for access to everything
	 */
	friend class Engine;
	
	/**
	 * for access to everything
	 */
	friend class Logic;
	
private:

public:

	/**
	 * a static list holding pointers to all objects that have been created
	 */
	static list<Object*> objects;
	
	/**
	 * a static list holding pointers to all objects that are physical at the moment
	 */
	static list<Object*> physicalObjects;
	
	/**
	 * a static list holding pointers to all objects that are visible at the moment
	 */
	static list<Object*> visibleObjects;
	
private:

	/**
	 * default constructor
	 */
	ObjectManager();
	
public:

	/**
	 * recieves a pointer to an object and stores it
	 * @param obj the newly created object
	 * @return the obj parameter is returned for immediate use
	 */
	Object* newObject(Object* obj);
	
	/**
	 * deletes an object
	 * @param obj the object to delete
	 */
	void deleteObject(Object* obj);
	
	/**
	 * default destructor
	 */
	~ObjectManager();
	
	
};

#endif
