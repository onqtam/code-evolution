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

#include "../include/texturemanager.h"
#include "../include/engine.h"

map<string, mapEntry> TextureManager::textureData;

const color TextureManager::transparent = {240,240,240};

Texture* TextureManager::getTexture(string texturePath) {
	if ( texturePath == "" ) {
		return NULL;
	}
	
	map<string, mapEntry>::iterator it = TextureManager::textureData.find(texturePath);
	
	if ( it != TextureManager::textureData.end() ) {
		it->second.referenceCount++;
		return it->second.texture;
	} else {
		struct mapEntry a;
		a.referenceCount = 1;
		a.texture = new Texture(texturePath);
		
		/*
		 * sets the colorkey.
		 */
		SDL_SetColorKey(a.texture->getTexture(), SDL_SRCCOLORKEY, SDL_MapRGB(Engine::engine->video.GetPixelFormat(), transparent.red, transparent.green, transparent.blue));
		
		textureData[texturePath] = a;
		
		return TextureManager::textureData[texturePath].texture;
	}
}

void TextureManager::ungetTexture(string texturePath) {
	if ( texturePath == "" ) {
		return;
	}
	
	map<string, mapEntry>::iterator it = TextureManager::textureData.find(texturePath);
	
	if ( it == TextureManager::textureData.end() ) {
	
	} else {
		if ( (--it->second.referenceCount) == 0 ) {
			delete it->second.texture;
			
			TextureManager::textureData.erase(it);
		} else {
		
		}
	}
}

