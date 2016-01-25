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

#ifndef COLLISION
#define COLLISION

#include <SDL.h>

using namespace std;

/**
 * Class for holding collisions
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 22 Match 2010
 */
class Collision {
	/**
	 * for access to everything
	 */
	friend class CollisionManager;
	
	/**
	 * for access to everything
	 */
	friend class Physics;
	
	/**
	 * for access to everything
	 */
	friend bool CheckCollision(Collision *col, int x, int y, Collision *col2, int x2, int y2, int skip);
	
private:

	/**
	 * the data of the collision
	 */
	Uint8 **mask;
	
	/**
	 * the width of the collision
	 */
	int w;
	
	/**
	 * the height of the collision
	 */
	int h;
	
public:

private:

	/**
	 * for freeing the dynamically allocated memory
	 */
	void freeCollision();
	
public:

	/**
	 * default constructor
	 */
	Collision();
	
	/**
	 * constructor with parameter
	 * @param srf a surface from which to make the collision
	 */
	Collision(SDL_Surface *srf);
	
	/**
	 * default destructor
	 */
	~Collision();
	
	/**
	 * for setting a new collision
	 * @param srf the surface from which to make the collision
	 * @return true on success
	 */
	bool set(SDL_Surface *srf);
	
	/**
	 * for updating a part of the collision
	 * @param srf the changed surface
	 * @param area the area to be updated
	 */
	void updateCollision(SDL_Surface* srf, SDL_Rect area);
	
	/**
	 * for setting a rectangular area of the collision with a certain value
	 * @param X the x
	 * @param Y the y
	 * @param W the width
	 * @param H the height
	 * @param value the value for setting
	 */
	void setRect(int X, int Y, int W, int H, int value);
};

/**
 * for bounding box collision checking
 * @param x the x of the first area
 * @param y the y of the first area
 * @param w the width of the first area
 * @param h the height of the first area
 * @param x2 the x of the second area
 * @param y2 the y of the second area
 * @param w2 the width of the second area
 * @param h2 the height of the second area
 * @return true on collision
 */
bool CheckCollision(int x, int y, int w, int h, int x2, int y2, int w2, int h2);

/**
 * for per-pixel collision checking
 * @param col the first collision
 * @param x the x pos of the first collision
 * @param y the y pos of the first collision
 * @param col2 the second collision
 * @param x2 the y pos of the second collision
 * @param y2 the y pos of the second collision
 * @param skip the step for checking(bigger skip means more pixels skipping the check)
 * @return true on collision
 */
bool CheckCollision(Collision *col, int x, int y, Collision *col2, int x2, int y2, int skip=1);

#endif
