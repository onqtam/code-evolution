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

#include "../include/collisionmanager.h"
#include "../include/funcs.h"

map<string, collisionMapEntry> CollisionManager::collisionData;

bool CollisionManager::calculateFrames(vector<Collision*>* collisions, Texture* texture, int width, int height) {
	if ( (width == 0) || (height == 0) ) {
		return false;
	}
	
	SDL_Surface* temp = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, texture->getTexture()->format->BitsPerPixel, texture->getTexture()->format->Rmask, texture->getTexture()->format->Gmask, texture->getTexture()->format->Bmask, texture->getTexture()->format->Amask);
	
	int rows = (texture->getHeight() / height);
	int columns = (texture->getWidth() / width);
	
	
	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < columns; k++) {
			SDL_Rect opa = makeRect(k*width, i*height, width, height);
			SDL_BlitSurface(texture->getTexture(), &opa, temp, NULL);
			collisions->push_back( new Collision(temp) );
		}
	}
	
	SDL_FreeSurface(temp);
	
	return true;
}

vector<Collision*>* CollisionManager::getCollisions(string collisionFilename, int width, int height) {
	map<string, collisionMapEntry>::iterator it = CollisionManager::collisionData.find(collisionFilename);
	
	if ( it != CollisionManager::collisionData.end() ) {
		it->second.referenceCount++;
		return &it->second.collisions;
	} else {
		Texture* tempTexture = new Texture(collisionFilename);
		collisionMapEntry a;
		a.referenceCount = 1;
		
		collisionData.insert( pair<string,collisionMapEntry> (collisionFilename, a) );
		
		calculateFrames( &(collisionData[collisionFilename].collisions), tempTexture, width, height );
		
		delete tempTexture;
		
		return &collisionData[collisionFilename].collisions;
	}
	
}

void CollisionManager::ungetCollisions(string collisionFilename) {
	map<string, collisionMapEntry>::iterator it = CollisionManager::collisionData.find(collisionFilename);
	
	if ( it == CollisionManager::collisionData.end() ) {
		fprintf(stderr, "Could not find collision with filename %s...\n", collisionFilename.c_str());
	} else {
		if ( (--it->second.referenceCount) == 0 ) {
			for ( unsigned int i = 0; i < it->second.collisions.size(); i++ ) {
				delete it->second.collisions[i];
			}
			
			CollisionManager::collisionData.erase(it);
		}
	}
}
