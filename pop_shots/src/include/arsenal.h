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

#ifndef ARSENAL
#define ARSENAL

#include "types.h"

#include <vector>

using namespace std;

#define ROWS 10

/**
 * Struct for holding weapons and ammounts.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 22 Match 2010
 */
struct wep {
	/**
	 * the type of the weapon
	 */
	weapon type;
	
	/**
	 * the quantity of the weapon
	 */
	int quantity;
	
	/**
	 * Constructor with default parameters
	 * @param arg_type the type of the weapon
	 * @param arg_quantity the quantity of the weapon
	 */
	wep(weapon arg_type = blank, int arg_quantity = -1) :
			type(arg_type),
			quantity(arg_quantity) {
			
	}
};

/**
 * Class for holding weapon sets.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 22 Match 2010
 */
class Arsenal {
private:

	/**
	 * the limit of the rows (not more than 10)
	 */
	static unsigned int rows;
	
public:

	/**
	 * the 2 dimentional array of weapons
	 */
	vector< vector<wep> > weapons;
	
private:


public:

	/**
	 * default constructor
	 */
	Arsenal();
	
	/**
	 * default destructor
	 */
	~Arsenal();
	
	/**
	 * for adding weapons
	 * @param arg_column the column in which the weapon should be placed
	 * @param arg_type the type of the weapon
	 * @param arg_ammount the desired quantity for the weapon
	 */
	void add(unsigned int arg_column, weapon arg_type, unsigned int arg_ammount);
	
};

#endif
