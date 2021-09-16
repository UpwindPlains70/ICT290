#ifndef LEVELHANDLER_H
#define LELVELHANDLER_H
#pragma once
#include "CollisionHandler.h"
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
	 * @date 15/09/2021, level maps updates (fixed movement)
	 */
extern enum levelStage;
extern levelStage lvlStage;

extern Point4 camPos;

template<int X, int Z>
class LevelMap
{
private:
	// 0 = empty, 1 = wall, 2 = ally, 3 = enemy.
	int array[X][Z];
public:
	int GetX() const { return X; }
	int GetZ() const { return Z; }
	int GetValue(int x, int z) const { return array[x][z]; }
	void SetValue(int x, int z, int value) { array[x][z] = value; }
};

void teleportCamera();

///check if player has gone far enough down the stairs to teleport
bool levelZeroClear();

void levelOneDraw();
void drawWalls();

///Read in 3D pillar object file
void drawPillar();
///draws and displays pillars in a wall structure
/// @param bool - neg
void displayWalls(bool neg);

///display the generated level map, uses set map X & Y value for size (length, width)
void displayMap();

///Size of each grid square
#define gridSquareSize 155

///Draw grid lines
void drawLines();

///Sets objstical locations (update: load from file)
void CreateMaps();
#endif // !LEVELHANDLER_H


