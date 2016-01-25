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

#include "../include/input.h"
#include "../include/engine.h"

Input::Input() {
	SDL_EnableKeyRepeat(300, 80);
}

Input::~Input() {

}

bool Input::IsKeyHeld(Keys::Key key) {
	return Keystates[key] == KeyState::Held;
}

bool Input::WasKeyPressed(Keys::Key key) {
	return Keystates[key] == KeyState::Pressed;
}

bool Input::WasKeyReleased(Keys::Key key) {
	return Keystates[key] == KeyState::Released;
}

KeyState::State Input::GetKeyState(Keys::Key key) {
	return Keystates[key];
}

bool Input::IsMouseButtonHeld(MouseButton::Button but) {
	return MouseButtons[but] == ButtonState::Held;
}

bool Input::WasMouseButtonPressed(MouseButton::Button but) {
	return MouseButtons[but] == ButtonState::Pressed;
}

bool Input::WasMouseButtonReleased(MouseButton::Button but) {
	return MouseButtons[but] == ButtonState::Released;
}

ButtonState::State Input::GetKeyState(MouseButton::Button but) {
	return MouseButtons[but];
}

int Input::GetMouseX() {
	return MouseX;
}


int Input::GetMouseY() {
	return MouseY;
}

void Input::KeyStatesToNextPhase() {
	/*
	 * for keyboard
	 */
	{
		std::list<Keys::Key>::iterator itr;
		
		/*
		 * converts all pressed to held
		 */
		for (itr = PressedKeys.begin(); itr != PressedKeys.end(); itr++) {
			Keystates[(*itr)] = KeyState::Held;
		}
		
		/*
		 * converts all releaset to up
		 */
		for (itr = ReleasedKeys.begin(); itr != ReleasedKeys.end(); itr++) {
			Keystates[(*itr)] = KeyState::Up;
		}
	}
	
	
	/*
	 * for mouse buttons
	 */
	{
		std::list<MouseButton::Button>::iterator itr;
		
		/*
		 * converts all pressed to held
		 */
		for (itr = PressedMouseButtons.begin(); itr != PressedMouseButtons.end(); itr++) {
			MouseButtons[(*itr)] = ButtonState::Held;
		}
		
		/*
		 * converts all released to up
		 */
		for (itr = ReleasedMouseButtons.begin(); itr != ReleasedMouseButtons.end(); itr++) {
			MouseButtons[(*itr)] = ButtonState::Up;
		}
	}
	
	/*
	 * clears all pressed/released for up until this moment
	 */
	PressedKeys.clear();
	ReleasedKeys.clear();
	
	ReleasedMouseButtons.clear();
	PressedMouseButtons.clear();
}

void Input::Update(SDL_Event ev) {
	switch ( ev.type ) {
	
	case SDL_KEYDOWN:
		keyPressed(ev);
		break;
		
	case SDL_KEYUP:
		keyReleased(ev);
		break;
		
	case SDL_MOUSEMOTION:
		mouseMotion(ev);
		break;
		
	case SDL_MOUSEBUTTONUP:
		mouseButtonReleased(ev);
		break;
		
	case SDL_MOUSEBUTTONDOWN:
		mouseButtonPressed(ev);
		break;
		
	default:
		break;
	}
	
}

void Input::keyPressed(SDL_Event ev) {
	/*
	 * update key states
	 */
	Keystates[(Keys::Key)ev.key.keysym.sym] = KeyState::Pressed;
	PressedKeys.push_back((Keys::Key)ev.key.keysym.sym);
	
	Engine::engine->teammanager.notifyLocalTeamForInput((Keys::Key)ev.key.keysym.sym, KeyState::Pressed);
}

void Input::keyReleased(SDL_Event ev) {
	/*
	 * update key states
	 */
	Keystates[(Keys::Key)ev.key.keysym.sym] = KeyState::Released;
	ReleasedKeys.push_back((Keys::Key)ev.key.keysym.sym);
	
	Engine::engine->teammanager.notifyLocalTeamForInput((Keys::Key)ev.key.keysym.sym, KeyState::Released);
}

void Input::mouseMotion(SDL_Event ev) {
	/*
	 * update mouse position
	 */
	Engine::engine->video.camera.moveEvent(ev);
	MouseX = ev.motion.x;
	MouseY = ev.motion.y;
}

void Input::mouseButtonPressed(SDL_Event ev) {
	/*
	 * update mousebutton states
	 */
	MouseButtons[(MouseButton::Button)ev.button.button] = ButtonState::Pressed;
	PressedMouseButtons.push_back((MouseButton::Button)ev.button.button);
}

void Input::mouseButtonReleased(SDL_Event ev) {
	/*
	 * update mousebutton states
	 */
	MouseButtons[(MouseButton::Button)ev.button.button] = ButtonState::Released;
	ReleasedMouseButtons.push_back((MouseButton::Button)ev.button.button);
}

