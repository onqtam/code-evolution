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

#ifndef CORE
#define CORE

#include <list>
#include <SDL.h>

#include "object.h"

using namespace std;

/**
 * Class for core operations of the engine.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 21 Dec 2009
 */
class Core {
	/**
	 * for access to running
	 */
	friend class Input;
	
private:

	/**
	 * holds current events (one by one)
	 */
	SDL_Event currEvent;
	
	/**
	 * shows whether the game loop is running or not
	 */
	bool running;
	
public:

	/**
	 * holds all events that occured in the last loop
	 */
	list<SDL_Event> events;
	
	/**
	 * holds the time for the last loop
	 */
	Uint32 last_loop_time;
	
public:

	/**
	* Default constructor
	*/
	Core();
	
	/**
	* Default destructor
	*/
	~Core();
	
	/**
	* Adds an event in SDL
	* @param ev event to be added
	*/
	void addEvent(SDL_Event ev);
	
	/**
	* clears all events from the events container
	*/
	void clearEvents();
	
	/**
	* handles all events
	*/
	void handleEvents();
	
	/**
	* main loop
	*/
	void loop();
};

#endif
