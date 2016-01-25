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

#ifndef WINDOW
#define WINDOW

#include <SDL.h>

#include "velocity.h"
#include "types.h"

using namespace std;

/**
 * Class for wind.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 22 Match 2010
 */
class Window {

	/**
	 * for access to everything
	 */
	friend class WindowSystem;
	
private:

	/**
	 * the SDL surface of the window
	 */
	SDL_Surface* surface;
	
	/**
	 * the velocity of the window
	 */
	Velocity velocity;
	
	/**
	 * the x pos of the window
	 */
	float x;
	
	/**
	 * the y pos of the window
	 */
	float y;
	
	/**
	 * this tells if the windows is visible
	 */
	bool visible;
	
	/**
	 * this tells what kind of a window the window actually is
	 */
	window_type type;
	
	/**
	 * flag telling if the window needs to be updated
	 */
	bool needToBeUpdated;
	
public:

private:

public:

	/**
	 * default constructor
	 */
	Window();
	
	/**
	 * default destructor
	 */
	~Window();
	
};

#endif
