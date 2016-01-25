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

#include "../include/explosionmanager.h"
#include "../include/texturemanager.h"

#include <stdio.h>
#include <SDL.h>

string ExplosionManager::textfile = "resources/explosions/list.lst";

ExplosionManager::ExplosionManager() {
	FILE* list = fopen(ExplosionManager::textfile.c_str(), "r");
	
	if ( list != NULL ) {
		char buffer[128];
		string temp;
		
		for (; fgets(buffer, 128, list) != NULL; ) {
			temp = "resources/explosions/";
			
			for ( int i = 0; buffer[i] != '\n'; i++ ) {
				temp += buffer[i];
			}
			
			explosionEntry entry;
			entry.texture = new Texture( temp );
			entry.radius = entry.texture->getWidth() / 2;
			
			SDL_SetColorKey(entry.texture->getTexture(), SDL_SRCCOLORKEY, SDL_MapRGB(entry.texture->getTexture()->format, 0, 0, 0));
			
			explosions.push_back(entry);
		}
		
		fclose(list);
	} else {
		fprintf(stderr, "Unable to open file %s with details about explosions.\n", ExplosionManager::textfile.c_str() );
	}
}

ExplosionManager::~ExplosionManager() {
	for ( vector<explosionEntry>::iterator it = explosions.begin(); it != explosions.end(); it++ ) {
		delete it->texture;
	}
}

Texture* ExplosionManager::getExplosion(float radius) {
	float temp=0;
	
	for ( unsigned int i = 0; i < explosions.size(); i++ ) {
		if ( explosions[i].radius == radius ) {
			return explosions[i].texture;
		}
		
		if ( explosions[i].radius < radius ) {
			if ( i == explosions.size() - 1 ) {
				return explosions[i].texture;
			}
		}
		
		if ( explosions[i].radius > radius ) {
			if ( i == 0 ) {
				return explosions[i].texture;
			} else {
				if ( explosions[i].radius -radius < radius - temp ) {
					return explosions[i].texture;
				} else {
					return explosions[i - 1].texture;
				}
			}
		}
		
		temp = explosions[i].radius;
	}
	
	fprintf(stderr, "no texture returned  (NULL)\n");
	return NULL;
}
