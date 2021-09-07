#ifndef LEVELHANDLER_H
#define LELVELHANDLER_H

#include "CollisionHandler.h"

extern enum levelStage;
extern levelStage lvlStage;

extern Point4 camPos;

void teleportCamera();

///check if player has gone far enough down the stairs to teleport
bool levelZeroClear();
#endif // !LEVELHANDLER_H


