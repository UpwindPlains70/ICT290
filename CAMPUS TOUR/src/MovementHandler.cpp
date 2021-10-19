//Aurthor: Peter Neve
//Version: 1
//Date: 29/08/2021
//Purpose: defines camera movement and UI overlay

#include <GL/glut.h>
#include <iostream>

#include "MovementHandler.h"

using std::cout;
using std::endl;

// screen width and height
int width, height;

// display campus map
bool DisplayMap = false;
// display welcome screen
bool DisplayWelcome = true;

// display ECL block
bool displayECL = true;

//control display quit
bool closing = false;

// USE THESE STTEINGS TO CHANGE SPEED (on different spec computers)
// Set speed (steps)
GLdouble movementSpeed = 1.0;
GLdouble rotationSpeed = 0.005;

//--------------------------------------------------------------------------------------
void keys(unsigned char key, int x, int y)
{
	//Put in if condition to restrict controls
	ImGui_ImplGLUT_KeyboardFunc(key, x, y);
	
	if (gameState != NotReady) {
		if (currLevel == 0)
			TourControls(key, x, y);
		else
			GameControls(key, x, y);
	}
}

void TourControls(unsigned char key, int x, int y)
{
	switch (key)
	{
		// step left
	case 'Z':
	case 'z':
		cam.DirectionLR(-1);
		break;
		// step right
	case 'X':
	case 'x':
		cam.DirectionLR(1);
		break;
		// look up
	case 'Q':
	case 'q':
		cam.DirectionLookUD(1);
		break;
		// look down
	case 'A':
	case 'a':
		cam.DirectionLookUD(-1);
		break;
		// display campus map
	case 'm':
	case 'M':
	{
		if (DisplayMap)
		{
			DisplayMap = false;
		}
		else
		{
			DisplayMap = true;
		}
	}
	break;
	// exit tour (escape key)
	case 27:
	{
		cam.SetRotateSpeed(0.0f);
		cam.SetMoveSpeed(0.0f);
		DisplayExit = true;
	}
	break;
	// display welcome page (space key)
	case ' ':
	{
		if (DisplayWelcome)
		{
			cam.SetRotateSpeed(rotationSpeed);
			cam.SetMoveSpeed(movementSpeed);
			DisplayWelcome = false;
		}
		else
		{
			cam.SetRotateSpeed(0.0f);
			cam.SetMoveSpeed(0.0f);
			DisplayWelcome = true;
		}
	}
	break;
	// display light fittings
	case 'O':
	case 'o':
	{
		if (lightsOn)
		{
			lightsOn = false;
		}
		else
		{
			lightsOn = true;
		}
	}
	break;

	case 'P':
	case 'p':
	{
		// Display ECL Block
		if (displayECL)
		{
			displayECL = false;
		}
		else
		{
			displayECL = true;
		}
	}
	break;

	}
}

void GameControls(unsigned char key, int x, int y)
{
	switch (key)
	{	// characterUp
	case 'I':
	case 'i':
		if (canIJKL)
		{
			movePlayer(0, 1);
		}
		break;
		// characterLeft
	case 'L':
	case 'l':
		if (canIJKL)
		{
			movePlayer(-1, 0);
		}
		break;
		// characterDown
	case 'K':
	case 'k':
		if (canIJKL)
		{
			movePlayer(0, -1);
		}
		break;
		// characterRight
	case 'J':
	case 'j':
		if (canIJKL)
		{
			movePlayer(1, 0);
		}
		break;
		// ability 1
	case '1':
		abilityPressed(1);
		break;
		// ability 2
	case '2':
		abilityPressed(2);
		break;
		// ability 3
	case '3':
		abilityPressed(3);
		break;
		// end Turn
	case '`':
		endTurn();
		break;
	}
}

