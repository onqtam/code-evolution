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

#ifndef WINDOWSYSTEM
#define WINDOWSYSTEM

#include "window.h"

#include <vector>

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
class WindowSystem {

	/**
	 * for access to everything
	 */
	friend class DrawingEngine;
	
private:

	/**
	 * holds all the windows
	 */
	vector<Window*> windows;
	
public:

private:

public:

	/**
	 * default constructor
	 */
	WindowSystem();
	
	/**
	 * default destructor
	 */
	~WindowSystem();
	
	/**
	 * used for registering a window
	 * @param wnd the new window to register
	 * @return the pointer to the window for immediate usage
	 */
	Window* registerWindow(Window* wnd);
	
};

#endif
