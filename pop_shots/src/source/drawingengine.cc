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

#include <stdlib.h>

#include "../include/drawingengine.h"
#include "../include/engine.h"
#include "../include/funcs.h"

bool (* DrawingEngine::func_pointer) (layer_key,layer_key) = compKeys;

void DrawingEngine::swapBuffers() {
	/*
	 * swaps the 2 buffers (pointers) and clears the add buffer (used only for registering needs for updation)
	 * use buffer is used by the drawing engine to update all objects that should at a given time.
	 */
	SDL_mutexP(mutex);
	
	swapPointers(addBuffer,useBuffer);
	
	addBuffer->clear();
	
	SDL_mutexV(mutex);
}

bool DrawingEngine::inScreen(SDL_Rect& rect, int& posX, int& posY, SDL_Rect* temp, int* x, int* y) {
	static SDL_Rect camera;
	camera.x = 0;
	camera.y = 0;
	camera.w = Engine::engine->video.camera.getWidth();
	camera.h = Engine::engine->video.camera.getHeight();
	
	static int camX;
	camX = Engine::engine->video.camera.getX();
	static int camY;
	camY = Engine::engine->video.camera.getY();
	
	return sectionsOverlap(camera, camX, camY, rect, posX, posY, temp, x, y);
}

bool DrawingEngine::inScreen(SDL_Rect& rect) {
	return overlaps(*Engine::engine->video.camera.getRectArea(), rect, &rect);
}

void DrawingEngine::dumpRectsToMask() {
	SDL_Surface* temp = SDL_CreateRGBSurface(SDL_SWSURFACE, Engine::engine->video.Width, Engine::engine->video.Height, Engine::engine->video.Bpp, Engine::engine->video.Surface->format->Rmask, Engine::engine->video.Surface->format->Gmask, Engine::engine->video.Surface->format->Bmask, Engine::engine->video.Surface->format->Amask);
	
	//RANDOM COLOURED SIDES OF RECTANGLES
	for ( list<SDL_Rect>::iterator it = useBuffer->begin(); it != useBuffer->end(); it++ ) {
		SDL_Rect tempRect = *it;
		tempRect.x -= Engine::engine->video.camera.getX();
		tempRect.y -= Engine::engine->video.camera.getY();
		
		tempRect.w = 1;
		
		int red = rand() % 255;
		int green = rand() % 255;
		int blue = rand() % 255;
		
		SDL_FillRect(temp, &tempRect, SDL_MapRGB(Engine::engine->video.GetPixelFormat(), red, green, blue) );
		
		tempRect.x += it->w - 1;
		
		SDL_FillRect(temp, &tempRect, SDL_MapRGB(Engine::engine->video.GetPixelFormat(), red, green, blue) );
		
		tempRect.x = it->x;
		tempRect.w = it->w;
		
		tempRect.h = 1;
		
		SDL_FillRect(temp, &tempRect, SDL_MapRGB(Engine::engine->video.GetPixelFormat(), red, green, blue) );
		
		tempRect.y += it->h - 1;
		
		SDL_FillRect(temp, &tempRect, SDL_MapRGB(Engine::engine->video.GetPixelFormat(), red, green, blue) );
	}
	
	/*
	//RANDOM COLOURED RECTANGLES
	for ( list<SDL_Rect>::iterator it = useBuffer->begin(); it != useBuffer->end(); it++ )
	{
		SDL_Rect tempRect = *it;
		tempRect.x -= Engine::engine->video.camera.getX();
		tempRect.y -= Engine::engine->video.camera.getY();
	
		SDL_FillRect(temp, &tempRect, SDL_MapRGB(Engine::engine->video.GetPixelFormat(), rand() % 255, rand() % 255, rand() % 255) );
	}
	*/
	
	/*
	//RED GREEN AND BLUE RECTANGLES ONLY.
	for( list<SDL_Rect>::iterator it = useBuffer->begin(); it != useBuffer->end(); it++ )
	{
		SDL_Rect tempRect = *it;
		tempRect.x -= Engine::engine->video.camera.getX();
		tempRect.y -= Engine::engine->video.camera.getY();
	
		if( tempRect.w > 2 && tempRect.h > 2 )
		{
			SDL_FillRect(temp, &tempRect, SDL_MapRGB(Engine::engine->video.GetPixelFormat(), 0, 255, 0) );
	
			tempRect.w -= 2;
			tempRect.h -= 2;
			tempRect.x += 1;
			tempRect.y += 1;
	
			SDL_FillRect(temp, &tempRect, SDL_MapRGB(Engine::engine->video.GetPixelFormat(), 255, 0, 0) );
	
		}
		else
		{
			SDL_FillRect(temp, &tempRect, SDL_MapRGB(Engine::engine->video.GetPixelFormat(), 0, 0, 255) );
		}
	}
	*/
	
	char filename[20];
	static int i=0;
	i++;
	sprintf(filename, "%d.bmp", i);
	
	SDL_SaveBMP(temp,filename);
	
	SDL_FreeSurface(temp);
}

