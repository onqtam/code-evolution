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

#ifndef WIND
#define WIND

#include <SDL.h>

using namespace std;

#define MAXWIND 150
#define UPDATE_INTERVAL 20

/**
 * Class for wind.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 22 Match 2010
 */
class Wind {
private:

	/**
	 * the current wind value
	 */
	static int wind;
	
	/**
	 * the maximum wind
	 */
	static int maxWind;
	
	/**
	 * the timer id for the timer, updating the wind
	 */
	SDL_TimerID timerId;
	
	/**
	 * the timer id of the debugging timer
	 */
	SDL_TimerID debugTimerId;
	
	/**
	 * the mutex, sunchronizating the access to the wind value
	 */
	SDL_mutex* mutex;
	
public:

	/**
	 * the update interval
	 */
	static int updateInterval;
	
private:

	/**
	 * the callback function, updating the wind value
	 * @param interval the interval between calls
	 * @param param some random params...
	 * @return the new interval
	 */
	static Uint32 updateWind(Uint32 interval, void *param);
	
	/**
	 * used for debugging wind
	 * @param interval the interval between calls
	 * @param param some random params...
	 * @return the new interval
	 */
	static Uint32 printWind(Uint32 interval, void *param);
	
public:

	/**
	 * default constructor
	 */
	Wind();
	
	/**
	 * default destructor
	 */
	~Wind();
	
	/**
	 * pauses the wind change
	 */
	void pause();
	
	/**
	 * resumes the wind change
	 */
	void resume();
	
	/**
	 * gets the direction of the wind
	 */
	int getWindDirection();
	
};

#endif
