#include "LevelHandler.h"

enum levelStage { zero, one, two, three };
levelStage lvlStage = one;
Point4 camPos = { 0.0, 9500.0, 0.0, 90.0 };

GLdouble currXPos;
GLdouble currYPos;
GLdouble currZPos;

LevelMap<7, 7> level1Map;

Point3D gameFloor[4] = { {1000, 9000, 1000},{1000, 9000, -1000},{-1000, 9000, -1000},{-1000, 9000, 1000} };
Point3D wall[4] = { {1000, 9000, 1000},{1000, 10000, 1000},{-1000, 10000, 1000},{-1000, 9000, 1000} };

void teleportCamera()
{
	//Change background colour to black
	glClearColor(0.1, 0.1, 0.1, 1.0);

	//change camera position
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
	glColor3f(0, 0, 0);
	//Wall East
	drawWalls();
	/*glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));
		glBegin(GL_POLYGON);
			glTexCoord2f(0.0, 0.0);
			glVertex3fv(wall[0]);
			glTexCoord2f(0.0, 1.0);
			glVertex3fv(wall[1]);
			glTexCoord2f(1.0, 1.0);
			glVertex3fv(wall[2]);
			glTexCoord2f(1.0, 0.0);
			glVertex3fv(wall[3]);
		glEnd();
	glPopMatrix();

	//Wall West
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));
		glRotatef(0, 0, 1, 0);
		glBegin(GL_POLYGON);
			glTexCoord2f(0.0, 0.0);
			glVertex3fv(wall[0]);
			glTexCoord2f(0.0, 1.0);
			glVertex3fv(wall[1]);
			glTexCoord2f(1.0, 1.0);
			glVertex3fv(wall[2]);
			glTexCoord2f(1.0, 0.0);
			glVertex3fv(wall[3]);
		glEnd();
	glPopMatrix();

	//Wall North
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));
		glRotatef(90, 0, 1, 0);
		glBegin(GL_POLYGON);
			glTexCoord2f(0.0, 0.0);
			glVertex3fv(wall[0]);
			glTexCoord2f(0.0, 1.0);
			glVertex3fv(wall[1]);
			glTexCoord2f(1.0, 1.0);
			glVertex3fv(wall[2]);
			glTexCoord2f(1.0, 0.0);
			glVertex3fv(wall[3]);
		glEnd();
	glPopMatrix();

	//Wall South
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));
		glRotatef(-90, 0, 1, 0);
		glBegin(GL_POLYGON);
			glTexCoord2f(0.0, 0.0);
			glVertex3fv(wall[0]);
			glTexCoord2f(0.0, 1.0);
			glVertex3fv(wall[1]);
			glTexCoord2f(1.0, 1.0);
			glVertex3fv(wall[2]);
			glTexCoord2f(1.0, 0.0);
			glVertex3fv(wall[3]);
		glEnd();
	glPopMatrix();*/

	//Floor
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));
		glBegin(GL_POLYGON);
			glTexCoord2f(0.0, 0.0);
			glVertex3fv(gameFloor[0]);
			glTexCoord2f(0.0, 1.0);
			glVertex3fv(gameFloor[1]);
			glTexCoord2f(1.0, 1.0);
			glVertex3fv(gameFloor[2]);
			glTexCoord2f(1.0, 0.0);
			glVertex3fv(gameFloor[3]);
		glEnd();
	glPopMatrix();

	//Lines
}

void drawWalls()
{
	for (int i = -90; i <= 180 ; i += 90)
	{
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));				
				glRotatef(i, 0, 1, 0);
				glBegin(GL_POLYGON);
					glTexCoord2f(0.0, 0.0);
					glVertex3fv(wall[0]);
					glTexCoord2f(0.0, 1.0);
					glVertex3fv(wall[1]);
					glTexCoord2f(1.0, 1.0);
					glVertex3fv(wall[2]);
					glTexCoord2f(1.0, 0.0);
					glVertex3fv(wall[3]);
				glEnd();
			glPopMatrix();
		/*glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));
			glRotatef(i, 1, 1, 0);
			glBegin(GL_POLYGON);
				glTexCoord2f(0.0, 0.0);
				glVertex3fv(wall[0]);
				glTexCoord2f(0.0, 1.0);
				glVertex3fv(wall[1]);
				glTexCoord2f(1.0, 1.0);
				glVertex3fv(wall[2]);
				glTexCoord2f(1.0, 0.0);
				glVertex3fv(wall[3]);
			glEnd();
		glPopMatrix();*/

	}
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