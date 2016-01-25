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

#ifndef INPUT
#define INPUT

#include <map>
#include <list>
#include <SDL.h>

#include "types.h"

/**
 * Class for handling events.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 21 Dec 2009
 */
class Input {

private:

	/**
	 * Holds the state of the keys
	 */
	std::map<Keys::Key, KeyState::State> Keystates;
	
	/**
	 * holds all keys that were pressed for a frame
	 */
	std::list<Keys::Key> PressedKeys;
	
	/**
	 * holds all keys that were released for a frame
	 */
	std::list<Keys::Key> ReleasedKeys;
	
	/**
	 * holds the x position of the mouse
	 */
	int MouseX;
	
	/**
	 * holds the y position of the mouse
	 */
	int MouseY;
	
	/**
	 * holds the state of the mouse buttons
	 */
	std::map<MouseButton::Button, ButtonState::State > MouseButtons;
	
	/**
	 * holds all mosue buttons that were pressed for a frame
	 */
	std::list<MouseButton::Button>	PressedMouseButtons;
	
	/**
	 * holds all mouse buttons that were released for a frame
	 */
	std::list<MouseButton::Button>	ReleasedMouseButtons;
	
public:

	/**
	 * Default constructor
	 */
	Input();
	
	/**
	 * Default destructor
	 */
	~Input();
	
	/**
	 * Tells if a key is inbetween being pressed and released
	 * @param key which key
	 * @return whether key is held or not
	 */
	bool IsKeyHeld(Keys::Key key);
	
	/**
	 * Tells if a key is pressed
	 * @param key which key
	 * @return whether key is pressed or not
	 */
	bool WasKeyPressed(Keys::Key key);
	
	/**
	 * Tells if a key is released
	 * @param key which key
	 * @return whether key is released or not
	 */
	bool WasKeyReleased(Keys::Key key);
	
	/**
	 * returns the state of the key
	 * @param key which key
	 * @return state of key
	 */
	KeyState::State GetKeyState(Keys::Key key);
	
	/**
	 * Tells if a mouse button is inbetween being pressed and released
	 * @param but which button
	 * @return whether button is held or not
	 */
	bool IsMouseButtonHeld(MouseButton::Button but);
	
	/**
	 * Tells if a mouse button is pressed
	 * @param but which button
	 * @return whether button is pressed or not
	 */
	bool WasMouseButtonPressed(MouseButton::Button but);
	
	/**
	 * Tells if a mouse button is released
	 * @param but which button
	 * @return whether button is released or not
	 */
	bool WasMouseButtonReleased(MouseButton::Button but);
	
	/**
	 * returns the state of the mouse button
	 * @param but which button
	 * @return state of button
	 */
	ButtonState::State GetKeyState(MouseButton::Button but);
	
	/**
	 * Gets mouse X position
	 * @return X position
	 */
	int GetMouseX();
	
	/**
	 * Gets mouse Y position
	 * @return Y position
	 */
	int GetMouseY();
	
	/**
	 * Updates all pressed to held and all released to up
	 */
	void KeyStatesToNextPhase();
	
	/**
	 * Updates keyboard and mouse states because of an event
	 * @param ev event to handle
	 */
	void Update(SDL_Event ev);
	
	/**
	 * handles keypress events
	 * @param ev event
	 */
	void keyPressed(SDL_Event ev);
	
	/**
	 * handles keyrelease events
	 * @param ev event
	 */
	void keyReleased(SDL_Event ev);
	
	/**
	 * handles mousemotion events
	 * @param ev event
	 */
	void mouseMotion(SDL_Event ev);
	
	/**
	 * handles mousebuttonpress events
	 * @param ev event
	 */
	void mouseButtonPressed(SDL_Event ev);
	
	/**
	 * handles mousebuttonrelease events
	 * @param ev event
	 */
	void mouseButtonReleased(SDL_Event ev);
};

#endif

