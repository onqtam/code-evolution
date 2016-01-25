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

#include "../include/team.h"
#include "../include/text.h"
#include "../include/sight.h"
#include "../include/engine.h"
#include "../include/types.h"

#include <string>

using namespace Keys;

int Team::degreesPerSec = DEGREESPERSEC;

int Team::jumpPower = JUMPPOWER;

int Team::sightDistance = SIGHTDISTANCE;

int Team::firePowerIncreasePerSec = FIREPOWERINCREASEPERSEC;

int Team::maxFirePower = MAXFIREPOWER;

Uint32 Team::timeBetweenEachFiring = TIMEBETWEENEACHFIRING;

Team::Team(string arg_teamName, int numberOfCharacters, int health, SDL_Color col) :
		teamName(arg_teamName),
		currentWorm(NULL),
		teamHealth(0) {
	if ( !(numberOfCharacters > 0) ) {
		return;
	}
	
	char str[128];
	
	string tempStr;
	
	for ( int i = 0; i < numberOfCharacters; i++ ) {
		worms.push_back( (Worm*)Engine::engine->logic.objectManager.newObject(new Worm(rand() % Engine::engine->logic.level.getWidth(),rand() % Engine::engine->logic.level.getHeight(), health)) );
		
		for ( ; Engine::engine->logic.physicsEngine.checkForCollision(worms.back(), 0, 0); ) {
			worms.back()->goTo(rand() % Engine::engine->logic.level.getWidth(),rand() % Engine::engine->logic.level.getHeight());
		}
		
		/*
		 * name
		 */
		sprintf(str, "Worm %d", i + 1);
		worms.back()->attached.push_back( new Text( str, worms.back()->getX() + worms.back()->getWidth()/2, worms.back()->getY() + worms.back()->getHeight() + size3 , size3, center_top, FONT_COMIC, col) );
		
		/*
		 * health (text)
		 */
		sprintf(str, "HP: %d", health);
		worms.back()->healthText = new Text( str, worms.back()->getX() + worms.back()->getWidth()/2, worms.back()->getY() + worms.back()->getHeight(), size3, center_top, FONT_COMIC, col);
		worms.back()->attached.push_back( worms.back()->healthText );
		
		/*
		 * sight
		 */
		worms.back()->sight = new Sight( worms.back(), Team::sightDistance);
		worms.back()->attached.push_back( worms.back()->sight );
		worms.back()->sight->toggleVisibility();
		
		teamHealth += health;
	}
	
	currentWorm = worms.front();
	
	currentWorm->sight->toggleVisibility();
	
	/*
	 * filling the team's arsenal
	 */
	arsenal.add(1, shell, 20);
	arsenal.add(1, power_shell, -1);
	arsenal.add(2, grenade, 20);
	arsenal.add(2, power_grenade, -1);
}

Team::~Team() {

}

void Team::notifyForEvent(team_event_type type, Object* obj, float value) {
	for ( vector<Worm*>::iterator it = worms.begin(); it != worms.end(); it++ ) {
		if ( *it == obj ) {
			switch (type) {
			case death:
				/*
				 * if a worm dies, it is removed from the team and the team's total health is decremented.
				 * if that worm is the current one, a new current worm is selected.
				 */
				teamHealth -= value;
				
				if ( currentWorm == *it ) {
					it = worms.erase(it);
					if ( worms.size() > 0 ) {
						currentWorm = worms.front();
						currentWorm->sight->toggleVisibility();
					} else {
						currentWorm = NULL;
					}
				} else {
					it = worms.erase(it);
				}
				
				break;
			case health_decrease:
				/*
				 * if a worm's health is decreased, the team's total health is decreased as well
				 */
				
				teamHealth -= value;
				
				char str[128];
				
				sprintf(str, "HP: %d", (*it)->getHealth());
				
				(*it)->healthText->changeText(str);
				
				break;
			}
			
			break;
		}
	}
}

