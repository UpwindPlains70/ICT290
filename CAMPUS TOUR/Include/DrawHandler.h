//Aurthor: Peter Neve
//Version: 1
//Date: 29/08/2021
//Purpose: handle all object geometry drawing, populate callList()

#ifndef DRAWHANDLER_H
#define DRAWHANDLER_H

#include <GL/glut.h>
#include "TextureHandler.h"
#include "CollisionHandler.h"

/**
	 * @brief Handles all display function calls & definitions
	 *
	 *
	 * @author Shay Leary
	 * @version 01
	 * @date March 2005, Finished
	 *
	 * @author Raymon Lua
	 * @version 02
	 * @date 28/08/2021, Added new room
	 * 
	 * @author Peter Neve
	 * @version 03
	 * @date 29/08/2021, Refactor
	 *
	 * @author Raymond Lua
	 * @version 04
	 * @date 29/08/2021, Added hallway
	 *
	 * @author Jason Botterill
	 * @version 05
	 * @date 29/08/2021, Added stairs to new room
	 *
	 * @author Mark Burns
	 * @version 06
	 * @date 29/08/2021, Added doors to new room
	 * 
	 * @author Peter Neve
	 * @version 07
	 * @date 6/09/2021, added decoration drawing DrawDecorations() from Decorations.h
	 */

/// calls functions to create display lists (below)
void CreateTextureList();

/// Glut Cylinder
extern GLUquadricObj* glu_cylinder;

/// creates different plains
void CreatePlains();

/// creates display lists
void DrawGrass();
void DrawChancPosts();
void DrawDoorPosts();
void DrawPurplePosts();
void DrawRedPosts();
void DrawMainPosts();
void DrawAboveWindowBlock();
void DrawDoorPaving();
void DrawPhysSciPosts();
void DrawLibraryPosts();
void DrawBricks();
void DrawPavement();
void DrawExtras();
void DrawRoof();
void DrawEntranceSteps();
void DrawLargerTextures();
void DrawLights();
void DrawBench();
void DrawCylinders();
void DrawAngledRoofBeam(int listNo, GLdouble x, GLdouble y, GLdouble z, GLdouble beamSize);
void DrawAngledRoofBeam2(int listNo, GLdouble x, GLdouble y, GLdouble z, GLdouble beamSize);
void DrawStepBricks();
void DrawMapExit();
void DrawECL();

void DrawRoom();
void DrawRoomStairs();
void DrawHallway();
void DrawHallwayStairs();
#endif