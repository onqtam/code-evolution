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

#include "../include/physics.h"
#include "../include/engine.h"
#include "../include/funcs.h"
#include "../include/math.h"

float Physics::gravity = GRAVITY;

int Physics::allowedDistance = ALLOWEDDISTANCE;

int Physics::threshold = THRESHOLD;

float Physics::bounceRatio = BOUNCERATIO;

float Physics::minimumBounceVelocity = MINIMUMBOUNCEVELOCITY;

void Physics::applyGravity(Object* obj) {
	((PhysicalObject*)obj)->velocity.y -= ((PhysicalObject*)obj)->physicalInterferenceRatio * ( gravity * ((float)Engine::engine->core.last_loop_time/1000) );
}

void Physics::applyWindEffect(PhysicalObject* obj) {
	obj->velocity.x +=  Engine::engine->logic.wind.getWindDirection() * ((float)Engine::engine->core.last_loop_time/1000);
}

Physics::Physics(float G) {
	gravity = G;
}

Physics::~Physics() {

}

bool Physics::checkForCollision(PhysicalObject* obj, float offX, float offY) {
	for ( list<Object*>::iterator it2 = ObjectManager::physicalObjects.begin(); it2 != ObjectManager::physicalObjects.end(); it2++ ) {
		if ( ((PhysicalObject*)(*it2))->collisions != NULL && obj != (PhysicalObject*)(*it2) ) {
			if ( CheckCollision( (int)(obj->x + offX), (int)(obj->y + offY), obj->width, obj->height , (int)(*it2)->x, (int)(*it2)->y, (*it2)->width, (*it2)->height ) ) {
				if ( CheckCollision( (*obj->collisions)[obj->collisionIndex], (int)(obj->x + offX), (int)(obj->y + offY), (*((PhysicalObject*)(*it2))->collisions)[((PhysicalObject*)(*it2))->collisionIndex]   , (int)(*it2)->x, (int)(*it2)->y ) ) {
					return true;
				}
			}
		}
	}
	
	bool result =  CheckCollision( &Engine::engine->logic.level.collision, 0, 0, (*obj->collisions)[obj->collisionIndex], (int)(obj->x + offX), (int)(obj->y + offY) );
	
	return result;
}

void Physics::moveObject(Object* obj, float offX, float offY) {
	obj->move(offX, offY);
	Engine::engine->logic.objectMapping->updateObjectPosition(obj, (int)offX, (int)offY);
}

