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

#include "../include/array2d.h"

void Array2d::freeArray() {
	if ( data!= NULL ) {
		for ( int i = 0; i < height; i++ ) {
			delete [] data[i];
		}
		
		delete data;
		
		data = NULL;
	}
}

Array2d::Array2d() :
		width(0),
		height(0),
		data(NULL) {
		
}

Array2d::Array2d(int w, int h) :
		width(w),
		height(h),
		data(NULL) {
	resizeArray(w, h);
}

Array2d::~Array2d() {
	freeArray();
}

void Array2d::resizeArray(int w, int h) {
	if ( !( w <= 0 || h <= 0 ) ) {
		freeArray();
		
		data = new Uint8 * [h];
		
		for ( int i = 0; i < h; i++ ) {
			data[i] = new Uint8 [w];
		}
	}
}
