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

#ifndef KEYS
#define KEYS

#include <SDL.h>


namespace KeyState {
enum State {
	Up,
	Pressed,
	Released,
	Held,
};
}

namespace ButtonState {
enum State {
	Up,
	Pressed,
	Released,
	Held,
};
}

namespace MouseButton {
enum Button {
	Left = SDL_BUTTON_LEFT,
	Right = SDL_BUTTON_RIGHT,
	Middle = SDL_BUTTON_MIDDLE,
};
}




namespace Keys {

/**
 * maps all keys to sdl keys
 */
typedef enum {
	Unknown		= SDLK_UNKNOWN,
	First		= SDLK_FIRST,
	Backspace	= SDLK_BACKSPACE,
	Tab			= SDLK_TAB,
	Clear		= SDLK_CLEAR,
	Return		= SDLK_RETURN,
	Pause		= SDLK_PAUSE,
	Escape		= SDLK_ESCAPE,
	Space		= SDLK_SPACE,
	Exclaim		= SDLK_EXCLAIM,
	DoubleQuote	= SDLK_QUOTEDBL,
	Hash		= SDLK_HASH,
	Dollar		= SDLK_DOLLAR,
	Ampersand		= SDLK_AMPERSAND,
	Quote		= SDLK_QUOTE,
	LeftParen	= SDLK_LEFTPAREN,
	RightParen	= SDLK_RIGHTPAREN,
	Asterisk	= SDLK_ASTERISK,
	Plus		= SDLK_PLUS,
	Comma		= SDLK_COMMA,
	Minus		= SDLK_MINUS,
	Period		= SDLK_PERIOD,
	Slash		= SDLK_SLASH,
	Num_0			= SDLK_0,
	Num_1			= SDLK_1,
	Num_2			= SDLK_2,
	Num_3			= SDLK_3,
	Num_4			= SDLK_4,
	Num_5			= SDLK_5,
	Num_6			= SDLK_6,
	Num_7			= SDLK_7,
	Num_8			= SDLK_8,
	Num_9			= SDLK_9,
	Colon			= SDLK_COLON,
	SemiColon		= SDLK_SEMICOLON,
	LessThan		= SDLK_LESS,
	Equals			= SDLK_EQUALS,
	GreaterThan		= SDLK_GREATER,
	Question		= SDLK_QUESTION,
	At				= SDLK_AT,
	
	
	/*
	Skip uppercase letters
	*/
	LeftBracket		= SDLK_LEFTBRACKET,
	BackSlash		= SDLK_BACKSLASH,
	RightBracket	= SDLK_RIGHTBRACKET,
	Caret			= SDLK_CARET,
	UnderScore		= SDLK_UNDERSCORE,
	BackQuote		= SDLK_BACKQUOTE,
	A			= SDLK_a,
	B			= SDLK_b,
	C			= SDLK_c,
	D			= SDLK_d,
	E			= SDLK_e,
	F			= SDLK_f,
	G			= SDLK_g,
	H			= SDLK_h,
	I			= SDLK_i,
	J			= SDLK_j,
	K			= SDLK_k,
	L			= SDLK_l,
	M			= SDLK_m,
	N			= SDLK_n,
	O			= SDLK_o,
	P			= SDLK_p,
	Q			= SDLK_q,
	R			= SDLK_r,
	S			= SDLK_s,
	T			= SDLK_t,
	U			= SDLK_u,
	V			= SDLK_v,
	W			= SDLK_w,
	X			= SDLK_x,
	Y			= SDLK_y,
	Z			= SDLK_z,
	Delete		= SDLK_DELETE,
	/* End of ASCII mapped keysyms */
	
	/* Numeric keypad */
	NumPad_0			= SDLK_KP0,
	NumPad_1			= SDLK_KP1,
	NumPad_2			= SDLK_KP2,
	NumPad_3			= SDLK_KP3,
	NumPad_4			= SDLK_KP4,
	NumPad_5			= SDLK_KP5,
	NumPad_6			= SDLK_KP6,
	NumPad_7			= SDLK_KP7,
	NumPad_8			= SDLK_KP8,
	NumPad_9			= SDLK_KP9,
	NumPad_Period		= SDLK_KP_PERIOD,
	NumPad_Divide		= SDLK_KP_DIVIDE,
	NumPad_Multiply		= SDLK_KP_MULTIPLY,
	NumPad_Minus		= SDLK_KP_MINUS,
	NumPad_Plus			= SDLK_KP_PLUS,
	NumPad_Enter		= SDLK_KP_ENTER,
	NumPad_Equals		= SDLK_KP_EQUALS,
	
	/* Arrows + Home/End pad */
	Up			= SDLK_UP,
	Down		= SDLK_DOWN,
	Right		= SDLK_RIGHT,
	Left		= SDLK_LEFT,
	Insert		= SDLK_INSERT,
	Home		= SDLK_HOME,
	End			= SDLK_END,
	PageUp		= SDLK_PAGEUP,
	PageDown	= SDLK_PAGEDOWN,
	
	/* Function keys */
	F1			= SDLK_F1,
	F2			= SDLK_F2,
	F3			= SDLK_F3,
	F4			= SDLK_F4,
	F5			= SDLK_F5,
	F6			= SDLK_F6,
	F7			= SDLK_F7,
	F8			= SDLK_F8,
	F9			= SDLK_F9,
	F10			= SDLK_F10,
	F11			= SDLK_F11,
	F12			= SDLK_F12,
	F13			= SDLK_F13,
	F14			= SDLK_F14,
	F15			= SDLK_F15,
	
	/* Key state modifier keys */
	NumLock			= SDLK_NUMLOCK,
	CapsLock		= SDLK_CAPSLOCK,
	ScrollLock		= SDLK_SCROLLOCK,
	RightShift		= SDLK_RSHIFT,
	LeftShift		= SDLK_LSHIFT,
	RightCtrl		= SDLK_RCTRL,
	LeftCtrl		= SDLK_LCTRL,
	RightAlt		= SDLK_RALT,
	LeftAlt			= SDLK_LALT,
	RightMeta		= SDLK_RMETA,
	LeftMeta		= SDLK_LMETA,
	LeftSuper		= SDLK_LSUPER,		/* Left "Windows" key */
	RightSuper		= SDLK_RSUPER,		/* Right "Windows" key */
	
	/* Miscellaneous function keys */
	Help		= SDLK_HELP,
	Print		= SDLK_PRINT,
	SysReq		= SDLK_SYSREQ,
	Break		= SDLK_BREAK,
	Menu		= SDLK_MENU,
	
	/* Add any other keys here */
} Key;
}


#endif
