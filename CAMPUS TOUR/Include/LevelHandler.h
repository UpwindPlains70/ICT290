#ifndef LEVELHANDLER_H
#define LEVELHANDLER_H
#pragma once
#include "CollisionHandler.h"
#include "MapLevel.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

/**
	 * @brief defines all functions relating to levels
	 *
	 * @author Peter Neve
	 * @version 01
	 * @date 7/09/2021, level change
	 * 
	 * @author Mark Burns
	 * @version 02
	 * @date 7/09/2021, level maps
	 * 
	 * @author Peter Neve
	 * @version 03
	 * @date 15/09/2021, level maps gen redo (fixed movement)
	 * 
	 * @author Mark Burns
	 * @version 04
	 * @date 17/09/2021, Level map reader (.csv)
	 *  
	 * @author Peter Neve
	 * @version 05
	 * @date 18/09/2021, floor generation for maps
	 */
//extern enum levelStage;
extern int currLevel;

using namespace std;

extern Point4 camPos;

void teleportCamera();

///check if player has gone far enough down the stairs to teleport
bool levelZeroClear();

///Read in 3D pillar object file
void drawLevelObjects();
///draws and displays pillars in a wall structure
/// @param bool - neg
void displayWalls(bool neg);

///display the generated level map, uses set map X & Y value for size (length, width)
void displayMap();

///Size of each grid square
#define gridSquareSize 155

extern map<int, vector<LevelMap>> mapList;
///Display the floor tiles and pillars
void displayFloor();

///Sets objstical locations (update: load from file)
void CreateMaps();

void printMap();
#endif // !LEVELHANDLER_H


