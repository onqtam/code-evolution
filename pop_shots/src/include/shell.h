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

#ifndef SHELL
#define SHELL

#include "physicalobject.h"

using namespace std;

/**
 * Sample animated class, representing shells.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 22 March 2010
 */
class Shell : public PhysicalObject {
private:

	/**
	 * static filename for file(image) of the texture of this class
	 */
	static string filename;
	
public:

private:

public:

	/**
	 * Constructor with parameters
	 * @param posX position X of the object
	 * @param posY position Y of the object
	 * @param delay delay between frames of animation
	 */
	Shell(int posX, int posY, Velocity vel);
	
	/**
	 * Default Destructor
	 */
	~Shell();
};

#endif
