#include "LevelHandler.h"

enum levelStage { zero, one, two, three };
levelStage lvlStage = zero;
//Point4 camPos = { 0.0, 8000.0, 0.0, 90.0 };
Point4 camPos = { 32720.0, 8000.0, 37000.0, 90.0 };

GLdouble currXPos;
GLdouble currYPos;
GLdouble currZPos;

LevelMap<7, 7> level1Map;


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

void levelOneDraw()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(0.5f, 0.5f, 0.5f);
	glLineWidth(100.0f);
	//North
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 50500.0f);
	glScalef(100000.0f, 6000.0f, 100000.0f);
	glutSolidCube(1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutWireCube(1.1f);
	glPopMatrix();

	//South
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -50500.0f - ((level1Map.GetY() - 1) * 1000));
	glScalef(100000.0f, 6000.0f, 100000.0f);
	glutSolidCube(1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutWireCube(1.1f);
	glPopMatrix();

	//East
	glPushMatrix();
	glTranslatef(50500.0f + ((level1Map.GetY() - 1) * 1000), 0.0f, 0.0f);
	glScalef(100000.0f, 6000.0f, 100000.0f);
	glutSolidCube(1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutWireCube(1.1f);
	glPopMatrix();

	//West
	glPushMatrix();
	glTranslatef(-50500.0f, 0.0f, 0.0f);
	glScalef(100000.0f, 6000.0f, 100000.0f);
	glutSolidCube(1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutWireCube(1.1f);
	glPopMatrix();

	//Floor
	glPushMatrix();
	glTranslatef(0.0f, -1.0f, 0.0f);
	glScalef(100000.0f, 1.0f, 100000.0f);
	glutSolidCube(1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutWireCube(1.1f);
	glPopMatrix();

	//Lines

	//Walls
}

void CreateMaps()
{
	//level 1 Map
	for (int a = 0; a < level1Map.GetX(); a++)
	{
		for (int b = 0; b < level1Map.GetY(); b++)
		{
			level1Map.SetValue(a, b, 0);
		}
	}
}