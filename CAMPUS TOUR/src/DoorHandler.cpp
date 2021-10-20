#include "DoorHandler.h"
#include <iostream>

//int dx = 0;
float prevTime;
float currTime;

door1 front;
door2 backL;
door2 backR;
float angle = 0;

using namespace std;

//Made by Mark Burns
void animate(int value)
{
	glutTimerFunc(TIMERSECS, animate, 0);
	prevTime = currTime;
	currTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	float dT = currTime - prevTime;
	GLdouble camX;
	GLdouble camY;
	GLdouble camZ;
	cam.getPosition(camX, camY, camZ);

	++angle/2;
	if (angle >= 360)
		angle = 0;
	//Front Door
	if ((camX > 33200 && camX < 35600) && (camZ > 36300 && camZ < 37800) && !playerSelection)
	{
		front.state = 1;
		if (front.pos.z >= front.openPos.z)
		{
			front.pos.z = front.openPos.z;
			front.moving = false;
		}
		else
		{
			front.moving = true;
		}
	}
	else
	{
		front.state = 0;
		if (front.pos.z <= front.closePos.z)
		{
			front.pos.z = front.closePos.z;
			front.moving = false;
		}
		else
		{
			front.moving = true;
		}
	}
	if (front.moving == true)
	{
		if (front.state == 0)
		{
			front.pos.z -= front.speed * dT;
		}
		else if (front.state == 1)
		{
			front.pos.z += front.speed * dT;
		}
	}

	//Back Left Door
	if ((camX > 37600 && camX < 38700) && (camZ > 37600 && camZ < 38400) && !playerSelection)
	{
		if (backL.state != 1)
		{
			backL.state = -1;
			if (backL.orientation - backL.loOrientation > 1)
			{
				backL.moving = true;
			}
			else
			{
				backL.orientation = backL.loOrientation;
				backL.moving = false;
			}
		}
		
	}
	else if ((camX > 36500 && camX < 37600) && (camZ > 37600 && camZ < 38400) && !playerSelection)
	{
		if (backL.state != -1)
		{
			backL.state = 1;
			if (backL.roOrientation - backL.orientation > 1)
			{
				backL.moving = true;
			}
			else
			{
				backL.orientation = backL.roOrientation;
				backL.moving = false;
			}
		}
	}
	else
	{
		backL.state = 0;
		if (backL.cOrientation + 1 > backL.orientation && backL.cOrientation - 1 < backL.orientation)
		{
			backL.orientation = backL.cOrientation;
			backL.moving = false;
		}
		else
		{
			backL.moving = true;
		}
	}

	//Back Right Door
	if ((camX > 36500 && camX < 37600) && (camZ > 38200 && camZ < 38800) && !playerSelection)
	{
		if (backR.state != 1)
		{
			backR.state = -1;
			if (backR.orientation - backR.loOrientation > 1)
			{
				backR.moving = true;
			}
			else
			{
				backR.orientation = backR.loOrientation;
				backR.moving = false;
			}
		}

	}
	else if ((camX > 37600 && camX < 38700) && (camZ > 38200 && camZ < 38800) && !playerSelection)
	{
		if (backR.state != -1)
		{
			backR.state = 1;
			if (backR.roOrientation - backR.orientation > 1)
			{
				backR.moving = true;
			}
			else
			{
				backR.orientation = backR.roOrientation;
				backR.moving = false;
			}
		}
	}
	else
	{
		backR.state = 0;
		if (backR.cOrientation + 1 > backR.orientation && backR.cOrientation - 1 < backR.orientation)
		{
			backR.orientation = backR.cOrientation;
			backR.moving = false;
		}
		else
		{
			backR.moving = true;
		}
	}

	//moving
	if (backL.moving == true)
	{
		if (backL.state == -1)
		{
			backL.orientation -= backL.speed * dT;
		}
		else if (backL.state == 1)
		{
			backL.orientation += backL.speed * dT;
		}
		else if (backL.state == 0)
		{
			if (backL.orientation > backL.cOrientation)
			{
				backL.orientation -= backL.speed * dT;
			}
			else
			{
				backL.orientation += backL.speed * dT;
			}
		}
	}
	if (backR.moving == true)
	{
		if (backR.state == -1)
		{
			backR.orientation -= backR.speed * dT;
		}
		else if (backR.state == 1)
		{
			backR.orientation += backR.speed * dT;
		}
		else if (backR.state == 0)
		{
			if (backR.orientation > backR.cOrientation)
			{
				backR.orientation -= backR.speed * dT;
			}
			else
			{
				backR.orientation += backR.speed * dT;
			}
		}
	}
	//Update();
	glutPostRedisplay();
}


