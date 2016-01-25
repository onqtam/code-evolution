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

#include "../include/teammanager.h"

TeamManager::TeamManager() {

}

TeamManager::~TeamManager() {

}

void TeamManager::notifyForEvent(team_event_type type, Object* obj, float value) {
	for ( unsigned int i = 0; i < teams.size(); i++ ) {
		teams[i].notifyForEvent(type, obj, value);
	}
}

void TeamManager::notifyLocalTeamForInput(Keys::Key key, KeyState::State state) {
	localTeam->notifyForInput(key, state);
}

void TeamManager::updateTeams() {
	localTeam->updateTeam();
}
