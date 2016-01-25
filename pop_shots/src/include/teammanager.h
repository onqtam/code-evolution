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

#ifndef TEAMMANAGER
#define TEAMMANAGER

#include "team.h"
#include "types.h"

#include <SDL.h>

#include <vector>

/**
 * Class for managing teams.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 21 Dec 2009
 */
class TeamManager {
private:

public:

	/**
	 * all the teams
	 */
	vector<Team> teams;
	
	/**
	 * the local team(local to thos computer)
	 */
	Team* localTeam;
	
private:

public:

	/**
	* Default constructor
	*/
	TeamManager();
	
	/**
	* Default destructor
	*/
	~TeamManager();
	
	/**
	* notifies all teams for an event
	* @param type the type of the event
	* @param obj the object, associated with the event
	* @param value some value (different meanings in different event types)
	*/
	void notifyForEvent(team_event_type type, Object* obj, float value);
	
	/**
	* for input notify-ing
	* @param key the key that has been changed
	* @param state the new state of the key
	*/
	void notifyLocalTeamForInput(Keys::Key key, KeyState::State state);
	
	/**
	* performs any update that needs to take place all the time (for instance raising the sight, increasing firepower)
	*/
	void updateTeams();
	
};

#endif
