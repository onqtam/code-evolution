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

#ifndef DRAWINGENGINE
#define DRAWINGENGINE

#include "animation.h"
#include "object.h"
#include "types.h"

#include <SDL.h>

#include <map>

using namespace std;

/**
 * Class for handling all drawing.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 21 Dec 2009
 */
class DrawingEngine {
	/**
	 * for access to everything
	 */
	friend class Core;
	
private:

	/**
	 * function pointer to a compare function for buffers (containers)
	 */
	static bool(*func_pointer)(layer_key, layer_key);
	
	/**
	 * one of the containers pointed by one of the above pointers
	 */
	list<SDL_Rect> marked_1;
	
	/**
	 * another of the containers pointed by one of the above pointers
	 */
	list<SDL_Rect> marked_2;
	
	/**
	 * buffer used to contain all newly registered objects' information about their updation
	 */
	list<SDL_Rect>* addBuffer;
	
	/**
	 * buffer used to contain information about all objects that are currently being updated
	 */
	list<SDL_Rect>* useBuffer;
	
	/**
	 * a rectangle used for blitting
	 */
	SDL_Rect help_rect1;
	
	/**
	 * a rectangle used for blitting
	 */
	SDL_Rect help_rect2;
	
	/**
	 * a mutex for managing multithreaded synchronisation
	 */
	SDL_mutex* mutex;
	
public:

private:

	/**
	* swaps the addBuffer and useBuffer
	*/
	void swapBuffers();
	
	/**
	* Checks if an area is in the screen
	* @param rect the area to be checked
	* @param posX the x pos of the area
	* @param posY the y pos of the area
	* @param temp the new area(the only overlapping area). used for returning
	* @param x the new pos x. used for returning
	* @param y the new pos y. used for returning
	* @return whether the area is in screen or not
	*/
	bool inScreen(SDL_Rect& rect, int& posX, int& posY, SDL_Rect* temp, int* x, int* y);
	
	/**
	* Checks if an area is in the screen
	* @param rect area to check if it is in screen
	* @return whether the area is in screen or not
	*/
	bool inScreen(SDL_Rect& rect);
	
	/**
	* writes all the current dirty rectangles to a .bmp image for debugging purposes
	*/
	void dumpRectsToMask();
	
public:

	/**
	* Default constructor
	*/
	DrawingEngine();
	
	/**
	* Default destructor
	*/
	~DrawingEngine();
	
	/**
	* Adds an area to addList
	* @param x the x pos of the area
	* @param y the y pos of the area
	* @param w the width of the area
	* @param h the height of the area
	*/
	void addToList(int x, int y, int w, int h);
	
	/**
	* redraws all (it handles the way everything is redrawn)
	*/
	void redraw();
	
	/**
	* redraws the level
	*/
	void redrawLevel();
};

#endif
