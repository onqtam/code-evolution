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

#ifndef TEAM
#define TEAM

#include "worm.h"
#include "types.h"
#include "arsenal.h"

#include <SDL.h>

#include <vector>
#include <string>

using namespace std;

#define DEGREESPERSEC 60
#define JUMPPOWER 500
#define SIGHTDISTANCE 150
#define FIREPOWERINCREASEPERSEC 1000
#define MAXFIREPOWER 2000
#define TIMEBETWEENEACHFIRING 1000

/**
 * Class for teams.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 21 Dec 2009
 */
class Team {
private:

public:

	/**
	 * the degrees per second to raise/lower the sight(if demanded)
	 */
	static int degreesPerSec;
	
	/**
	 * the power for jumping
	 */
	static int jumpPower;
	
	/**
	 * the distance between the objects and their sights
	 */
	static int sightDistance;
	
	/**
	 * the ammount of power increased by each second for firing weapons
	 */
	static int firePowerIncreasePerSec;
	
	/**
	 * the maximum fire pwoer
	 */
	static int maxFirePower;
	
	/**
	 * the minimum ammount of time between each firing for an object
	 */
	static Uint32 timeBetweenEachFiring;
	
	/**
	 * the name of the team
	 */
	string teamName;
	
	/**
	 * all the worms in the team
	 */
	vector<Worm*> worms;
	
	/**
	 * the currently selected worm in the team
	 */
	Worm* currentWorm;
	
	/**
	 * the sum of all worms' health
	 */
	int teamHealth;
	
	/**
	 * the arsenal for the team
	 */
	Arsenal arsenal;
	
private:

public:

	/**
	* constructor with parameters
	* @param arg_teamName the name of the team
	* @param numberOfCharacters the number of worms
	* @param health the health of each worm
	* @param col the color of the team
	*/
	Team(string arg_teamName, int numberOfCharacters, int health, SDL_Color col = makeColor(128,128,128));
	
	/**
	* Default destructor
	*/
	~Team();
	
	/**
	* for notification of some event
	* @param type the type of the event
	* @param obj the object, associated with the event
	* @param value some value (different meanings in different event types)
	*/
	void notifyForEvent(team_event_type type, Object* obj, float value);
	
	/**
	* for notification of some input
	* @param key the key that has been changed
	* @param state the new state of the key
	*/
	void notifyForInput(Keys::Key key, KeyState::State state);
	
	/**
	* updates that need to be done almost non-stop take place here.
	*/
	void updateTeam();
	
};

#endif
