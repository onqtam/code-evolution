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

#ifndef ARRAY2D
#define ARRAY2D

#include <SDL.h>

using namespace std;

/**
 * Class for 2 dimentional dynamic arrays.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 22 Match 2010
 */
class Array2d {
private:

	/**
	 * holds the width of the array
	 */
	int width;
	
	/**
	 * holds the height of the array
	 */
	int height;
	
	/**
	 * holds the data of the array
	 */
	Uint8** data;
	
public:

private:

	/**
	 * function for freeing the dynamic memory
	 */
	void freeArray();
	
public:

	/**
	 * Default constructor
	 */
	Array2d();
	
	/**
	 * Constructor with parameters
	 * @param w the width of the array
	 * @param h the height of the array
	 */
	Array2d(int w, int h);
	
	/**
	 * Default destructor
	 */
	~Array2d();
	
	/**
	 * For resizing the array
	 * @param w the width of the desired new array
	 * @param h the height of the desired new array
	 */
	void resizeArray(int w, int h);
	
};

#endif
