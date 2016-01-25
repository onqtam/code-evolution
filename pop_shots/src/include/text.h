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

#ifndef TEXT
#define TEXT

#include <SDL.h>

#include <string>

#include "animation.h"
#include "funcs.h"
#include "types.h"

using namespace std;

/**
 * Class for text.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 22 March 2010
 */
class Text : public Animation {
private:

	/**
	 * the text itself
	 */
	string text;
	
	/**
	 * the size of the font
	 */
	int fontSize;
	
	/**
	 * the font name
	 */
	string fontName;
	
	/**
	 * the font color
	 */
	SDL_Color fontColor;
	
public:

private:

public:

	/**
	 * constructor with parameters
	 * @param txt the text
	 * @param posX the x pos of the text
	 * @param posY the y pos of the text
	 * @param fSize the font size
	 * @param alignment the alignment of the text
	 * @param fName the font name
	 * @param col the color
	 */
	Text(string txt, int posX, int posY, font_size fSize = size5, text_alignment alignment = center, string fName = FONT_SANS, SDL_Color col = makeColor(128,128,128));
	
	/**
	 * default destructor
	 */
	~Text();
	
	/**
	 * aligns the text
	 * @param alignment the new alignment
	 */
	void align(text_alignment alignment);
	
	/**
	 * changes the text
	 * @param newText the new text
	 * @param fSize the new font size
	 * @param fName the new font name
	 * @param col the new color
	 * @return true on success
	 */
	bool changeText(string newText, int fSize, string fName, SDL_Color col);
	
	/**
	 * changes the text
	 * @param newText the new text
	 * @return true on success
	 */
	bool changeText(string newText);
	
	/**
	 * gets the text
	 * @return the text string
	 */
	string getText();
	
};

#endif
