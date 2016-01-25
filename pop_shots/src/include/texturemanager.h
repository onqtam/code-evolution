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

#ifndef TEXTUREMANAGER
#define TEXTUREMANAGER

#include "texture.h"
#include "types.h"
#include <map>

/**
 * structure for texture manager's container entries.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 21 Dec 2009
 */
struct mapEntry {
	unsigned int referenceCount;
	Texture *texture;
};

/**
 * Class for managing textures.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 21 Dec 2009
 */
class TextureManager {
private:

	/**
	 * the map holding all textures, associated with their filenames
	 */
	static map<string, mapEntry> textureData;
	
public:

	/**
	 * holds the transparent color
	 */
	static const color transparent;
	
private:

public:

	/**
	 * gets a texture
	 * @param texturePath the name of the texture file
	 * @return a pointer to a texture
	 */
	static Texture* getTexture(string texturePath);
	
	/**
	 * informs that a texture is no longer needed by an object
	 * @param texturePath the texture that has one less references
	 */
	static void ungetTexture(string texturePath);
};

#endif
