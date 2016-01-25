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

#ifndef WORM
#define WORM

#include "physicalobject.h"
#include "sight.h"
#include "types.h"
#include "text.h"

#include <string>

using namespace std;

/**
 * Class for worms.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 19 Match 2010
 */
class Worm : public PhysicalObject {
private:

	/**
	 * the filename of the animation file
	 */
	static string filename;
	
	/**
	 * the filename of the collision file
	 */
	static string collision_filename;
	
public:

	/**
	 * the sight of the worm
	 */
	Sight* sight;
	
	/**
	 * the text, indicating the worm's health
	 */
	Text* healthText;
	
	/**
	 * the current firepower
	 */
	float firePower;
	
	/**
	 * tells if the worm is firing
	 */
	bool firing;
	
	/**
	 * tells when the worm las fired anything
	 */
	Uint32 lastFired;
	
	/**
	 * tells which column of weapons is currently selected by the worm
	 */
	unsigned int weaponColumn;
	
	/**
	 * tells which weapon from a given column is seleted
	 */
	unsigned int wep;
	
private:

public:

	/**
	 * constructor with parameters
	 * @param posX the x pos of the worm
	 * @param posY the y pos of the worm
	 * @param health the health of the worm
	 */
	Worm(int posX, int posY, int health);
	
	/**
	 * default destructor
	 */
	~Worm();
	
	/**
	 * increases the firepower of the worm with a given value
	 * @param value the value to add to the current firepower
	 */
	void increaseFirePower(float value);
	
	/**
	 * fires a weapon
	 * @param w the weapon to fire
	 * @param power the power to shoot the weapon with
	 */
	void fire(weapon w, float power);
};

#endif
