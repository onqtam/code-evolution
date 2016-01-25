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

#include "../include/texture.h"
#include <SDL_image.h>

Texture::Texture(std::string newFilename) :
		texture(NULL) {
	if ( newFilename != "" ) {
		loadTexture(newFilename);
	}
}

Texture::~Texture() {
	if (texture != NULL) {
		deleteTexture();
	}
}

void Texture::deleteTexture() {
	SDL_FreeSurface(texture);
	texture=NULL;
	filename = "";
}

SDL_Surface* Texture::loadTexture(std::string newFilename) {
	if (texture != NULL) {
		deleteTexture();
	}
	
	/*
	 * all textures' surfaces should match the format of the display for fast and proper blitting & usage.
	 */
	texture = SDL_DisplayFormat(IMG_Load(newFilename.c_str()));
	
	filename = newFilename;
	
	return texture;
}
