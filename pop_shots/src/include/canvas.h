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

#ifndef CANVAS
#define CANVAS

#include <SDL.h>

/**
 * Class for canvases.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 21 Dec 2009
 */
class Canvas {
private:

	/**
	 * surface of the canvas
	 */
	SDL_Surface* Surface;
	
private:

	/**
	* Converts the canvas
	*/
	void convertCanvas(void);
	
public:

	/**
	* Default constructor
	*/
	Canvas();
	
	/**
	* Default destructor
	*/
	~Canvas();
	
	/**
	* Sets the surface of the canvas
	* @param newSurface the new surface of the canvas
	*/
	void setCanvas(SDL_Surface* newSurface);
	
	/**
	* Gets a pointer to the surface of the canvas
	* @return surface pointer
	*/
	SDL_Surface* getCanvas() {
		return Surface;
	}
	
	/**
	* Gets the height of the canvas(surface)
	* @return height
	*/
	int getHeight() {
		return Surface->h;
	}
	
	/**
	* Gets the width of the canvas(surface)
	* @return width
	*/
	int getWidth() {
		return Surface->w;
	}
};

#endif
