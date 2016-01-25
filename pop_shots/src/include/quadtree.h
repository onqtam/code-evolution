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

#ifndef QUADTREE
#define QUADTREE

#define MAX_OBJECTS_PER_QUADTREE 6
#define MIN_OBJECTS_PER_QUADTREE 3
#define MAX_QUADTREE_DEPTH 5

#include "object.h"
#include "point2d.h"

#include <SDL.h>
#include <set>

using namespace std;

/**
 * Class for quadtrees.
 *
 * @author Viktor Kirilov
 *
 * @email n1ntendo@abv.bg
 *
 * @date 22 Match 2010
 */
class QuadTree {
private:

	/**
	 * the bottom left corner point
	 */
	Point2d bottom_left_corner;
	
	/**
	 * the top right corner point
	 */
	Point2d top_right_corner;
	
	/**
	 * the center point
	 */
	Point2d center;
	
	/**
	 * the current depth of the tree
	 */
	int depth;
	
	/**
	 * the objects, associated with this tree
	 */
	set<Object*> objects;
	
	/**
	 * the number of objects the tree holds
	 */
	int numberOfObjects;
	
	/**
	 * the children of the quadtree
	 */
	QuadTree* children[2][2];
	
	/**
	 * tells if the tree has any children
	 */
	bool hasChildren;
	
public:

	/**
	 * used for debugging the state of the quadtree
	 */
	static SDL_Surface* quadTreeChildren;
	
private:

	/**
	 * manages an object
	 * @param obj the object to manage
	 * @param posX the x pos of the object
	 * @param posY the y pos of the object
	 * @param width the width of the object
	 * @param height the height of the object
	 * @param addObject tells if the object should be added or removed
	 */
	void manageObject(Object* obj, int posX, int posY, int width, int height, bool addObject);
	
	/**
	 * makes children
	 */
	void makeChildren();
	
	/**
	 * collects objects from children
	 * @param container used to store the collected objects
	 */
	void collectObjects(set<Object*> &container);
	
	/**
	 * destroys all children
	 */
	void destroyChildren();
	
	/**
	 * removes an object
	 * @param obj the object to be removed
	 * @param posX the x of the object
	 * @param posY the y of the object
	 * @param width the width of the object
	 * @param height the height of the object
	 */
	void remove(Object* obj, int posX, int posY, int width, int height);
	
public:

	/**
	 * constructor with parameters
	 * @param bottom_left tells where the bottom left corner should be
	 * @param top_right tells where the top right corner should be
	 * @param Depth tells the current depth of the tree
	 */
	QuadTree(Point2d bottom_left, Point2d top_right, int Depth);
	
	/**
	 * default destructor
	 */
	~QuadTree();
	
	/**
	 * adds an object
	 * @param obj the object to be added
	 */
	void add(Object* obj);
	
	/**
	 * removes an object
	 * @param obj the object to be removed
	 */
	void remove(Object* obj);
	
	/**
	 * updates an object within the quadtree
	 * @param obj the object to be updated
	 * @param offsetX the offset in x
	 * @param offsetY the offset in y
	 */
	void updateObjectPosition(Object* obj, int offsetX, int offsetY);
	
	/**
	 * gets all the potential overlappings between objects
	 * @param pairs the container to be filled with pairs
	 */
	void potentialObjectOverlapping(set<pair<Object*, Object*> > &pairs);
	
};

#endif
