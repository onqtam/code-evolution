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

#ifndef OBJECT
#define OBJECT

#include <vector>

using namespace std;

/**
 * Class for main object functionality.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 21 Dec 2009
 */
class Object {
	/**
	 * for access to everything
	 */
	friend class ObjectManager;
	
	/**
	 * for access to everything
	 */
	friend class Team;
	
	/**
	 * for access to everything
	 */
	friend class Physics;
	
	/**
	 * for access to everything
	 */
	friend class PhysicalObject;
	
protected:

	/**
	 * X position of the object
	 */
	float x;
	
	/**
	 * Y position of the object
	 */
	float y;
	
	/**
	 * Tells whether the object is one of the visible ones or not
	 */
	bool visible;
	
	/**
	 * Tells whether the object is one of the physical ones or not
	 */
	bool physical;
	
	/**
	 * the id of the layer this object is supposed to be on
	 */
	int layerId;
	
	/**
	 * the width of each frame
	 */
	int width;
	
	/**
	 * the height of each frame
	 */
	int height;
	
	/**
	 * all the attached objects
	 */
	vector<Object*> attached;
	
public:

private:

public:

	/**
	 * Constructor with default parameters
	 * @param X initial X position
	 * @param Y initial Y position
	 */
	Object(float X=0, float Y=0, int layer = 0);
	
	/**
	 * Default Destructor (virtual so polymorphism can exist)
	 */
	virtual ~Object();
	
	/**
	 * Gets X value
	 * @return X position
	 */
	float getX() {
		return x;
	}
	
	/**
	 * Gets Y value
	 * @return Y position
	 */
	float getY() {
		return y;
	}
	
	/**
	 * Gets the width of each frame
	 * @return width
	 */
	int getWidth();
	
	/**
	 * Gets the height of each frame
	 * @return height
	 */
	int getHeight();
	
	/**
	 * gets the layer id of the object (vector layer, raster layer...)
	 * @return layer id
	 */
	int getLayerId();
	
	/**
	 * Checks if an object is visible
	 * @return whether it is visible or not
	 */
	bool isVisible();
	
	/**
	 * Checks if an object is physical
	 * @return whether it is physical or not
	 */
	bool isPhysical();
	
	/**
	 * Changes the physical property of the objet to the opposite of the current state
	 * @return whether it is physical or not
	 */
	bool togglePhysics();
	
	/**
	 * toggles the visibility of the object
	 */
	bool toggleVisibility();
	
	/**
	 * moves the object and all attached objects to it
	 * @param X the offset x
	 * @param Y the offset y
	 */
	void move(float X, float Y);
	
	/**
	 * teleports the object(and all attached objects to it) to a given position
	 * @param X the new x
	 * @param Y the new y
	 */
	void goTo(float X, float Y);
};

#endif
