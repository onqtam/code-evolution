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

#ifndef CAMERA
#define CAMERA

#include <SDL.h>

#define HORIZONTALBOUNDRY 700

#define VERTICALBOUNDRY 500

/**
 * Class for the camera.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 21 Dec 2009
 */
class Camera {
	/**
	 * The Drawing Engine needs direct access to the camera
	 */
	friend class DrawingEngine;
	
private:

	/**
	 * the maximum number of pixels the camera can move away from the level horizontally
	 */
	static int horizontalBoundry;
	
	/**
	 * the maximum number of pixels the camera can move away from the level vertically
	 */
	static int verticalBoundry;
	
	/**
	 * tells if the camera has been moved
	 */
	bool moved;
	
	/**
	 * shows the X offset of the camera from the last moves
	 */
	int offX;
	
	/**
	 * shows the Y offset of the camera from the last moves
	 */
	int offY;
	
	/**
	 * tells if the camera is directly controlled by mouse movement
	 */
	bool controlledByMouse;
	
	/**
	 * the area which the camera covers (from the level)
	 */
	SDL_Rect area;
	
	/**
	 * the X position of the camera
	 */
	int posX;
	
	/**
	 * the Y position of the camera
	 */
	int posY;
	
	/**
	 * the width of the camera
	 */
	int width;
	
	/**
	 * the height of the camera
	 */
	int height;
	
public:

	/**
	 * Default constructor
	 */
	Camera();
	
	/**
	 * Default destructor
	 */
	~Camera();
	
	/**
	 * sets the X of the camera
	 * @param x coordinate x
	 */
	void gotoX(int x) {
		posX=x;
	}
	
	/**
	 * sets the Y of the camera
	 * @param y coordinate y
	 */
	void gotoY(int y) {
		posY=y;
	}
	
	/**
	 * sets the x and y of the camera
	 * @param x the X coord
	 * @param y the Y coord
	 */
	void gotoXY(int x, int y) {
		posX=x;
		posY=y;
	}
	
	/**
	 * offsets the camera by X
	 * @param x offset X
	 */
	void offsetX(int x);
	
	/**
	 * offsets the camera by Y
	 * @param y offset Y
	 */
	void offsetY(int y);
	
	/**
	 * offsets the camera by X and Y
	 * @param x offset X
	 * @param y offset Y
	 */
	void offsetXY(int x, int y);
	
	/**
	 * gets the X position of the camera
	 * @return x position
	 */
	int getX() {
		return posX;
	}
	
	/**
	 * gets the Y position of the camera
	 * @return y position
	 */
	int getY() {
		return posY;
	}
	
	/**
	 * gets the width of the camera
	 * @return width
	 */
	int getWidth() {
		return width;
	}
	
	/**
	 * gets the height of the camera
	 * @return height
	 */
	int getHeight() {
		return height;
	}
	
	/**
	 * gets the current offset X
	 * @return offset X
	 */
	int getOffsetX() {
		return offX;
	}
	
	/**
	 * gets the current offset Y
	 * @return offset Y
	 */
	int getOffsetY() {
		return offY;
	}
	
	/**
	 * updates camera's position using offsets
	 */
	void updatePosition();
	
	/**
	 * Gets the area in a rectangular structure
	 * @return rectangle
	 */
	SDL_Rect* getRectArea();
	
	/**
	 * Gets the area in a rectangular structure with the Y coord inverted
	 * @return rectangle
	 */
	SDL_Rect* getRectAreaInverse();
	
	/**
	 * Centeres the camera in the level
	 */
	void centerCamera();
	
	/**
	 * Adjusts the size of the camera (needed after the screen has been resized)
	 */
	void adjustSize(int w, int h);
	
	/**
	 * Sets whether the camera to be controlled directly by the mouse or not
	 * @param controlled whether it should be controlled or not
	 */
	void setMouseControl(bool controlled);
	
	/**
	 * Tells if the camera is directly controlled by the mouse or not
	 * @return controlled or not
	 */
	bool mouseControlled();
	
	/**
	 * Resets the offsets and the moved flag
	 */
	void reset();
	
	/**
	 * Updates camera position from event information
	 * @param ev event structure with information
	 */
	void moveEvent(SDL_Event ev);
};

#endif
