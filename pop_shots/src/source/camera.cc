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

#include "../include/camera.h"
#include "../include/engine.h"
#include "../include/funcs.h"

int Camera::horizontalBoundry = HORIZONTALBOUNDRY;

int Camera::verticalBoundry = VERTICALBOUNDRY;

Camera::Camera() {
	moved = true;
	controlledByMouse = true;
	offX = 0;
	offY = 0;
}

Camera::~Camera() {

}

void Camera::offsetX(int x) {
	if (x + posX < -Camera::horizontalBoundry) {
		/*
		 * if new pos exceeds limits on the left
		 */
		x = - ( Camera::horizontalBoundry + posX );
	} else {
		if (x + posX + width >Engine::engine->logic.level.getWidth() + Camera::horizontalBoundry) {
			/*
			 * if new pos exceeds limits on the right
			 */
			x = Engine::engine->logic.level.getWidth() + Camera::horizontalBoundry - posX - width;
		}
	}
	
	/*
	 * There is no offset. (caused by warping mouse in the center)
	 */
	if (x == 0) {
		return;
	}
	
	/*
	 * if actual offset exists    increment
	 */
	offX += x;
}

void Camera::offsetY(int y) {
	if (y + posY < -Camera::verticalBoundry) {
		/*
		 * if new pos exceeds limits on the bottom
		 */
		y = - ( Camera::verticalBoundry + posY );
	} else {
		if (y + posY + height >Engine::engine->logic.level.getHeight() + Camera::verticalBoundry) {
			/*
			 * if new pos exceeds limits on the top
			 */
			y = Engine::engine->logic.level.getHeight() + Camera::verticalBoundry - posY - height;
		}
	}
	
	/*
	 * There is no offset. (caused by warping mouse in the center)
	 */
	if (y == 0) {
		return;
	}
	
	/*
	 * if actual offset exists    increment
	 */
	offY+=y;
}

void Camera::offsetXY(int x, int y) {
	offsetX(x);
	offsetY(y);
}

void Camera::updatePosition() {
	if ( offX != 0 || offY != 0) {
		/*
		 * if moved update position and marked as moved
		 */
		if ( offX != 0) {
			posX += offX;
			offX=0;
		}
		if ( offY != 0) {
			posY += offY;
			offY=0;
		}
		moved = true;
	}
}

SDL_Rect* Camera::getRectArea() {
	area.x=posX;
	area.y=posY;
	area.w=width;
	area.h=height;
	return &area;
}

SDL_Rect* Camera::getRectAreaInverse() {
	area.x = posX;
	area.y = normalizeCoordY(posY,height);;
	area.w = width;
	area.h = height;
	return &area;
}

void Camera::centerCamera() {
	/*
	 * this puts the camera in the center of the level
	 */
	gotoXY((Engine::engine->logic.level.getWidth() - getWidth()) / 2, (Engine::engine->logic.level.getHeight() - getHeight()) / 2);
}

void Camera::adjustSize(int w, int h) {
	/*
	 * make adjustments to camera size when screen size has changed
	 */
	width=w;
	height=h;
	moved=true;
}

void Camera::setMouseControl(bool controlled) {
	controlledByMouse=controlled;
}

bool Camera::mouseControlled() {
	return controlledByMouse;
}

void Camera::reset() {
	moved=false;
}

void Camera::moveEvent(SDL_Event ev) {
	/*
	 * if camera is directly controlled by mouse     update its position using info from the event.
	 * note that the x and y from the event should not be the center of the screen because thats where
	 * the mouse is warped after this block of code and it would become infinite without this check.
	 * (warp only if not previously warped)
	 */
	if ( (mouseControlled()) && ( (ev.motion.x != getWidth() / 2 ) || (ev.motion.y != getHeight() / 2 ) ) ) {
		offsetX( ( ev.motion.x - getWidth() / 2) );
		offsetY( ( ev.motion.y - getHeight() / 2) * (-1));
		SDL_WarpMouse(getWidth()/2, getHeight()/2); //reset mouse position
	}
}

