#include <math.h>
#include <GL/glut.h>
#include <time.h>
#include <iostream>

//#include <windows.h> // only used if mouse is required (not portable)
#include "DisplayHandler.h"
#include "DrawHandler.h"
#include "MovementHandler.h"
#include "LevelHandler.h"

GLdouble stepIncrement;
GLdouble angleIncrement;
int frameCount = 0;
clock_t lastClock = 0;

// ratio of screen
float ratio;

// initializes setting
void myinit();

// display functions
void Display();
void reshape(int w, int h);

void IncrementFrameCount();

// deletes image and clears memory
void DeleteImageFromMemory(unsigned char* tempImage);

//--------------------------------------------------------------------------------------
//  Main function
//--------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,500);
	glutCreateWindow("Murdoch University Campus Tour");

	myinit();

	glutIgnoreKeyRepeat(1);
	glutSpecialFunc(movementKeys);
	glutSpecialUpFunc(releaseKey);
	glutKeyboardUpFunc (releaseKeys);
	glutKeyboardFunc(keys);

	glutDisplayFunc(Display);
	glutIdleFunc(Display);
	glutMouseFunc(Mouse);

	// ONLY USE IF REQUIRE MOUSE MOVEMENT
	//glutPassiveMotionFunc(mouseMove);
	//ShowCursor(FALSE);

	glutTimerFunc(TIMERSECS, animate, 0);
	
	glutReshapeFunc(reshape);
	glutMainLoop();
	return(0);
}

//--------------------------------------------------------------------------------------
//  Initialize Settings
//--------------------------------------------------------------------------------------
void myinit()
{
	// set background (sky colour)
	glClearColor(97.0/255.0, 140.0/255.0, 185.0/255.0, 1.0);

	// set perpsective
	gluLookAt(0.0, 1.75, 0.0,
		      0.0, 1.75, -1,
			  0.0f,1.0f,0.0f);

	// settings for glut cylinders
	glu_cylinder = gluNewQuadric();
    gluQuadricTexture(glu_cylinder, GL_TRUE );

	// set the world co-ordinates (used to set quadrants for bounding boxes)
	cam.SetWorldCoordinates(36000.0, 43200.0);
	// turn collision detection on (level zero)
	//if (lvlStage == 0)
		cam.SetCollisionDetectionOn(true);
	// set number of bounding boxes required
	cam.SetNoBoundingBoxes(24);  // originally started with 19 
	// set starting position of user
	cam.Position(32720.0, 10500.0, 37000.0, 90.0);

	CreatePlains();

	// creates bounding boxes and places in array
	CreateBoundingBoxes();
	// copies bounding boxes from array to linked lists (one fopr each quadrant)
	cam.InitiateBoundingBoxes();

	// load texture images and create display lists
	CreateTextureList();
	CreateTextures();
	
	//Doors
	CreateDoors();

	//Maps
	CreateMaps();

	currTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
}

//--------------------------------------------------------------------------------------
//  Main Display Function
//--------------------------------------------------------------------------------------
void Display()
{
	// check for movement
	cam.CheckCamera();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (closing) exit(0);

	// DISPLAY TEXTURES
	//enable texture mapping
	glEnable (GL_TEXTURE_2D);
	glPushMatrix();
		// displays the welcome screen
		if (DisplayWelcome) cam.DisplayWelcomeScreen (width, height, 1, tp.GetTexture(WELCOME));
		// displays the exit screen
		if (DisplayExit) cam.DisplayWelcomeScreen (width, height, 0, tp.GetTexture(EXIT) );
		// displays the map
		if (DisplayMap) cam.DisplayMap(width, height, tp.GetTexture(MAP));
		// display no exit sign (position check should really be in an object, but didn't have time)
		if ((cam.GetLR() > 35500.0) && (cam.GetFB() < 25344.0) ||
			(cam.GetLR() > 34100.0) && (cam.GetFB() > 41127.0))
		{
			cam.DisplayNoExit(width, height,tp.GetTexture(NO_EXIT));
		}
				// set the movement and rotation speed according to frame count
		IncrementFrameCount();
		cam.SetMoveSpeed (stepIncrement);
		cam.SetRotateSpeed (angleIncrement);
		// display images
		DrawBackdrop();
		//DisplayDoors(); //should be in DrawBackdrop()
		
	glPopMatrix();
	glDisable (GL_TEXTURE_2D);

	// clear buffers
	glFlush();
	glutSwapBuffers();
}

//--------------------------------------------------------------------------------------
void reshape(int w, int h)
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0) h = 1;
	ratio = 1.0f * w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45,ratio,1,250000);
	glMatrixMode(GL_MODELVIEW);
}

//--------------------------------------------------------------------------------------
//  Delete raw image and clear memory
//--------------------------------------------------------------------------------------
void DeleteImageFromMemory(unsigned char* tempImage)
{
	tempImage = NULL;
		if (tempImage == NULL)
	{
		delete [] tempImage;
	}
}

//--------------------------------------------------------------------------------------
//  Increments frame count used for setting movement speed
//--------------------------------------------------------------------------------------
void IncrementFrameCount()
{
	double t = ((GLdouble)(clock()-lastClock))/(GLdouble)CLOCKS_PER_SEC;
	frameCount ++;

	// reset after t
	if (t > 0.1)
	{
		stepIncrement = t/frameCount * 1400;
		angleIncrement = t/frameCount;
		frameCount = 0;
		lastClock = clock();
	}
}
