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

#ifndef ANIMATION
#define ANIMATION

#include <list>
#include <string>
#include <vector>
#include <SDL.h>

#include "texture.h"
#include "types.h"
#include "object.h"

using namespace std;

/**
 * Class for animating objects.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 21 Dec 2009
 */
class Animation : public Object {
	/**
	 * For access to everything.
	 */
	friend class DrawingEngine;
	
	/**
	 * For access to everything.
	 */
	friend class PhysicalObject;
	
protected:

	/**
	 * holds all the frames
	 */
	vector<SDL_Rect> frames;
	
	/**
	 * holds a pointer to the animation's texture
	 */
	Texture* texture;
	
	/**
	 * holds the current frame index
	 */
	int currentIndex;
	
	/**
	 * holds the id of the timer, assiciaed with the animation
	 */
	SDL_TimerID timerId;
	
	/**
	 * holds the delay between the frames
	 */
	Uint32 delay;
	
private:

	/**
	 * Callback function for animations' timers
	 * @param interval the interval of the timer
	 * @param param parameters (in void*)
	 * @return new interval of the timer
	 */
	static Uint32 updateAnimation(Uint32 interval, void *param);
	
	/**
	 * Calculates the frames (and fills the frames container)
	 * @return whether calculation was successful or not
	 */
	bool calculateFrames();
	
protected:

	/**
	 * Gets a pointer to the animation's texture
	 */
	Texture* getTexture();
	
public:

	/**
	 * Constructor
	 * @param text texture of the animation
	 * @param dly delay between frames
	 * @param X position x of the object(animated object)
	 * @param Y position Y of the object(animated object)
	 * @param h height of each frame (used by calculateFrames())
	 * @param w width of each frame (used by calculateFrames())
	 */
	Animation(string name, Uint32 dly = 0, float X = 0, float Y = 0, int h = 0, int w = 0, int layer = raster_object);
	
	/**
	 * Default destructor
	 */
	~Animation();
	
	/**
	 * Gets the area on the texture associated with the current frame
	 * @return rectangle
	 */
	SDL_Rect getCurrentFrame(void);
	
	/**
	 * Sets the delay between frames
	 * @param newDelay the new delay between frames
	 */
	void setDelay(Uint32 newDelay);
	
	/**
	 * Gets the delay between frames
	 * @return the delay
	 */
	Uint32 getDelay();
	
	/**
	 * Pauses the animation
	 */
	void pause(void);
	
	/**
	 * Resumes the animation
	 */
	void resume(void);
	
	/**
	 * Gets the index of the current frame
	 * @return index
	 */
	int getIndexOfCurrentFrame();
	
	/**
	 * Sets the width of each frame (and causes calculateFrames() to be executed)
	 * @param w the width
	 */
	void setWidth(int w);
	
	/**
	 * Sets the height of each frame (and causes calculateFrames() to be executed)
	 * @param h the height
	 */
	void setHeight(int h);
	
};

#endif
