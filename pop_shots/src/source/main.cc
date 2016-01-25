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

#include "../include/engine.h"
#include "../include/funcs.h"

#include <string>
#include <stdio.h>

using namespace std;

/**
 * Main entry point of the application.
 *
 * @param argc - the number of arguments
 *
 * @param argv - the arguments
 *
 * @return the result of the program
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 21 Dec 2009
 */
int main(int argc, char* argv[]) {
	Engine* myEng = Engine::Instance();
	
	FILE* args = fopen("parameters.ini", "r");
	char temp[128];
	int tempInt;
	int red;
	int green;
	int blue;
	
	/*
	 * screen resolution
	 */
	int width;
	int height;
	fscanf(args, "Resolution %d %d\n", &width, &height);
	myEng->video.ResizeWindow(width,height);
	
	/*
	 * whether to make fullscreen or not
	 */
	fscanf(args, "Fullscreen %s\n", temp);
	if ( temp[0] == 't' && temp[1] == 'r' && temp[2] == 'u' && temp[3] == 'e' ) {
		myEng->video.ToggleFullScreen();
	}
	
	/*
	 * map initialization
	 */
	char map[128];
	fscanf(args, "Map %s\n\n", map);
	myEng->logic.loadLevel(map);
	
	/*
	 * team initialization
	 */
	int health;
	int worms;
	char ch;
	for (;;) {
		ch = fscanf(args, "%c", &ch);
		if ( ch != EOF ) {
			fscanf(args, "eam %i\n", &tempInt);
			fscanf(args, "Name %s\n", temp);
			fscanf(args, "Color %i %i %i\n", &red, &green, &blue);
			fscanf(args, "Health %i\n", &health);
			fscanf(args, "Worms %i\n", &worms);
			myEng->teammanager.teams.push_back(Team(temp, worms, health, makeColor(red,green,blue)));
		} else {
			break;
		}
	}
	myEng->teammanager.localTeam = &myEng->teammanager.teams.front();
	
	fclose(args);
	
	myEng->video.camera.centerCamera();
	
	myEng->core.loop();
	
	return 0;
}
