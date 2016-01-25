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

#include "../include/quadtree.h"
#include "../include/funcs.h"

void QuadTree::manageObject(Object* obj, int posX, int posY, int width, int height, bool addObject) {
	SDL_Rect objectArea = makeRect(posX, posY, width, height);
	
	SDL_Rect rects[2][2] = {{makeRect(bottom_left_corner.x, bottom_left_corner.y, center.x - bottom_left_corner.x, center.y - bottom_left_corner.y), makeRect(center.x, bottom_left_corner.y, center.x - bottom_left_corner.x, center.y - bottom_left_corner.y)}, { makeRect(bottom_left_corner.x, center.y, center.x - bottom_left_corner.x, center.y - bottom_left_corner.y), makeRect(center.x, center.y, center.x - bottom_left_corner.x, center.y - bottom_left_corner.y)}};
	
	for ( int x = 0; x < 2; x++ ) {
		for ( int y = 0; y < 2; y++ ) {
			if ( overlap_true_false(rects[x][y], objectArea) ) {
				if ( addObject ) {
					children[x][y]->add(obj);
				} else {
					children[x][y]->remove(obj);
				}
			}
		}
	}
}

void QuadTree::makeChildren() {
	int minX;
	int maxX;
	int minY;
	int maxY;
	
	Point2d min;
	Point2d max;
	
	for ( int x = 0; x < 2; x++ ) {
		if ( x == 0 ) {
			minX = bottom_left_corner.x;
			maxX = center.x;
		} else {
			minX = center.x;
			maxX = top_right_corner.x;
		}
		
		for ( int y = 0; y < 2; y++ ) {
			if ( y == 0 ) {
				minY = bottom_left_corner.y;
				maxY = center.y;
			} else {
				minY = center.y;
				maxY = top_right_corner.y;
			}
			
			children[x][y] = new QuadTree( makePoint2d(minX, minY), makePoint2d(maxX, maxY), depth + 1 );
		}
	}
	
	for ( set<Object*>::iterator it = objects.begin(); it != objects.end(); it++ ) {
		manageObject( *it, (*it)->getX(), (*it)->getY(), (*it)->getWidth(), (*it)->getHeight(), true );
	}
	
	objects.clear();
	
	hasChildren = true;
}

void QuadTree::collectObjects(set<Object*> &container) {
	if ( hasChildren ) {
		for ( int x = 0; x < 2; x++ ) {
			for ( int y = 0; y < 2; y++ ) {
				children[x][y]->collectObjects(container);
			}
		}
	} else {
		for ( set<Object*>::iterator it = objects.begin(); it != objects.end(); it++ ) {
			container.insert(*it);
		}
	}
}

void QuadTree::destroyChildren() {
	collectObjects(objects);
	
	for ( int x = 0; x < 2; x++ ) {
		for ( int y = 0; y < 2; y++ ) {
			delete children[x][y];
		}
	}
	
	hasChildren=false;
}

void QuadTree::remove(Object* obj, int posX, int posY, int width, int height) {
	numberOfObjects--;
	
	if ( hasChildren && numberOfObjects < MIN_OBJECTS_PER_QUADTREE ) {
		destroyChildren();
	}
	
	if ( hasChildren ) {
		manageObject(obj, posX, posY, width, height, false);
	} else {
		objects.erase(obj);
	}
}

QuadTree::QuadTree(Point2d bottom_left, Point2d top_right, int Depth) :
		bottom_left_corner(bottom_left),
		top_right_corner(top_right),
		center( makePoint2d( (bottom_left.x + top_right.x )/2, (bottom_left.y + top_right.y)/2 ) ),
		depth(Depth),
		numberOfObjects(0),
		hasChildren(false) {
		
}

QuadTree::~QuadTree() {
	if (hasChildren) {
		destroyChildren();
	}
}

void QuadTree::add(Object* obj) {
	numberOfObjects++;
	
	if ( !hasChildren && depth < MAX_QUADTREE_DEPTH && numberOfObjects > MAX_OBJECTS_PER_QUADTREE ) {
		makeChildren();
	}
	
	if ( hasChildren ) {
		manageObject(obj, obj->getX(), obj->getY(), obj->getWidth(), obj->getHeight(), true);
	} else {
		objects.insert(obj);
	}
}

void QuadTree::remove(Object* obj) {
	remove(obj, obj->getX(), obj->getY(), obj->getWidth(), obj->getHeight());
}

void QuadTree::updateObjectPosition(Object* obj, int offsetX, int offsetY) {
	remove(obj, obj->getX() - offsetX, obj->getY() - offsetY, obj->getWidth(), obj->getHeight());
	add(obj);
}

void QuadTree::potentialObjectOverlapping(set<pair<Object*, Object*> > &pairs) {
	if ( hasChildren ) {
		for ( int x = 0; x < 2; x++ ) {
			for ( int y = 0; y < 2; y++ ) {
				children[x][y]->potentialObjectOverlapping(pairs);
			}
		}
	} else {
		for ( set<Object*>::iterator it1 = objects.begin(); it1 != objects.end(); it1++ ) {
			for ( set<Object*>::iterator it2 = objects.begin(); it2 != objects.end(); it2++ ) {
				pairs.insert( pair<Object*, Object*>(*it1, *it2) );
			}
		}
	}
}
