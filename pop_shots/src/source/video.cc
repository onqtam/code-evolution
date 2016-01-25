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

#include "../include/video.h"
#include "../include/engine.h"
#include "../include/core.h"
#include "../include/camera.h"

#include <iostream>

using namespace std;

Video::Video() {
	Initialize(320,240,32,false);
	ShowWindow("game");
	camera.adjustSize(Width, Height);
}

Video::~Video() {
}

bool Video::Initialize(int width, int height, int bpp, bool currVisibility ) {
	Width = width;
	Height = height;
	Bpp = bpp;
	Surface = NULL;
	
	/*
	 * initalize SDL
	 */
	if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0 ) {
		cout << "Unable to initialize Video/Timer Sub System: " << SDL_GetError() << endl;
		exit(1);
	}
	
	SdlFlags = 0;
	
	FullScreen = false;
	
	const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
	
	if (videoInfo->hw_available) {
		PRINT(LOL  WE GOT HARDWARE SURFACE LOL)
		SdlFlags |= SDL_HWSURFACE;
	} else {
		SdlFlags |= SDL_SWSURFACE;
	}
	
	/*
	 * This checks if hardware blits can be done
	 */
	if ( videoInfo->blit_hw ) {
		SdlFlags |= SDL_HWACCEL;
	}
	
	/*
	 * if any parameters are 0 then get the current OS setting for them
	 */
	if (Width == 0) {
		Width = videoInfo->current_w;
	}
	if (Height == 0) {
		Height = videoInfo->current_h;
	}
	if (Bpp == 0) {
		Bpp = videoInfo->vfmt->BitsPerPixel;
	}
	
	/*
	 * check to see if the the properties are supported
	 */
	Bpp = SDL_VideoModeOK(Width, Height, Bpp, SdlFlags);
	
	if (Bpp == 0) {
		return false;
	}
	
	/*
	 * set cursor visibility
	 */
	CursorVisibility(currVisibility);
	
	return true;
}

void Video::SwapBuffers() {
	SDL_Flip(Surface);
}

void Video::ClearScreen() {
	SDL_Rect rect;
	rect.x=0;
	rect.y=0;
	rect.w=Width;
	rect.h=Height;
	SDL_FillRect(Surface, &rect,  SDL_MapRGB(Surface->format , 255, 255, 255));
	SDL_Flip(Surface);
}

bool Video::ShowWindow(std::string WindowTitle) {
	/*
	 * create the surface
	 */
	Surface = SDL_SetVideoMode(Width, Height, Bpp, SdlFlags);
	
	if ( Surface == NULL ) {
		cout << "Video mode set failed: " << SDL_GetError() << endl;
		return false;
	}
	
	/*
	 * set the real video info
	 */
	const SDL_VideoInfo* vidInfo = SDL_GetVideoInfo();
	
	Width = vidInfo->current_w;
	Height = vidInfo->current_h;
	
	/*
	 * set the window title
	 */
	SDL_WM_SetCaption(WindowTitle.c_str(), NULL);
	
	return 1;
}

bool Video::ResizeWindow(int width, int height) {
	/*
	 * Protect against a divide by zero
	 */
	if ( height == 0 ) {
		height = 1;
	}
	
	/*
	 * resize sdl surface
	 */
	Surface = SDL_SetVideoMode( width, height, Bpp, SdlFlags );
	
	if (Surface == NULL) {
		cout << "Could not resize window, reverting: " << SDL_GetError() << endl;
		
		Surface = SDL_SetVideoMode( Width, Height, Bpp, SdlFlags );
		
		if (Surface == NULL) {
			cout << "Could not revert to previous settings, quiting: " << SDL_GetError() << endl;
			exit(2);
		}
		
		return false;
	} else {
		Width = width;
		Height = height;
		
		/*
		 * informs all things listening for a resize event
		 * this VIDEORESIZE event is triggered manually
		 */
		SDL_Event resizeEvent;
		resizeEvent.type=SDL_VIDEORESIZE;
		Engine::engine->core.addEvent(resizeEvent);
	}
	
	return true;
}

void Video::CursorVisibility(bool visible) {
	if (visible) {
		SDL_ShowCursor(SDL_ENABLE);
	} else {
		SDL_ShowCursor(SDL_DISABLE);
	}
}

bool Video::ToggleFullScreen() {
	FullScreen = !FullScreen;
	
	if (FullScreen) {
		Surface = SDL_SetVideoMode( Width, Height, Bpp, SdlFlags | SDL_FULLSCREEN );
		SdlFlags|=SDL_FULLSCREEN;
	} else {
		Surface = SDL_SetVideoMode( Width, Height, Bpp, SdlFlags);
	}
	
	
	if (Surface == NULL) {
		FullScreen = !FullScreen;
		cout << "Failed to toggle fullscreen, reverting to previous resolution" << endl;
		
		if (FullScreen) {
			Surface = SDL_SetVideoMode( Width, Height, Bpp, SdlFlags | SDL_FULLSCREEN );
		} else {
			Surface = SDL_SetVideoMode( Width, Height, Bpp, SdlFlags);
		}
		
		if (Surface == NULL) {
			cout << "Failed to revert to previous resolution, quiting" << endl;
			exit(2);
		}
		
		return false;
	}
	
	return true;
}

SDL_PixelFormat* Video::GetPixelFormat() {
	return Surface->format;
}

int Video::GetWidth() {
	return Width;
}

int Video::GetHeight() {
	return Height;
}