//--------------------------------------------------------------------------------------
// Keyboard Functions
//--------------------------------------------------------------------------------------
void movementKeys(int key, int x, int y)
{
	GLdouble m_x = 0;
	GLdouble m_y = 0;
	GLdouble m_z = 0;
	cam.getPosition(m_x, m_y, m_z);
	cout << "Position: " << m_x << " " << m_y << " " << m_z << endl;
	if (gameState != NotReady)
	{
		switch (key)
		{
		case GLUT_KEY_LEFT:
			cam.DirectionRotateLR(-1);
			break;

		case GLUT_KEY_RIGHT:
			cam.DirectionRotateLR(1);
			break;

		case GLUT_KEY_UP:
			cam.DirectionFB(1);
			break;

		case GLUT_KEY_DOWN:
			cam.DirectionFB(-1);
			break;
		}

		auto sprintCheck = glutGetModifiers();

		if (sprintCheck == GLUT_ACTIVE_SHIFT) {
			movementSpeed = 2.0;
		}
		else {
			movementSpeed = 1.0;
		}
	}
	else
		releaseKey(key, x, y);
}

//--------------------------------------------------------------------------------------
void releaseKey(int key, int x, int y)
{
	switch (key)
	{
		// rotate left or right
	case GLUT_KEY_LEFT:
	case GLUT_KEY_RIGHT:
		cam.DirectionRotateLR(0);
		break;
		// move backwards or forwards
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN:
		cam.DirectionFB(0);
		break;
	}
}

//--------------------------------------------------------------------------------------
void releaseKeys(unsigned char key, int x, int y)
{
		//Prevent backspace loop error
	ImGui_ImplGLUT_KeyboardUpFunc(key, x, y);
	switch (key)
	{
		// step left or right
	case 'x':
	case 'X':
	case 'z':
	case 'Z':
		cam.DirectionLR(0);
		break;
		// look left up or down
	case 'a':
	case 'A':
	case 'q':
	case 'Q':
		cam.DirectionLookUD(0);
		break;
	}
}

//--------------------------------------------------------------------------------------
//  Mouse Buttons
//--------------------------------------------------------------------------------------
void Mouse(int button, int state, int x, int y)
{
	ImGui_ImplGLUT_MouseFunc(button, state, x, y);
	// exit tour if clicked on exit splash screen
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
	{
		if ((DisplayExit) && (x <= width / 2.0 + 256.0) && (x >= width / 2.0 - 256.0)
			&& (y <= height / 2.0 + 256.0) && (y >= height / 2.0 - 256.0))
		{
			//DeleteImageFromMemory(image);
			closing = true;
		}
		/*if ((x <= width / 2.0 + 256.0) && (x >= width / 2.0 - 256.0)
			&& (y <= height / 2.0 + 256.0) && (y >= height / 2.0 - 256.0) && popUpMessageState != None)
		{

			popUpMessage = false; // closes the pop up message 
			popUpMessageState = None;  // Stops the enum state from being anything else eg if it used to be TotalWin, it is now set to None
		}*/
	}
}

//--------------------------------------------------------------------------------------
//  Mouse Movements (NOT USED)
//  Can be used to rotate around screen using mouse, but keyboard used instead
//--------------------------------------------------------------------------------------
void mouseMove(int x, int y)
{
	if (x < 0)
		cam.DirectionRotateLR(0);
	else if (x > width)
		cam.DirectionRotateLR(0);
	else if (x > width / 2.0)
	{
		cam.DirectionRotateLR(1);
		//Display();
		glutWarpPointer(width / 2.0, height / 2.0);
	}
	else if (x < width / 2.0)
	{
		cam.DirectionRotateLR(-1);
		//Display();
		glutWarpPointer(width / 2.0, height / 2.0);
	}
	else
		cam.DirectionRotateLR(0);
	if (y < 0 || y > height)
		cam.DirectionLookUD(0);

	else if (y > height / 2.0) {
		cam.DirectionLookUD(-1);
		//Display();
		glutWarpPointer(width / 2.0, height / 2.0);
	}
	else if (y < height / 2.0) {
		cam.DirectionLookUD(1);
		//Display();
		glutWarpPointer(width / 2.0, height / 2.0);
	}
	else
		cam.DirectionLookUD(0);

	glutPostRedisplay();
}
