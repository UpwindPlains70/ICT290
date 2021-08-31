#include "DoorHandler.h"

//int dx = 0;
float prevTime;
float currTime;

door1 front;
door2 backL;
door2 backR;


//Made by Mark Burns
void animate(int value)
{
	glutTimerFunc(TIMERSECS, animate, 0);
	prevTime = currTime;
	currTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	float dT = currTime - prevTime;
	int camX;
	int camY;
	int camZ;
	cam.getPosition(camX, camY, camZ);

	//Front Door
	if ((camX > 33200 && camX < 35600) && (camZ > 36300 && camZ < 37800))
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
	if ((camX > 33200 && camX < 35600) && (camZ > 36300 && camZ < 37800))
	{
		backL.state = 1;
		if ((backL.orientation < backL.loOrientation) && (backL.orientation >= backL.cOrientation))
		{
			backL.moving = true;
		}
		else
		{
			backL.orientation = backL.loOrientation;
			backL.moving = false;
		}
	}
	else if ((camX > 33200 && camX < 35600) && (camZ > 36300 && camZ < 37800))
	{
		backL.state = 1;
		if ((backL.orientation > backL.roOrientation) && (backL.orientation = backL.cOrientation))
		{
			backL.moving = true;
		}
		else
		{
			backL.orientation = backL.roOrientation;
			backL.moving = false;
		}
	}
	else
	{
		backL.state = 0;
		if (backL.orientation != backL.cOrientation)
		{
			front.moving = true;
		}
	}
	if (backL.moving == true)
	{
		if ((backL.state == -1) || (backL.state == 0 && backL.orientation > backL.cOrientation))
		{
			backL.loOrientation -= backL.speed * dT;
		}
		else if ((backL.state == 1) || (backL.state == 0 && backL.orientation < backL.cOrientation))
		{
			backL.roOrientation += backL.speed * dT;
		}
	}

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
	front.openPos.z = 37520.0f;
	front.closePos.x = 0.0f;
	front.closePos.y = 0.0f;
	front.closePos.z = 36920.0f;
	front.pos.x = 34330.0f;
	front.pos.y = 10450.0f;
	front.pos.z = 36920.0f;
	front.scale.x = 50.0f;
	front.scale.y = 1500.0f;
	front.scale.z = 560.0f;

	//Back Double Doors
	backL.orientation = 0.0;
	backL.loOrientation = -90.0;
	backL.cOrientation = 0.0;
	backL.roOrientation = 90.0;
	backL.state = 0;
	backL.moving = false;
	backL.speed = 10.0;
	backL.pos.x = 37560.0f;
	backL.pos.y = 10450.0f;
	backL.pos.z = 38000.0f;
	backL.scale.x = 50.0f;
	backL.scale.y = 1500.0f;
	backL.scale.z = 500.0f;
	backR.orientation = 180.0;
	backR.loOrientation = 90.0;
	backR.cOrientation = 180.0;
	backR.roOrientation = 270.0;
	backR.state = 0;
	backR.moving = false;
	backR.speed = 10.0;
	backR.pos.x = 37560.0f;
	backR.pos.y = 10450.0f;
	backR.pos.z = 38500.0f;
	backR.scale.x = 50.0f;
	backR.scale.y = 1500.0f;
	backR.scale.z = 500.0f;
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
	glutSolidCube(1.0f);
	glPopMatrix();

	//Back Double Doors
	glPushMatrix();
	glTranslatef(backL.pos.x, backL.pos.y, backL.pos.z);
	glRotatef(backL.orientation, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, backL.scale.z / 2.0);
	glScalef(backL.scale.x, backL.scale.y, backL.scale.z);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(backR.pos.x, backR.pos.y, backR.pos.z);
	glRotatef(backR.orientation, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, backR.scale.z / -2.0);
	glScalef(backR.scale.x, backR.scale.y, backR.scale.z);
	glutSolidCube(1.0f);
	glPopMatrix();
}