//--------------------------------------------------------------------------------------
// Create each door
//  Made by Mark Burns
//--------------------------------------------------------------------------------------
void CreateDoors()
{
	//Front Slide Door
	front.orientation = 0;
	front.state = 0;
	front.moving = false;
	front.speed = 2000.0;
	front.openPos.x = 0.0f;
	front.openPos.y = 0.0f;
	front.openPos.z = 38020.0f;
	front.closePos.x = 0.0f;
	front.closePos.y = 0.0f;
	front.closePos.z = 36600.0f;
	front.pos.x = 34330.0f;
	front.pos.y = 10000.0f;
	front.pos.z = 36600.0f;
	front.scale.x = 50.0f;
	front.scale.y = 1500.0f;
	front.scale.z = 560.0f;

	//Back Double Doors
	////L
	backL.orientation = 0.0;
	backL.loOrientation = -90.0;
	backL.cOrientation = 0.0;
	backL.roOrientation = 90.0;
	backL.state = 0;
	backL.moving = false;
	backL.speed = 30.0;
	backL.pos.x = 37570.0f;
	backL.pos.y = 10000.0f;
	backL.pos.z = 37505.0f;
	backL.scale.x = 50.0f;
	backL.scale.y = 1500.0f;
	backL.scale.z = 400.0f;
	////R
	backR.orientation = 180;
	backR.loOrientation = 90;
	backR.cOrientation = 180;
	backR.roOrientation = -90;
	backR.state = 0;
	backR.moving = false;
	backR.speed = 30.0;
	backR.pos.x = 37570.0f;
	backR.pos.y = 10000.0f;
	backR.pos.z = 38990.0f;
	backR.scale.x = 50.0f;
	backR.scale.y = 1500.0f;
	backR.scale.z = 400.0f;
}

//--------------------------------------------------------------------------------------
//  Display each door
//  Made by Mark Burns
//--------------------------------------------------------------------------------------
void DisplayDoors()
{
	//Front Slide Door
	glPushMatrix();
	glTranslatef(front.pos.x, front.pos.y, front.pos.z);
	glRotatef(front.orientation, 0.0f, 1.0f, 0.0f);
	glScalef(front.scale.x, front.scale.y, front.scale.z);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 15, 0);
	glVertex3f(0, 15, 2);
	glVertex3f(0, 0, 2);
	glEnd();
	glPopMatrix();

	//Back Double Doors
	///L
	glPushMatrix();
	//to position
	glTranslatef(backL.pos.x, backL.pos.y, backL.pos.z);
	//rotation
	glRotatef(backL.orientation, 0.0f, 1.0f, 0.0f);
	//scale?
	//glTranslatef(0.0f, 0.0f, backL.scale.z * 0.5f);
	glScalef(backL.scale.x, backL.scale.y, backL.scale.z);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(285));   // WALL_BRICK_YZ
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);

	glTexCoord2f(0, 15);
	glVertex3f(0, 15, 0);

	glTexCoord2f(1, 15);
	glVertex3f(0, 15, 2);

	glTexCoord2f(1, 0);
	glVertex3f(0, 0, 2);

	glEnd();
	glPopMatrix();

	/// R
	glPushMatrix();
	glTranslatef(backR.pos.x, backR.pos.y, backR.pos.z);
	glRotatef(backR.orientation, 0.0f, 1.0f, 0.0f);
	glScalef(backR.scale.x, backR.scale.y, backR.scale.z);
	//glutSolidCube(1.0f);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(285)); // WALL_BRICK_YZ
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0, 15);
	glVertex3f(0, 15, 0);
	glTexCoord2f(1, 15);
	glVertex3f(0, 15, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(0, 0, 1.75);
	glEnd();
	glPopMatrix();
}