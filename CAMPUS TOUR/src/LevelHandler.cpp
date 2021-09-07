#include "LevelHandler.h"

enum levelStage { zero, one, two, three };
levelStage lvlStage = zero;
Point4 camPos = { 32720.0, 8000.0, 37000.0, 90.0 };

GLdouble currXPos;
GLdouble currYPos;
GLdouble currZPos;

void teleportCamera()
{
	cam.Position(camPos[0], camPos[1], camPos[2], camPos[3]);
}

bool levelZeroClear()
{
	cam.getPosition(currXPos, currYPos, currZPos);

	if (currYPos < 9000.0)
	{
		lvlStage = one;
		teleportCamera();
		return true;
	}
	return false;
}