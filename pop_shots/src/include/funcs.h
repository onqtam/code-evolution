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

#ifndef FUNCS
#define FUNCS

#include <list>
#include <stdio.h>
#include <SDL.h>

#include "point2d.h"
#include "velocity.h"
#include "types.h"

#include "debug.h"

using namespace std;

/**
 * compares 2 keys with type layer_key
 * @param key1 first key to compare
 * @param key2 second key to compare
 * @return true if key1 > key2
 */
bool compKeys(layer_key key1, layer_key key2);

/**
 * Makes a recatangle
 * @param x X of rectangle
 * @param y Y of rectangle
 * @param h H of rectangle
 * @param w W of rectangle
 * @return rectangle structure
 */
SDL_Rect makeRect(int x, int y, int w, int h);

/**
 * returns the absolute of a number
 * @param number the number
 * @return the absolute value
 */
inline float absolute(float number) {
	if ( number < 0 ) {
		return number * (-1);
	}
	return number;
}

/**
 * rounds a float to an int
 * @param number the number to round
 * @return the rounded value
 */
inline int round_float(float number) {
	return (int)(number + 0.5f);
}

/**
 * returns the sign of a number (1 or -1)
 * @param number the number
 * @return the sign
 */
inline int sign(float number) {
	if ( number < 0 ) {
		return -1;
	}
	
	return 1;
}

/**
 * rounds a number to the nearest bigger integer
 * @param number the number to round
 * @return the rounded value
 */
inline int roundToNearestBiggerInt(float number) {
	if ( number != (int)number) {
		return (int)(number + 1);
	}
	
	return (int)number;
}

/**
 * makes an SDL_Color struct
 * @param red the ammount of red
 * @param green the ammount of green
 * @param blue the ammount of blue
 * @param alpha the ammount of alpha
 * @return the struct
 */
SDL_Color makeColor(int red, int green, int blue, int alpha = 0);

/**
 * makes a 2d point structure
 * @param x the x of the point
 * @param y the y of the point
 * @return the 2dpoint
 */
Point2d makePoint2d(int x, int y);

/**
 * makes a velocity structure
 * @param x the x of the velocity
 * @param t the y of the velocity
 * @return the velocity object
 */
Velocity makeVelocity(float x, float y);

/**
 * makes and explosion structure
 * @param x the x of the explosion epicenter
 * @param y the y of the explosion epicenter
 * @param radius the radius of the xplosion
 * @return the struct
 */
Explosion makeExplosion(float x, float y, float radius);

/**
 * Normalizes the Y coord of an object judging on its position and height
 * @param oldY current Y position
 * @param itemHeight height of object
 * @return new Y coord
 */
int normalizeCoordY(int oldY, int itemHeight);

/**
 * tells if 2 sections of 2 areas overlap and returns the overlapped section of the area
 * @param area1 the first area
 * @param x1 the x of the first area
 * @param y1 the y of the first area
 * @param area2 the second area
 * @param x2 the x of the second area
 * @param y2 the y of the second area
 * @param areaNew the new area
 * @param xNew the x of the new area
 * @param yNew the y of the new area
 * @return true/false
 */
bool sectionsOverlap(SDL_Rect &area1, int x1, int y1, SDL_Rect &area2, int &x2, int &y2, SDL_Rect* areaNew, int* xNew, int* yNew);

/**
 * tells if 2 areas overlap and makes a new area, representing the overlapped region (if any)
 * @param area1 the first area
 * @param area2 the second area
 * @param areaNew the new area
 * @return true/false depending if the 2 areas overlap or not
 */
bool overlaps(SDL_Rect &area1, SDL_Rect &area2, SDL_Rect* areaNew);

/**
 * tells if 2 areas overlap
 * @param area1 the first area
 * @param area2 the second area
 * @return whether they overlap or not (true/false)
 */
bool overlap_true_false(SDL_Rect area1, SDL_Rect area2);

/**
 * gets a pixel from a given surface at a given position
 * @param srf the surface to take the pixel from
 * @param x the x of the pixel
 * @param y the y of the pixel
 * @return the color
 */
Uint32 GetPixel(SDL_Surface *srf, int x, int y);

/**
 * draws a pixel to a given surface
 * @param surface the surface to draw to
 * @param x the x pos of the desired new pixel
 * @param y the y pos of the desired new pixel
 * @param r the ammount of red
 * @param g the ammount of green
 * @param b the ammount of blue
 */
void drawPixel(SDL_Surface* surface, int x, int y, unsigned int r, unsigned int g, unsigned int b);

/**
 * Finds an item in a list and returns an iterator pointing to it
 * @param aList a list to search in
 * @param object an object to search for
 * @return iterator pointing to the found element
 */
template <typename T>
typename list<T*>::iterator findItemInList(list<T*>& aList, T* object) {

	typename list<T*>::iterator it;
	
	for (it=aList.begin(); it!=aList.end(); it++) {
		if ((*it) == object) {
			return it;
		}
	}
	
	fprintf(stderr,"Element not found! returning end() iterator...\n");
	return aList.end();
}

/**
 * swaps 2 pointers
 * @param pointer1 first pointer
 * @param pointer2 second pointer
 */
template <class T>
void swapPointers(T* &pointer1,T* &pointer2) {
	T* temp=pointer1;
	pointer1=pointer2;
	pointer2=temp;
}

#endif
