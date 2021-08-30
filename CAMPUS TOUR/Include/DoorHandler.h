#ifndef DOORHANDLER_H
#define DOOORHANDLER_H

#include <GL/glut.h>
#include "TextureHandler.h"
#include "CollisionHandler.h"

#define TIMERSECS 25

//int dx = 0;
extern float prevTime;
extern float currTime;

//Position
class Position {
	public:
		GLfloat x;
		GLfloat y;
		GLfloat z;
};

// Door Turn
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

// Door Slide
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

extern door1 front;
extern door2 backL;
extern door2 backR;

void DisplayDoors();
void CreateDoors();
void animate(int value);

#endif // !DOORHANDLER_H