void Team::notifyForInput(Keys::Key key, KeyState::State state) {
	if ( currentWorm == NULL ) {
		return;
	}
	
	if ( state == KeyState::Pressed ) {
		if ( key == Tab ) {
			/*
			 * if the tab key is pressed
			 * -if more than 1 worm is present
			 * --change the currently selected worm
			 * --quit walking, firing and whatever the current worm is doing
			 * --handle visibility of sights
			 */
			if ( worms.size() > 1 ) {
				for ( unsigned int i = 0; i < worms.size(); i++ ) {
					if ( worms[i] == currentWorm ) {
						/*
						 * hide sight
						 */
						currentWorm->sight->toggleVisibility();
						
						if ( i + 1 < worms.size() ) {
							/*
							 * go to next worm
							 */
							currentWorm = worms[i + 1];
						} else {
							/*
							 * go to first worm
							 */
							currentWorm = worms[0];
						}
						
						/*
						 * stop walking (if needed) and make the new selected object to walk (keeping the direction)
						 */
						if ( worms[i]->getWalkingDirection() != none ) {
							currentWorm->turnTo(worms[i]->getWalkingDirection());
							worms[i]->turnTo(none);
						}
						
						/*
						 * show sight of new selected worm
						 */
						currentWorm->sight->toggleVisibility();
						
						break;
					}
				}
			}
		}
		
		if ( key == Left ) {
			currentWorm->turnTo(left);
			currentWorm->sight->changeAngle(currentWorm->getAngle());
		}
		
		if ( key == Right ) {
			currentWorm->turnTo(right);
			currentWorm->sight->changeAngle(currentWorm->getAngle());
		}
		
		if ( key == Return ) {
			currentWorm->jump(Team::jumpPower, currentWorm->getAngle());
		}
		
		if ( key == Space ) {
			/*
			 * if space has been pressed
			 * -if current worm is firing
			 * --increase firepower
			 * -else
			 * --make current worm firing
			 */
			if ( currentWorm->firing ) {
				currentWorm->increaseFirePower( ((float)Engine::engine->core.last_loop_time * Team::firePowerIncreasePerSec)/1000 );
			} else {
				if ( SDL_GetTicks() > currentWorm->lastFired + Team::timeBetweenEachFiring ) {
					if ( arsenal.weapons[currentWorm->weaponColumn].size() > 0 ) {
						if ( arsenal.weapons[currentWorm->weaponColumn][currentWorm->wep].quantity > 0 || arsenal.weapons[currentWorm->weaponColumn][currentWorm->wep].quantity == -1) {
							currentWorm->firing = true;
							currentWorm->increaseFirePower( ((float)Engine::engine->core.last_loop_time * Team::firePowerIncreasePerSec)/1000 );
							
							fprintf(stderr, "starting to fire... quantity left: %d\n", arsenal.weapons[currentWorm->weaponColumn][currentWorm->wep].quantity - 1);
						}
					}
				}
			}
			
			if ( currentWorm->firePower > Team::maxFirePower ) {
				currentWorm->fire(arsenal.weapons[currentWorm->weaponColumn][currentWorm->wep].type, Team::maxFirePower);
				if ( arsenal.weapons[currentWorm->weaponColumn][currentWorm->wep].quantity != -1 ) {
					arsenal.weapons[currentWorm->weaponColumn][currentWorm->wep].quantity--;
				}
				currentWorm->lastFired = SDL_GetTicks();
				currentWorm->firePower = 0;
				currentWorm->firing = false;
			}
		}
		
		if ( key >= Num_0 && key <= Num_9 ) {
			if ( currentWorm->weaponColumn == (unsigned int)(key - 48) ) {
				if ( arsenal.weapons[currentWorm->weaponColumn].size() > 1 ) {
					/*
					 * if we change the position in the column while firing we fire the weapon being fired at once and change the current weapon after that.
					 */
					if ( currentWorm->firing ) {
						currentWorm->fire(arsenal.weapons[currentWorm->weaponColumn][currentWorm->wep].type , currentWorm->firePower);
						if ( arsenal.weapons[currentWorm->weaponColumn][currentWorm->wep].quantity != -1 ) {
							arsenal.weapons[currentWorm->weaponColumn][currentWorm->wep].quantity--;
						}
						currentWorm->lastFired = SDL_GetTicks();
						currentWorm->firePower = 0;
						currentWorm->firing = false;
					}
					
					if ( currentWorm->wep + 1< arsenal.weapons[currentWorm->weaponColumn].size() ) {
						PRINT(going to next one in this column)
						currentWorm->wep++;
					} else {
						PRINT(going to first in this column)
						currentWorm->wep = 0;
					}
				}
			} else {
				/*
				 * if we change the column while firing we fire the weapon being fired at once and change the current weapon after that.
				 */
				if ( currentWorm->firing ) {
					currentWorm->fire(arsenal.weapons[currentWorm->weaponColumn][currentWorm->wep].type , currentWorm->firePower);
					if ( arsenal.weapons[currentWorm->weaponColumn][currentWorm->wep].quantity != -1 ) {
						arsenal.weapons[currentWorm->weaponColumn][currentWorm->wep].quantity--;
					}
					currentWorm->lastFired = SDL_GetTicks();
					currentWorm->firePower = 0;
					currentWorm->firing = false;
				}
				
				if ( (unsigned int)(key - 48) == 0 ) {
					currentWorm->weaponColumn = 10;
				} else {
					currentWorm->weaponColumn = (unsigned int)(key - 48);
				}
				
				currentWorm->wep = 0;
			}
		}
	}
	
	if ( state == KeyState::Released ) {
		if ( key == Left ) {
			if ( !(Engine::engine->input.IsKeyHeld(Right)) ) {
				currentWorm->turnTo(none);
			} else {
				currentWorm->turnTo(right);
				currentWorm->sight->changeAngle(currentWorm->getAngle());
			}
		}
		
		if ( key == Right ) {
			if ( !(Engine::engine->input.IsKeyHeld(Left)) ) {
				currentWorm->turnTo(none);
			} else {
				currentWorm->turnTo(left);
				currentWorm->sight->changeAngle(currentWorm->getAngle());
			}
		}
		
		if ( key == Space ) {
			if ( currentWorm->firing ) {
				currentWorm->fire(arsenal.weapons[currentWorm->weaponColumn][currentWorm->wep].type , currentWorm->firePower);
				if ( arsenal.weapons[currentWorm->weaponColumn][currentWorm->wep].quantity != -1 ) {
					arsenal.weapons[currentWorm->weaponColumn][currentWorm->wep].quantity--;
				}
				currentWorm->lastFired = SDL_GetTicks();
				currentWorm->firePower = 0;
				currentWorm->firing = false;
			}
		}
	}
}

