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

#ifndef TEXTURE
#define TEXTURE

#include <string>
#include <SDL.h>

using namespace std;

/**
 * Class for textures.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 21 Dec 2009
 */
class Texture {

	/**
	 * for direct access to the surface
	 */
	friend class Text;
	
private:

	/**
	 * The surface to the texture itself
	 */
	SDL_Surface* texture;
	
	/**
	 * the filename of the texture
	 */
	string filename;
	
public:

	/**
	 * Constructor with a filename specified
	 * @param filename name of file(picture) to be loaded in the texture(surface)
	 */
	Texture(string newFilename = "");
	
	/**
	 * Default destructor
	 */
	~Texture();
	
	/**
	 * Gets the width of the texture
	 * @return width
	 */
	int getWidth() {
		if ( texture != NULL ) {
			return texture->w;
		} else {
			return 0;
		}
	}
	
	/**
	 * Gets the height of the texture
	 * @return height
	 */
	int getHeight() {
		if ( texture != NULL ) {
			return texture->h;
		} else {
			return 0;
		}
	}
	
	/**
	 * gets the filename
	 * @return the filename
	 */
	string getFileName() {
		return filename;
	}
	
	/**
	 * Gets a pointer to the surface of the texture
	 * @return pointer to surface
	 */
	SDL_Surface* getTexture() {
		return texture;
	}
	
	/**
	 * Deletes(frees) the surface of the texture
	 */
	void deleteTexture();
	
	/**
	 * Loads a file(picture) to the texture(surface)
	 * @return pointer to surface
	 */
	SDL_Surface* loadTexture(string);
	
};

#endif

