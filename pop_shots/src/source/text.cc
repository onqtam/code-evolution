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

#include "../include/text.h"
#include "../include/engine.h"

Text::Text(string txt, int posX, int posY, font_size fSize, text_alignment alignment, string fName, SDL_Color col) :
		Animation("", 0, 0, 0, 0, 0, text_object),
		fontSize(fSize),
		fontName(fName),
		fontColor(col) {
	texture = new Texture();
	
	if ( changeText(txt, fSize, fName, col) ) {
		x += posX;
		y += posY;
		
		align(alignment);
		
		toggleVisibility();
	}
}

Text::~Text() {
	delete texture;
}

void Text::align(text_alignment alignment) {
	switch (alignment) {
	case center:
	
		break;
	case center_top:
	
		y += getHeight()/2;
		
		break;
	case center_bottom:
	
		y -= getHeight()/2;
		
		break;
	case left_middle:
	
		x -= getWidth()/2;
		
		break;
	case right_middle:
	
		x += getWidth()/2;
		
		break;
	case left_bottom:
	
		x -= getWidth()/2;
		y -= getHeight()/2;
		
		break;
	case right_bottom:
	
		x += getWidth()/2;
		y -= getHeight()/2;
		
		break;
	case left_top:
	
		x -= getWidth()/2;
		y += getHeight()/2;
		
		break;
	case right_top:
	
		x += getWidth()/2;
		y += getHeight()/2;
		
		break;
	}
}

bool Text::changeText(string newText, int fSize, string fName, SDL_Color col) {
	if ( newText == "" ) {
		if ( texture->texture != NULL ) {
			texture->deleteTexture();
		}
		if ( visible ) {
			toggleVisibility();
		}
		
		return false;
	}
	
	int centerX = x + texture->getWidth()/2;
	int centerY = y + texture->getHeight()/2;
	
	text = newText;
	
	fontColor = col;
	
	if ( texture->texture != NULL ) {
		texture->deleteTexture();
	}
	
	texture->texture = TTF_RenderText_Solid(Engine::engine->fontmanager.getFont(fName, fSize),text.c_str(), fontColor);
	
	if ( texture->texture == NULL ) {
		fprintf(stderr, "Could not set text with font %s and size %d... Reverting...\n", fName.c_str(), fSize);
	} else {
		fontSize = fSize;
		fontName = fName;
	}
	
	x = centerX - texture->getWidth()/2;
	y = centerY - texture->getHeight()/2;
	
	setWidth(texture->getWidth());
	setHeight(texture->getHeight());
	
	Engine::engine->drawingengine.addToList((int)getX(), (int)getY(), (int)width, (int)height );
	
	return true;
}

bool Text::changeText(string newText) {
	if ( newText == "" ) {
		if ( texture->texture != NULL ) {
			texture->deleteTexture();
		}
		if ( visible ) {
			toggleVisibility();
		}
		
		return false;
	}
	
	int centerX = x + texture->getWidth()/2;
	int centerY = y + texture->getHeight()/2;
	
	text = newText;
	
	if ( texture->texture != NULL ) {
		texture->deleteTexture();
	}
	
	texture->texture = TTF_RenderText_Solid(Engine::engine->fontmanager.getFont(fontName, fontSize),text.c_str(), fontColor);
	
	x = centerX - texture->getWidth()/2;
	y = centerY - texture->getHeight()/2;
	
	setWidth(texture->getWidth());
	setHeight(texture->getHeight());
	
	Engine::engine->drawingengine.addToList((int)getX(), (int)getY(), (int)width, (int)height );
	
	return true;
}

string Text::getText() {
	return text;
}
