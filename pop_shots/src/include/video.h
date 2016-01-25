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

#ifndef VIDEO
#define VIDEO

#include <string>
#include <SDL.h>

#include "camera.h"

using namespace std;

/**
 * Class for video memory operations.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 21 Dec 2009
 */
class Video {
	/**
	 * For access to the surface.
	 */
	friend class DrawingEngine;
	
protected:

	/**
	 * Stores the width of the drawing area
	 */
	int Width;
	
	/**
	 * Stores the height of the drawing area
	 */
	int Height;
	
	/**
	 * Stores the bits per pixel of the screen
	 */
	int Bpp;
	
	/**
	 * Tells if the window id fullscreen or not
	 */
	bool FullScreen;
	
	/**
	 * Stores the drawing surface
	 */
	SDL_Surface* Surface;
	
	/**
	 * Stores the drawing surface's capabilities
	 */
	Uint32 SdlFlags;
	
public:

	/**
	 * the camera
	 */
	Camera camera;
	
public:

	/**
	 * name:
	 * Default Constructor
	 */
	Video();
	
	/**
	 * name:
	 * Default Destructor
	 */
	~Video();
	
	/**
	 * Initializes all parts of the video subsystem
	 * @param Width width of screen
	 * @param Height height of screen
	 * @param Bpp bits per pixel of screen
	 * @param currVisibility whether to show the cursor or not
	 * @return success of initialization
	 */
	bool Initialize(int Width = 0, int Height = 0, int Bpp = 0, bool currVisibility = false);
	
	/**
	 * Clears the screen (put black color + flip buffers)
	 */
	void ClearScreen();
	
	/**
	 * Swaps the buffers
	 */
	void SwapBuffers();
	
	/**
	 * Shows the window with a title
	 * @param WindowTitle title of window
	 */
	bool ShowWindow(string WindowTitle = "");
	
	/**
	 * Resizes the window
	 * @param width new width
	 * @param height new height
	 */
	bool ResizeWindow(int width, int height);
	
	/**
	 * Sets the cursor visibility
	 * @param visible visibility
	 */
	void CursorVisibility(bool visible);
	
	/**
	 * Changes Screen mode (full to windowed or windowed to full)
	 * @return whether new mode is fullscreen or not
	 */
	bool ToggleFullScreen();
	
	/**
	 * Gets the pixel format
	 * @return the pixel format of the main surface
	 */
	SDL_PixelFormat* GetPixelFormat();
	
	/**
	 * Gets the width of the screen/window
	 * @return width
	 */
	int GetWidth();
	
	/**
	 * Gets the height of the screen/window
	 * @return height
	 */
	int GetHeight();
};

#endif

