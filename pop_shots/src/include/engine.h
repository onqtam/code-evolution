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

#ifndef ENGINE
#define ENGINE

#include "video.h"
#include "core.h"
#include "input.h"
#include "drawingengine.h"
#include "texturemanager.h"
#include "windowsystem.h"
#include "teammanager.h"
#include "fontmanager.h"
#include "logic.h"

/**
 * Class for engine initialization.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 21 Dec 2009
 */
class Engine {

public:

	/**
	* a static pointer to the engine (all access to engine subsystems is made throught this pointer)
	*/
	static Engine *engine;
	
	/**
	 * core subsystem
	 */
	Core core;
	
	/**
	 * texture managing subsystem
	 */
	TextureManager texturemanager;
	
	/**
	 * video subsystem
	 */
	Video video;
	
	/**
	 * logic module
	 */
	Logic logic;
	
	/**
	 * input subsystem
	 */
	Input input;
	
	/**
	 * drawing engine
	 */
	DrawingEngine drawingengine;
	
	/**
	 * font manager
	 */
	FontManager fontmanager;
	
	/**
	 * the window system
	 */
	WindowSystem windowsystem;
	
	/**
	 * team manager
	 */
	TeamManager teammanager;
	
private:

	/**
	* a static function that frees the engine at exit of the program.
	*/
	static void freeEngine(void);
	
	/**
	* Default constructor (it is private to limit the creation of the engine)
	*/
	Engine();
	
public:

	/**
	* get a shared instance of the engine, so you don't have to pass around pointers to subsystems
	* @return pointer to created engine
	*/
	static Engine* Instance();
	
	/**
	* Default destructor
	*/
	~Engine();
};

#endif
