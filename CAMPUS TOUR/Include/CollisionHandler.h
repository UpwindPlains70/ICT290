#ifndef COLLISONHANDLER_H
#define COLLISONHANDLER_H

#include "camera.h"
#include "Decorations.h"
/**
	 * @brief Handles all collision based code
	 *
	 *
	 * @author Shay Leary
	 * @version 01
	 * @date April, 2005, Finished
	 *
	 *
	 * @author Peter Neve
	 * @version 02
	 * @date 29/08/2021, Refactor
	 * 
	 * 
	 * @author Jason Botterill
	 * @version 03
	 * @date 29/08/2021, added new room collisions
	 * 
	 * @author Peter Neve
	 * @version 04
	 * @date 6/09/2021, added decoration collisions using Decoration
	 */
//Objects
extern Camera cam;

// creates bounding boxes for collsion detection
void CreateBoundingBoxes();

/// Creates bouding boxes for decoration objects
void CreateDecorationBoundingBoxes();

#endif // COLLISONHANDLER_H
