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

template<int X, int Y>
class LevelMap
{
private:
	// 0 = empty, 1 = wall, 2 = ally, 3 = enemy.
	int array[X][Y];
public:
	int GetX() const { return X; }
	int GetY() const { return Y; }
	int GetValue(int x, int y) const { return array[x][y]; }
	void SetValue(int x, int y, int value) { array[x][y] = value; }
};

void teleportCamera();

///check if player has gone far enough down the stairs to teleport
bool levelZeroClear();

void levelOneDraw();

void drawWalls();
void CreateMaps();
#endif // !LEVELHANDLER_H


