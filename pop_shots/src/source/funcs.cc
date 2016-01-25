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

#include "../include/funcs.h"
#include "../include/engine.h"

bool compKeys(layer_key key1, layer_key key2) {
	if ( key1.layer < key2.layer ) {
		return true;
	}
	if ( key1.layer > key2.layer ) {
		return false;
	}
	return (key1.address < key2.address);
}

SDL_Rect makeRect(int x, int y, int w, int h) {
	SDL_Rect out={x,y,w,h};
	return out;
}

SDL_Color makeColor(int red, int green, int blue, int alpha) {
	SDL_Color out = {red, green, blue, alpha};
	return out;
}

Point2d makePoint2d(int x, int y) {
	Point2d out(x,y);
	return out;
}

Velocity makeVelocity(float x, float y) {
	Velocity out(x,y);
	return out;
}

Explosion makeExplosion(float x, float y, float radius) {
	Explosion out = {x, y, radius};
	return out;
}

int normalizeCoordY(int oldY, int itemHeight) {
	/*
	 * inverts the Y coordinate
	 */
	return Engine::engine->logic.level.getHeight() - itemHeight - oldY;
}

bool sectionsOverlap(SDL_Rect &area1, int x1, int y1, SDL_Rect &area2, int &x2, int &y2, SDL_Rect* areaNew, int* xNew, int* yNew) {
	(*xNew) = x2;
	(*yNew) = y2;
	(*areaNew) = area2;
	
	if ( ( y1 < y2 + area2.h ) && ( x1 < x2 + area2.w ) ) {
		/*
		 * y coord
		 */
		if ( y2 < y1 + area1.h ) {
			if ( y1 + area1.h < y2 + area2.h ) {
				/*
				 * because SDL's vertical coordination is inverted
				 */
				areaNew->y += ( y2 + area2.h ) - ( y1 + area1.h );
				
				areaNew->h = area2.h - ( ( y2 + area2.h ) - ( y1 + area1.h ) );
			}
			if ( y1 > y2 ) {
				/*
				 * things like
				 * areaNew->y += y1 - y2;
				 * are not needed because SDL's vertical coordination is inverted
				 */
				areaNew->h -= y1 - y2;
				(*yNew) = y1;
			}
		} else {
			return false;
		}
		
		/*
		 * x coord
		 */
		if ( x2 < x1 + area1.w ) {
			if ( x2 + area2.w > x1+ area1.w ) {
				areaNew->w = area2.w - ( ( x2 + area2.w ) - ( x1 + area1.w ) );
			}
			if ( x2 < x1 ) {
				areaNew->x += x1 - x2;
				areaNew->w -= x1 - x2;
				(*xNew) = x1;
			}
		} else {
			return false;
		}
	} else {
		return false;
	}
	
	return true;
}

bool overlaps(SDL_Rect &area1, SDL_Rect &area2, SDL_Rect* areaNew) {
	(*areaNew) = area2;
	
	if ( ( area1.y < area2.y + area2.h ) && ( area1.x < area2.x + area2.w ) ) {
		/*
		 * y coord
		 */
		if ( area2.y < area1.y + area1.h ) {
			if ( area1.y + area1.h < area2.y + area2.h ) {
				areaNew->h -= (area2.y + area2.h) - (area1.y + area1.h);
			}
			if ( area1.y > area2.y ) {
				areaNew->h -= area1.y - area2.y;
				areaNew->y = area1.y;
			}
		} else {
			return false;
		}
		
		/*
		 * x coord
		 */
		if ( area2.x < area1.x + area1.w ) {
			if ( area2.x + area2.w > area1.x+ area1.w ) {
				areaNew->w -= (area2.x + area2.w) - (area1.x + area1.w);
			}
			if ( area2.x < area1.x ) {
				areaNew->w -= area1.x - area2.x;
				areaNew->x = area1.x;
			}
		} else {
			return false;
		}
	} else {
		return false;
	}
	
	return true;
}

bool overlap_true_false(SDL_Rect area1, SDL_Rect area2) {
	if ( ( area1.y < area2.y + area2.h ) && ( area1.x < area2.x + area2.w ) ) {
		if ( not (area2.y < area1.y + area1.h) ) {
			return false;
		}
		
		if ( not (area2.x < area1.x + area1.w) ) {
			return false;
		}
	} else {
		return false;
	}
	
	return true;
}

Uint32 GetPixel(SDL_Surface *srf, int x, int y) {
	if (x < 0 || y < 0 || x >= srf->w || y >= srf->h) {
		return 0;
	}
	
	int bpp=srf->format->BitsPerPixel;
	
	if (bpp == 32) {
		Uint32 *pixels=(Uint32 *)srf->pixels+y*srf->w+x;
		return *pixels;
	}
	if (bpp == 16) {
		Uint16 *pixels=(Uint16 *)srf->pixels+y*srf->w+x;
		return *pixels;
	}
	if (bpp == 8) {
		Uint8 *pixels=(Uint8 *)srf->pixels+y*srf->w+x;
		return *pixels;
	}
	
	return 0;
}

void drawPixel(SDL_Surface* surface, int x, int y, unsigned int r, unsigned int g, unsigned int b) {
	Uint32 Color = SDL_MapRGB(surface->format,r,g,b);
	char* pointer = (char*)surface->pixels;
	
	pointer += ( (surface->h - y - 1) * surface->pitch );
	pointer += (x*surface->format->BytesPerPixel);
	
	memcpy(pointer,&Color,surface->format->BytesPerPixel);
}
