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

#include "../include/arsenal.h"

unsigned int Arsenal::rows = ROWS;

Arsenal::Arsenal() :
		weapons(vector<vector<wep> >(10)) {
		
}

Arsenal::~Arsenal() {

}

void Arsenal::add(unsigned int arg_column, weapon arg_type, unsigned int arg_ammount) {
	if ( arg_column > 10 ) {
		return;
	}
	
	/*
	 * this pushes a weapon back to a column of weapons
	 */
	weapons[arg_column].push_back(wep(arg_type, arg_ammount));
}
