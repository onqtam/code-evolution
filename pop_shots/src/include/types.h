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

#ifndef TYPES
#define TYPES

#include "debug.h"

#include "object.h"

#include <SDL.h>

/**
 * for NULL
 */
#include <cstddef>

/**
 * for atexit()
 */
#include <stdlib.h>

/**
 * for all the keys
 */
#include "keys.h"

#ifndef FONT_SANS
#define FONT_SANS "resources/fonts/sans_bold.ttf"
#endif

#ifndef FONT_STENCIL
#define FONT_STENCIL "resources/fonts/stencil_std.otf"
#endif

#ifndef FONT_COMIC
#define FONT_COMIC "resources/fonts/comic_sans_ms_bold.ttf"
#endif

#ifndef FONT_PURISA
#define FONT_PURISA "resources/fonts/purisa_bold.ttf"
#endif

#ifndef FONT_MONO
#define FONT_MONO "resources/fonts/tlwg_mono_bold.ttf"
#endif

enum font_size {
	size1 = 10,
	size2 = 20,
	size3 = 30,
	size4 = 40,
	size5 = 50,
	size6 = 60,
	size7 = 70,
	size8 = 80,
	size9 = 90,
	size10 = 100,
	size11 = 110,
	size12 = 120,
	size13 = 130,
	size14 = 140,
	size15 = 150,
	size16 = 160,
	size17 = 170,
	size18 = 180,
	size19 = 190,
	size20 = 200
};

enum text_alignment {
	center,
	center_top,
	center_bottom,
	left_middle,
	right_middle,
	left_bottom,
	right_bottom,
	left_top,
	right_top
};

namespace Side {
enum side {
	left,
	right,
	top,
	bottom
};
}

enum team_event_type {
	death,
	health_decrease
};

enum bouncing_type {
	bounce_none,
	bounce_horizontally_only,
	bounce_vertically_only,
	bounce_any_direction
};

enum window_type {
	info_window,
	weapon_window,
	menu_window,
	wind_window,
	help_window
};

enum explosive_type {
	non_explosive,
	explosive_on_timeout,
	explosive_on_contact
};

enum direction {
	none,
	left,
	right,
	up,
	down
};

enum weapon {
	blank,
	grenade,
	power_grenade,
	shell,
	power_shell
};

/**
 * part of the keys of the drawingengine containers
 */
enum layers {
	level,
	raster_object,
	vector_object,
	character_object,
	projectile_object,
	effect_object,
	gadget_object,
	text_object
};

struct layer_key {
	int layer;
	void* address;
};

struct drawInfo {
	Object* obj;
	SDL_Rect area;
	int posX;
	int posY;
};

struct color {
	int red;
	int green;
	int blue;
};

struct Explosion {
	float x;
	float y;
	
	float radius;
};

#endif