void Team::updateTeam() {
	/*
	 * updating the team means updating the current worm
	 * -sight movement
	 * -firing
	 */
	if ( currentWorm == NULL ) {
		return;
	}
	
	if ( Engine::engine->input.IsKeyHeld(Up) ) {
		currentWorm->increaseAngle( ((float)Engine::engine->core.last_loop_time/1000) * Team::degreesPerSec );
		
		currentWorm->sight->changeAngle(currentWorm->getAngle());
	}
	
	if ( Engine::engine->input.IsKeyHeld(Down) ) {
		currentWorm->increaseAngle( - ((float)Engine::engine->core.last_loop_time/1000) * Team::degreesPerSec );
		
		currentWorm->sight->changeAngle(currentWorm->getAngle());
	}
	
	if ( Engine::engine->input.IsKeyHeld(Space) ) {
		if ( currentWorm->firing ) {
			currentWorm->increaseFirePower( ((float)Engine::engine->core.last_loop_time * Team::firePowerIncreasePerSec)/1000 );
		}
		
		if ( currentWorm->firePower > Team::maxFirePower ) {
			currentWorm->fire(arsenal.weapons[currentWorm->weaponColumn][currentWorm->wep].type, Team::maxFirePower);
			currentWorm->lastFired = SDL_GetTicks();
			currentWorm->firePower = 0;
			currentWorm->firing = false;
		}
	}
}