void Physics::updateObjects() {
	if ( Engine::engine->core.last_loop_time > 0 ) {
		Engine::engine->teammanager.updateTeams();
		
		float seconds = ((float)Engine::engine->core.last_loop_time/1000);
		float offsetX=0;
		float offsetY=0;
		float tempOffsetX=0;
		float tempOffsetY=0;
		float stepX=0;
		float stepY=0;
		int steps=0;
		
		PhysicalObject* temp=NULL;
		
		for ( list<Object*>::iterator it = ObjectManager::physicalObjects.begin(); it != ObjectManager::physicalObjects.end(); it++ ) {
			temp = (PhysicalObject*)(*it);
			
			offsetX=0;
			offsetY=0;
			stepX=0;
			stepY=0;
			tempOffsetX=0;
			tempOffsetY=0;
			
			/*
			 * decrement time to live field
			 */
			if ( temp->ttl != -1 ) {
				temp->ttl -= Engine::engine->core.last_loop_time;
				
				if ( temp->ttl < 1 ) {
					if ( temp->explosive == explosive_on_timeout ) {
						explosions.push_back( makeExplosion( ((*it)->getX() + (*it)->getWidth()/2 ) + tempOffsetX, ((*it)->getY() + (*it)->getHeight()/2) + tempOffsetY , temp->radius_of_explosion ) );
					}
					
					Engine::engine->logic.objectMapping->remove(*it);
					Engine::engine->logic.objectManager.deleteObject(*it);
					it = ObjectManager::physicalObjects.erase(it);
					
					continue;
				}
			}
			
			/*
			 * perform flying
			 */
			if ( temp->flying ) {
				/*
				 * apply gravity
				 */
				applyGravity( *it );
				
				if ( temp->layerId == projectile_object ) {
					applyWindEffect( temp );
				}
				
				offsetX = temp->velocity.x * seconds;
				offsetY = temp->velocity.y * seconds;
				
				if ( temp->representedByVelocity == true ) {
					temp->updateRepresentationFromVelocity();
				}
				
				
				if ( temp->collisions != NULL && ( offsetX || offsetY ) ) {
					if ( absolute(offsetX) > absolute(offsetY) ) {
						steps = roundToNearestBiggerInt(absolute(offsetX));
						
						stepX = (absolute(offsetX) / steps);
						
						stepY = (absolute(offsetY) / steps);
					} else {
						steps = roundToNearestBiggerInt(absolute(offsetY));
						
						stepX = (absolute(offsetX) / steps);
						
						stepY = (absolute(offsetY) / steps);
					}
					
					stepX *= sign(offsetX);
					stepY *= sign(offsetY);
					
					bool collided = false;
					
					/*
					 * walk through the trajectory
					 */
					for ( int i = 1; !(collided) && (i <= steps) ; i++ ) {
						collided = checkForCollision( temp, tempOffsetX + stepX, tempOffsetY + stepY );
						
						if ( !(collided) ) {
							tempOffsetX += stepX;
							tempOffsetY += stepY;
						}
					}
					
					/*
					 * if collision occured, perform:
					 * checks if object needs to explode
					 * checks if object needs to bounce
					 */
					if ( collided ) {
						if ( temp->explosive == explosive_on_contact) {
							explosions.push_back( makeExplosion( ((*it)->getX() + (*it)->getWidth()/2 ) + tempOffsetX + stepX, ((*it)->getY() + (*it)->getHeight()/2) + tempOffsetY + stepY, temp->radius_of_explosion ) );
							
							Engine::engine->logic.objectMapping->remove(*it);
							Engine::engine->logic.objectManager.deleteObject(*it);
							it = ObjectManager::physicalObjects.erase(it);
							
							continue;
						} else {
							/*
							 * checking for horizontal bouncing
							 */
							if ( ((temp->bouncing == bounce_horizontally_only) || (temp->bouncing == bounce_any_direction)) && (offsetX != 0) ) {
								if ( checkForCollision( temp, tempOffsetX + stepX, tempOffsetY) ) {
									temp->velocity.x *= -Physics::bounceRatio;
									
									if ( absolute(temp->velocity.x) < Physics::minimumBounceVelocity ) {
										temp->velocity.x = 0;
									}
								}
							} else {
								temp->velocity.x = 0;
							}
							
							/*
							 * check for vertical bouncing
							 */
							if ( (temp->bouncing == bounce_vertically_only) || (temp->bouncing == bounce_any_direction) ) {
								if ( checkForCollision( temp, tempOffsetX, tempOffsetY + stepY ) ) {
									temp->velocity.y *= -Physics::bounceRatio;
									if ( absolute(temp->velocity.y) < Physics::minimumBounceVelocity ) {
										temp->velocity.y = 0;
									}
								}
							} else {
								temp->velocity.y = 0;
							}
							
							/*
							 * check if there is ground under the object. if there is, the object will no longer be flying ( only if it hasnt bounced (velocity.y == 0) )
							 */
							if ( checkForCollision( temp, tempOffsetX, tempOffsetY - 1) ) {
								if ( temp->velocity.y == 0 ) {
									temp->flying = false;
								}
							}
							
							/*
							 * stop animating if object stopped moving(flying)     (useful for making grenades stop spinning when they hit the ground... etc.)
							 */
							if ( temp->bouncing != bounce_none ) {
								if ( temp->flying == false ) {
									temp->setDelay(0);
								} else {
									temp->setDelay(temp->getDelay() + 10);
								}
							}
						}
					}
				}
			}
			
			/*
			 * perform walking
			 */
			if ( !(temp->flying) ) {
				if ( temp->walkingDirection != none ) {
					offsetX = temp->walkingSpeed * seconds;
					
					if ( temp->walkingDirection == left ) {
						offsetX *= -1;
					}
					
					stepX = (absolute(offsetX) / roundToNearestBiggerInt(absolute(offsetX)));
					
					stepX *= sign(offsetX);
					
					bool collided = false;
					
					int k = 0;
					
					/*
					 * go through step by step through the path, needed to be walked
					 * and see if it is possible without going up too much over something
					 */
					for ( int i = 1; !(collided) && ( i <= roundToNearestBiggerInt(absolute(offsetX)) ); i++ ) {
						collided = true;
						
						for ( k = -threshold; k <= threshold; k++ ) {
							if ( !checkForCollision(temp, tempOffsetX + stepX, (tempOffsetY + k)) ) {
								tempOffsetY += k;
								collided = false;
								break;
							}
						}
						
						if ( !(collided) ) {
							tempOffsetX += stepX;
						}
						
						if ( k == -threshold ) {
							if ( !checkForCollision(temp, tempOffsetX, tempOffsetY - 1) ) {
								temp->flying = true;
								break;
							}
						}
					}
				}
			}
			
			/*
			 * if actual offset exists
			 *
			 * all objects that go too far from the level are destroyed
			 */
			if ( tempOffsetX != 0 || tempOffsetY != 0 ) {
				if ( (temp->getX() + tempOffsetX) < (-Physics::allowedDistance) || (temp->getX() + tempOffsetX) > (Engine::engine->logic.level.getWidth() + Physics::allowedDistance) ) {
					if ( temp->layerId == character_object ) {
						Engine::engine->teammanager.notifyForEvent(death, (Object*)temp , temp->getHealth());
					}
					
					Engine::engine->logic.objectMapping->remove(*it);
					Engine::engine->logic.objectManager.deleteObject(*it);
					it = ObjectManager::physicalObjects.erase(it);
					
					fprintf(stderr, "Object went too far and was destroyed.\n");
					
					continue;
				}
				
				if ( (temp->getY() + tempOffsetY) < (-Physics::allowedDistance) || (temp->getY() + tempOffsetY) > (Engine::engine->logic.level.getHeight() + Physics::allowedDistance * 3) ) {
					if ( temp->layerId == character_object ) {
						Engine::engine->teammanager.notifyForEvent(death, (Object*)temp , temp->getHealth());
					}
					
					Engine::engine->logic.objectMapping->remove(*it);
					Engine::engine->logic.objectManager.deleteObject(*it);
					it = ObjectManager::physicalObjects.erase(it);
					
					fprintf(stderr, "Object went too far and was destroyed.\n");
					
					continue;
				}
				
				if ( ((int)(tempOffsetX + temp->x) != (int)(temp->x)) || ((int)(tempOffsetY + temp->y) != (int)(temp->y)) ) {
					Engine::engine->logic.objectMapping->updateObjectPosition( (*it), (int)(tempOffsetX + temp->x) - (int)(temp->x), (int)(tempOffsetY + temp->y) - (int)(temp->y) );
				}
				
				temp->move(tempOffsetX, tempOffsetY);
			}
		}
		
		/*
		 * explosion handling
		 * (all explosions that took place in the last updation)
		 */
		SDL_Rect areaOfExplosion;
		Texture* explosionTexture;
		
		for ( list<Explosion>::iterator it = explosions.begin(); it != explosions.end(); it++ ) {
			explosionTexture = Engine::engine->logic.explosionManager.getExplosion(it->radius);
			areaOfExplosion = makeRect(it->x - explosionTexture->getWidth() / 2, it->y - explosionTexture->getHeight() / 2, explosionTexture->getWidth(), explosionTexture->getHeight() );
			
			if ( Engine::engine->logic.level.destructive ) {
				/*
				 * update level
				 */
				areaOfExplosion.y = Engine::engine->logic.level.getHeight() - areaOfExplosion.y - explosionTexture->getHeight();
				SDL_BlitSurface(explosionTexture->getTexture(), NULL, Engine::engine->logic.level.getSurface(), &areaOfExplosion);
				
				/*
				 * update level's collision
				 */
				areaOfExplosion.y = it->y - explosionTexture->getHeight() / 2;
				Engine::engine->logic.level.collision.updateCollision( Engine::engine->logic.level.getSurface(), areaOfExplosion );
				
				/*
				 * fix collision's bounding box
				 */
				vector<Side::side> sides;
				sides.push_back(Side::top);
				sides.push_back(Side::bottom);
				sides.push_back(Side::left);
				sides.push_back(Side::right);
				Engine::engine->logic.level.makeCollisionOnSides(sides, 2);
				Engine::engine->logic.level.drawSides(sides, SDL_MapRGB(Engine::engine->logic.level.getSurface()->format,255,0,0), 2);
				
				/*
				 * to update screen
				 */
				Engine::engine->drawingengine.addToList(it->x - explosionTexture->getWidth() / 2, it->y - explosionTexture->getHeight() / 2,  explosionTexture->getWidth(),  explosionTexture->getHeight());
			}
			
			if ( it->radius <= explosionTexture->getWidth()/2 ) {
				it->radius = explosionTexture->getWidth()/2 + 1;
			}
			
			float distance = 0;
			
			for ( list<Object*>::iterator it2 = ObjectManager::physicalObjects.begin(); it2 != ObjectManager::physicalObjects.end(); it2++ ) {
				temp = (PhysicalObject*)(*it2);
				
				distance = sqrt( ( pow(absolute(temp->getX() + temp->getWidth()/2 - it->x), 2) ) + ( pow(absolute(temp->getY() + temp->getHeight()/2 - it->y), 2) ) );
				
				/*
				 * if in range
				 */
				if ( distance <= it->radius ) {
					temp->flying = true;
					
					temp->velocity = temp->velocity + makeVelocity( (temp->getX() + temp->getWidth()/2 - it->x) / distance, (temp->getY() + temp->getHeight()/2 - it->y) / distance ) * (it->radius - distance) * temp->physicalInterferenceRatio * 2;
					
					if ( temp->health != -1 ) {
						int tempHealthDecrease = (it->radius - distance) * temp->physicalInterferenceRatio;
						
						fprintf(stderr, "Decrementing health by %d. Health left: %d\n", tempHealthDecrease, temp->health - tempHealthDecrease);
						
						if ( !(temp->health - tempHealthDecrease > 0) ) {
							Engine::engine->teammanager.notifyForEvent(death, *it2, temp->getHealth());
							
							fprintf(stderr, "\tkilling object.\n");
							
							Engine::engine->logic.objectMapping->remove(*it2);
							Engine::engine->logic.objectManager.deleteObject(*it2);
							it2 = ObjectManager::physicalObjects.erase(it2);
						} else {
							temp->health -= tempHealthDecrease;
							Engine::engine->teammanager.notifyForEvent(health_decrease, *it2, tempHealthDecrease);
						}
					}
					
				}
			}
		}
		
		explosions.clear();
	}
}
