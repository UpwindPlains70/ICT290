//Aurthor: Peter Neve
//Version: 1
//Date: 29/08/2021
//Purpose: defines camera movement and UI overlay

#ifndef MOVEMENTHANDLER_H
#define MOVEMENTHANDLER_H

#include "CollisionHandler.h"
#include "DisplayHandler.h"

// keyboard and mouse functions
void keys(unsigned char key, int x, int y);
void movementKeys(int key, int x, int y);
void releaseKey(int key, int x, int y);
void releaseKeys(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void mouseMove(int x, int y);

// screen width and height
extern int width, height;

// display campus map
extern bool DisplayMap;
// display welcome screen
extern bool DisplayWelcome;
// display exit screen
extern bool DisplayExit;

// display ECL block
extern bool displayECL;

//control display quit
extern bool closing;

// USE THESE STTEINGS TO CHANGE SPEED (on different spec computers)
// Set speed (steps)
extern GLdouble movementSpeed;
extern GLdouble rotationSpeed;

#endif // !MOVEMENTHANDLER_H