//Aurthor: Peter Neve
//Version: 1
//Date: 29/08/2021
// Refactor of main
//Purpose: handle all object display, references 'DrawHandler' callList()

#ifndef DISPLAYHANDLER_H
#define DISPLAYHANDLER_H

//#include "TextureHandler.h"
#include "DoorHandler.h"

// display light fittings
extern bool lightsOn;

// calls display functions below to draw the backdrops
void DrawBackdrop();
// functions to display display lists (images) and bind them to a texture
void DisplayAboveWindowBlock();
void DisplayBench();
void DisplayBricks();
void DisplayChancPosts();
void DisplayCylinders();
void DisplayDoorPaving();
void DisplayDoorPosts();
void DisplayEntranceSteps();
void DisplayExtras();
void DisplayGrass();
void DisplayLargerTextures();
void DisplayLibraryPosts();
void DisplayMainPosts();
void DisplayPavement();
void DisplayPhysSciPosts();
void DisplayPurplePosts();
void DisplayRedPosts();
void DisplayRoof();
void DisplayStepBricks();
void DisplayLights();
void DisplayECL();

void DisplayRoom();
void DisplayRoomStairs();
void DisplayHallway();
#endif // !DISPLAYERHANDLER_H
