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

#include "../include/animation.h"
#include "../include/engine.h"
#include "../include/funcs.h"
#include "../include/types.h"

Uint32 Animation::updateAnimation(Uint32 interval, void *param) {
	/*
	 * parameters casted to whatever i expect
	 */
	Animation* specs = (Animation*)param;
	if ((unsigned int)specs->currentIndex < specs->frames.size() - 1) {
		/*
		 * if not reached the last frame increment
		 */
		specs->currentIndex++;
	} else {
		if (specs->frames.size() != 0) {
			specs->currentIndex = 0;
		}
	}
	
	/*
	 * if frames actually exist    add to list for updation
	 */
	if ( ( specs->frames.size() > 0 ) && ( specs->visible ) ) {
		if ( Engine::engine != NULL ) {
			Engine::engine->drawingengine.addToList((int)specs->getX(), (int)specs->getY(), (int)specs->width, (int)specs->height );
		}
	}
	
	return interval;
}

bool Animation::calculateFrames() {
	/*
	 * if width or height of animation frames is 0   quit with false
	 */
	if ( (width == 0) || (height == 0) ) {
		return false;
	}
	frames.clear();
	
	int rows = (texture->getHeight() / height);
	int columns = (texture->getWidth() / width);
	
	/*
	 * calculating all frames' positions
	 */
	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < columns; k++) {
			frames.push_back(makeRect(k*width, i*height, width, height));
		}
	}
	
	return true;
}

Texture* Animation::getTexture() {
	return texture;
}

Animation::Animation(string name, Uint32 dly, float X, float Y, int h, int w, int layer)
		: Object(X,Y,layer), texture(Engine::engine->texturemanager.getTexture(name)), currentIndex(0), timerId(0), delay(0) {
	width=w;
	height=h;
	/*
	 * if texture actually has been set
	 */
	if (texture!=NULL) {
		calculateFrames();
		setDelay(dly);
	}
	Engine::engine->drawingengine.addToList((int)getX(), (int)getY(), (int)width, (int)height );
}

Animation::~Animation() {
	if ( layerId != text_object ) {
		Engine::engine->texturemanager.ungetTexture(texture->getFileName());
	}
	
	if (timerId!=0) {
		SDL_RemoveTimer(timerId);
	}
}

SDL_Rect Animation::getCurrentFrame() {
	return frames[currentIndex];
}

void Animation::setDelay(Uint32 newDelay) {
	if (newDelay > 0) {
		/*
		 * if a previous timer exists remove and create new
		 */
		if ( delay != 0 ) {
			SDL_RemoveTimer(timerId);
		}
		timerId = SDL_AddTimer(newDelay,updateAnimation,this);
		delay=newDelay;
	} else {
		/*
		 * if a previous timer exists remove and dont create new
		 */
		if ( delay != 0 ) {
			SDL_RemoveTimer(timerId);
			timerId=0;
		}
		delay = 0;
	}
}

Uint32 Animation::getDelay() {
	return delay;
}

void Animation::pause(void) {
	if (timerId!=0) {
		SDL_RemoveTimer(timerId);
		timerId=0;
	}
}

void Animation::resume(void) {
	if (timerId==0) {
		timerId = SDL_AddTimer(delay,updateAnimation,this);
	}
}

int Animation::getIndexOfCurrentFrame() {
	return currentIndex;
}

void Animation::setWidth(int w) {
	if (texture->getWidth() % w == 0) {
		/*
		 * recalculation of all frames is necessary after each width/height change occurs
		 */
		width=w;
		calculateFrames();
	}
}

void Animation::setHeight(int h) {
	if (texture->getHeight() % h == 0) {
		/*
		 * recalculation of all frames is necessary after each width/height change occurs
		 */
		height=h;
		calculateFrames();
	}
}
