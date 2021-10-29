#ifndef DOORHANDLER_H
#define DOOORHANDLER_H

#include <GL/glut.h>
#include "TextureHandler.h"
#include "CollisionHandler.h"
#include "UpdateHandler.h"
#include "UIHandler.h"

#define TIMERSECS 25

/**
	 * @brief Defines everything for door object (behavior, pos, orientation, etc)
	 *
	 * @author Mark Burns
	 * @version 01
	 * @date 29/08/2021, Started
	 * 
	 * @author Peter Neve
	 * @version 02
	 * @date 29/08/2021, Refactor
	 * 
	 * @author Raymond Lau
	 * @version 03
	 * @date 09/10/2021, made doors planes instead of cubes
	 * 
	 * @author Jason Botterill
	 * @version 04
	 * @date 20/10/2021, textured doors
	 * 
	 * @author Peter Neve
	 * @version 05
	 * @date 29/10/2021, door y scale fix & front z scale
	 * 
	 */
///prevTime value for animation tracking
extern float prevTime;
///currTime value for animation tracking
extern float currTime;

///Position (Point3)
class Position {
	public:
		GLfloat x;
		GLfloat y;
		GLfloat z;
};

/// Door Turn object
class door2 {
	public: 
		float orientation;
		float loOrientation;
		float cOrientation;
		float roOrientation;
		//state -1:left-open, 0:closed, 1:right-open
		int state;
		bool moving;
		float speed;
		Position pos;
		Position scale;
};

/// Door Slide object
class door1 {
	public:
		float orientation;
		//state 1:open, 0:closed
		int state;
		bool moving;
		float speed;
		Position openPos;
		Position closePos;
		Position pos;
		Position scale;
};

/// front sliding door
extern door1 front;
/// back left swival door
extern door2 backL;
/// back right swival door
extern door2 backR;
extern float angle;

/**
* @brief display doors in 3D world
* 
* @return void
*/
void DisplayDoors();

/**
* @brief draw door geometry
*
* @return void
*/
void CreateDoors();

/**
* @brief Allows doors to turn/rotate
*
* @param int - val
* @return void
*/
void animate(int value);

#endif // !DOORHANDLER_H