DrawingEngine::DrawingEngine() :
		addBuffer (&marked_1),
		useBuffer (&marked_2),
		mutex (SDL_CreateMutex()) {
		
}

DrawingEngine::~DrawingEngine() {

}

void DrawingEngine::addToList(int x, int y, int w, int h) {
	SDL_mutexP(mutex);
	
	if ( not Engine::engine->video.camera.moved ) {
		SDL_Rect temp = {x ,y ,w ,h };
		
		if ( inScreen(temp) ) {
			list<SDL_Rect> tempRects;
			tempRects.push_back(temp);
			
			for ( list<SDL_Rect>::iterator tempIt = tempRects.begin(); tempIt != tempRects.end(); tempIt++ ) {
				for ( list<SDL_Rect>::iterator dirtyIt = addBuffer->begin(); dirtyIt != addBuffer->end(); dirtyIt++ ) {
					if ( overlap_true_false( *tempIt, *dirtyIt ) ) {
						/*
						 * make little rects and push_back to tempRects, after which erase overlapped region from tempRects
						 */
						
						/*
						 * rectangle from temporary above overlapping area between temporary and dirty becomes a new rectangle, added to temporay.
						 */
						if ( (dirtyIt->y + dirtyIt->h) < (tempIt->y + tempIt->h) ) {
							temp=makeRect(tempIt->x, dirtyIt->y + dirtyIt->h, tempIt->w, (tempIt->y + tempIt->h) - (dirtyIt->y + dirtyIt->h));
							tempRects.push_back( temp );
							
							tempIt->h -= (tempIt->y + tempIt->h) - (dirtyIt->y + dirtyIt->h);
						}
						
						/*
						 * rectangle from temporary below overlapping area between temporary and dirty becomes a new rectangle, added to temporay.
						 */
						if ( tempIt->y < dirtyIt->y ) {
							temp=makeRect(tempIt->x, tempIt->y, tempIt->w, dirtyIt->y - tempIt->y);
							tempRects.push_back( temp );
							
							tempIt->h -= dirtyIt->y - tempIt->y;
							tempIt->y = dirtyIt->y;
						}
						
						/*
						 * rectangle from temporary on the right of overlapping area between temporary and dirty becomes a new rectangle, added to temporay.
						 */
						if ( tempIt->x + tempIt->w > dirtyIt->x + dirtyIt->w ) {
							temp=makeRect(dirtyIt->x + dirtyIt->w, tempIt->y, (tempIt->x + tempIt->w) - (dirtyIt->x + dirtyIt->w), tempIt->h);
							tempRects.push_back( temp );
							
							tempIt->w -= (tempIt->x + tempIt->w) - (dirtyIt->x + dirtyIt->w);
						}
						
						/*
						 * rectangle from temporary on the left of overlapping area between temporary and dirty becomes a new rectangle, added to temporay.
						 */
						if ( tempIt->x < dirtyIt->x ) {
							temp=makeRect(tempIt->x, tempIt->y, dirtyIt->x - tempIt->x, tempIt->h);
							tempRects.push_back( temp );
							
							tempIt->w -= dirtyIt->x - tempIt->x;
							tempIt->x = dirtyIt->x;
						}
						
						tempIt = tempRects.erase(tempIt);
						break;
					}
				}
			}
			
			for ( list<SDL_Rect>::iterator tempIt = tempRects.begin(); tempIt != tempRects.end(); tempIt++ ) {
				addBuffer->push_back(*tempIt);
			}
		}
	}
	
	SDL_mutexV(mutex);
}

