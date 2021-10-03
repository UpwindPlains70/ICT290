#ifndef DISPLAYHANDLER_H
#define DISPLAYHANDLER_H

#include "DoorHandler.h"
#include "Decorations.h"
#include "LevelHandler.h"

/**
	 * @brief Handles all display function calls & definitions
	 *
	 *
	 * @author Shay Leary
	 * @version 01
	 * @date March 2005, Finished
	 *
	 * @author Raymon Lua
	 * @version 03
	 * @date 28/08/2021, Added new room
	 * 
	 * @author Peter Neve
	 * @version 02
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
	 * @date 6/09/2021, Added Decorations.h for displaying decoration objects
	 */

/// display light fittings
extern bool lightsOn;

//entities Display
void DisplayEntities();
/// calls display functions below to draw the backdrops
void DrawBackdrop();
/// functions to display display lists (images) and bind them to a texture
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

/// new room added by Raymond Lua
void DisplayRoom();
/// new stairs added by Jason Botterill
void DisplayRoomStairs();
void DisplayHallway();
void DisplayHallwayStairs();


#endif // !DISPLAYERHANDLER_H
