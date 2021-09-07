#ifndef LEVELHANDLER_H
#define LELVELHANDLER_H
#pragma once
#include "CollisionHandler.h"

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

void CreateMaps();
#endif // !LEVELHANDLER_H