void DrawingEngine::redraw() {
	swapBuffers();
	
	/*
	 * if camera moved, make a dirtyRect with the camera's area
	 */
	if ( Engine::engine->video.camera.moved ) {
		useBuffer->clear();
		useBuffer->push_back( *Engine::engine->video.camera.getRectArea() );
	}
	
	if ( useBuffer->size() > 0 ) {
		/*
		 * FOR DEBUGGING DIRTY RECTANGLES
		 */
		//dumpRectsToMask();
	}
	
	map<layer_key, drawInfo, bool(*)(layer_key,layer_key)> objectMap( func_pointer );
	
	for ( list<SDL_Rect>::iterator dirtyIt = useBuffer->begin(); dirtyIt != useBuffer->end(); dirtyIt++ ) {
		/*
		 * find all objects in section
		 */
		
		for ( list<Object*>::iterator objIt = ObjectManager::visibleObjects.begin(); objIt != ObjectManager::visibleObjects.end(); objIt++ ) {
			drawInfo tempInfo = {*objIt, ((Animation*)*objIt)->getCurrentFrame(), (*objIt)->getX(), (*objIt)->getY()};
			
			if ( sectionsOverlap( *dirtyIt, (int)dirtyIt->x, (int)dirtyIt->y, tempInfo.area, tempInfo.posX, tempInfo.posY, &tempInfo.area, &tempInfo.posX, &tempInfo.posY) ) {
				layer_key tempKey = { (*objIt)->getLayerId(), *objIt };
				objectMap.insert( pair<layer_key, drawInfo> ( tempKey, tempInfo) );
			}
		}
		
		/*
		 * draw all objects in section
		 */
		
		help_rect1 = (*dirtyIt);
		help_rect2 = (*dirtyIt);
		
		help_rect1.x -= Engine::engine->video.camera.getX();
		help_rect1.y = Engine::engine->video.camera.getHeight() - ( help_rect1.h + (help_rect1.y - Engine::engine->video.camera.getY()) );
		
		help_rect2.y =  Engine::engine->logic.level.getHeight() - ( help_rect2.y + help_rect2.h );
		
		/*
		 * blit some background... TODO REPLACE THIS METHOD WITH SMARTER ONE
		 */
		
		SDL_FillRect( Engine::engine->video.Surface, &help_rect1, SDL_MapRGB(Engine::engine->video.Surface->format, 255, 255, 255) );
		
		SDL_BlitSurface(Engine::engine->logic.level.getSurface(), &help_rect2, Engine::engine->video.Surface, &help_rect1);
		
		for ( map<layer_key, drawInfo, bool(*)(layer_key,layer_key)>::iterator infoIt = objectMap.begin(); infoIt != objectMap.end(); infoIt++ ) {
			help_rect1.x = infoIt->second.posX - Engine::engine->video.camera.getX();
			help_rect1.y = Engine::engine->video.camera.getHeight() - infoIt->second.area.h - ( infoIt->second.posY - Engine::engine->video.camera.getY() );
			help_rect1.w = infoIt->second.area.w;
			help_rect1.h = infoIt->second.area.h;
			
			SDL_BlitSurface( ((Animation*)infoIt->second.obj)->getTexture()->getTexture(), &infoIt->second.area, Engine::engine->video.Surface, &help_rect1);
		}
		
		objectMap.clear();
	}
	
	/*
	 * update screen
	 */
	
	for ( list<SDL_Rect>::iterator dirtyIt = useBuffer->begin(); dirtyIt != useBuffer->end(); dirtyIt++ ) {
		SDL_UpdateRect( Engine::engine->video.Surface, dirtyIt->x - Engine::engine->video.camera.getX(), Engine::engine->video.camera.getHeight() - ( dirtyIt->h + (dirtyIt->y - Engine::engine->video.camera.getY()) ) , dirtyIt->w, dirtyIt->h );
	}
	
	/*
	 * cleanup
	 */
	
	useBuffer->clear();
	
}

void DrawingEngine::redrawLevel() {
	/*
	 * direct blit of the oprtion of the level on the screen's surface
	 */
	SDL_BlitSurface(Engine::engine->logic.level.getSurface(), Engine::engine->video.camera.getRectAreaInverse(), Engine::engine->video.Surface, NULL);
}
