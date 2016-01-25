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

#ifndef FONTMANAGER
#define FONTMANAGER

#include "types.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <map>
#include <vector>
#include <string>

using namespace std;

/**
 * Class for managing fonts
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 21 Dec 2009
 */
class FontManager {
private:

	/**
	 * holds all currently loaded fonts, associated with a filename
	 */
	map<string , vector<TTF_Font*> > fonts;
	
public:

private:

public:

	/**
	 * default constructor
	 */
	FontManager();
	
	/**
	 * default destructor
	 */
	~FontManager();
	
	/**
	 * gets a desired font
	 * @param fontName the name of the font
	 * @param size the height of the font
	 * @return a pointer to a TTF_Font
	 */
	TTF_Font* getFont(string fontName, int size);
	
};

#endif
