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

#include "../include/collision.h"
#include "../include/texturemanager.h"
#include "../include/funcs.h"
#include "../include/types.h"

void Collision::freeCollision() {
	if ( mask != NULL ) {
		for (int a=0; a < w; a++) {
			delete [] mask[a];
		}
		
		delete [] mask;
		
		mask = NULL;
	}
}

Collision::Collision() :
		mask(NULL),
		w(0),
		h(0) {
		
}

Collision::Collision(SDL_Surface *srf) :
		mask(NULL),
		w(0),
		h(0)

{
	set(srf);
}

Collision::~Collision() {
	freeCollision();
}

bool Collision::set(SDL_Surface *srf) {
	if (mask != NULL) {
		freeCollision();
	}
	
	if (!srf) {
		return 1;
	}
	
	w = srf->w;
	h = srf->h;
	mask=new Uint8 *[w];
	
	for (int a = 0; a < w; a++) {
		mask[a] = new Uint8 [h];
	}
	
	Uint32 col=SDL_MapRGB(srf->format,TextureManager::transparent.red,TextureManager::transparent.green,TextureManager::transparent.blue);
	
	for (int a = 0, b = 0; b < h; ) {
		if (GetPixel(srf, a, b) == col) {
			mask[a][h - b - 1]=0;
		} else {
			mask[a][h - b - 1]=1;
		}
		
		a++;
		
		if (a >= w) {
			a = 0;
			b++;
		}
	}
	
	return 0;
}

void Collision::updateCollision(SDL_Surface* srf, SDL_Rect area) {
	if ( mask == NULL ) {
		set(srf);
		
		return;
	}
	
	if (!srf) {
		return;
	}
	
	if ( w != srf->w || h != srf->h ) {
		set(srf);
		
		return;
	}
	
	Uint32 col=SDL_MapRGB(srf->format,TextureManager::transparent.red,TextureManager::transparent.green,TextureManager::transparent.blue);
	
	SDL_Rect temp = {0, 0, w, h};
	
	/*
	 * normalize the area (if needed) so we dont exceed the mask
	 */
	overlaps(temp, area, &area);
	
	for (int a = area.x, b = h - area.y - area.h; b < h - area.y; ) {
		if (GetPixel(srf, a, b) == col) {
			mask[a][h - b - 1]=0;
		}
		
		a++;
		
		if (a >= area.x + area.w) {
			a = area.x;
			b++;
		}
	}
}

void Collision::setRect(int X, int Y, int W, int H, int value) {
	if ( mask == NULL ) {
		return;
	}
	
	for ( int i=X; i<X+W && i >= 0 && i < w; i++ ) {
		for ( int k=Y; k<Y+H && k>=0 && k<h; k++ ) {
			mask[i][k]=value;
		}
	}
}

bool CheckCollision(int x, int y, int w, int h, int x2, int y2, int w2, int h2) {
	if (x+w <= x2 || y+h <= y2 || x >= x2+w2 || y >= y2+h2) {
		return 0;
	}
	return 1;
}

bool CheckCollision(Collision *col, int x, int y, Collision *col2, int x2, int y2, int skip) {
	if (!CheckCollision(x, y, col->w, col->h, x2, y2, col2->w, col2->h) ) {
		return 0;
	}
	
	int w=col->w;
	int h=col->h;
	int w2=col2->w;
	int h2=col2->h;
	
	int xe=x+w;
	int ye=y+h;
	int x2e=x2+w2;
	int y2e=y2+h2;
	
	int xstart=(x < x2) ? x2 : x;
	int xend=(xe < x2e) ? xe : x2e;
	int ystart=(y < y2) ? y2 : y;
	int yend=(ye < y2e) ? ye : y2e;
	
	for (int b=ystart; b < yend; b+=skip) {
		for (int a=xstart; a < xend; a+=skip) {
			if (col->mask[a-x][b-y] && col2->mask[a-x2][b-y2]) {
				return true;
			}
		}
	}
	
	return false;
}
