//GUI lidrary
#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl2.h"

#include <math.h>
#include <GL/glut.h>
#include <time.h>
#include <iostream>

//#include <windows.h> // only used if mouse is required (not portable)
#include "DisplayHandler.h"
#include "DrawHandler.h"
#include "MovementHandler.h"
#include "LevelHandler.h"
#include "DataHandler.h"


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

// Our state
bool show_demo_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

void my_display_code()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGLUT_NewFrame();

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}

	// Rendering
	ImGui::Render();
	ImGuiIO& io = ImGui::GetIO();
	glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);

	glutPostRedisplay();
}

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

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	
	// Setup Platform/Renderer backends
	ImGui_ImplGLUT_Init();
	ImGui_ImplOpenGL2_Init();

		//Smoothness
	glutIdleFunc(Display);

	//interaction
	glutMotionFunc(ImGui_ImplGLUT_MotionFunc);
	glutMouseFunc(Mouse);

	glutTimerFunc(TIMERSECS, animate, 0);
	
	glutReshapeFunc(reshape);
	glutMainLoop();

	// Cleanup
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplGLUT_Shutdown();
	ImGui::DestroyContext();
	
	return(0);
}

GLfloat light_position[] = { 32720.0, 10500.0, 37000.0 , 1};
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

	//Enable lighting
	glEnable(GL_LIGHTING); 
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// set the world co-ordinates (used to set quadrants for bounding boxes)
	cam.SetWorldCoordinates(36000.0, 43200.0);
	// turn collision detection on (level zero)
		cam.SetCollisionDetectionOn(true);
	// set number of bounding boxes required
	cam.SetNoBoundingBoxes(82);  // originally started with 19 
	// set starting position of user
	//cam.Position(32720.0, 10500.0, 37000.0, 90.0);
	cam.Position(0.0, 9500.0, 0.0, 180.0);//Level testing pos

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
	
	//Get Data
	GetCharacterData();
	GetEnemyData();
	GetAbilityData();
	GetEnemyPerLevelData();


	currTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
}

//--------------------------------------------------------------------------------------
//  Main Display Function
//--------------------------------------------------------------------------------------
void Display()
{
		//Turn collisions off for all levels except zero
	if (currLevel != 0)
		cam.SetCollisionDetectionOn(false);

	// check for movement
	cam.CheckCamera();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (closing) exit(0);
	///Enable object shading from light
	/*glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_NORMALIZE);*/
	// DISPLAY TEXTURES
	//enable texture mapping
	glEnable (GL_TEXTURE_2D);
	glPushMatrix();
		// displays the welcome screen
		if (DisplayWelcome) cam.DisplayWelcomeScreen (width, height, 1, tp.GetTexture(WELCOME));
		// displays the exit screen
		if (DisplayExit) cam.DisplayWelcomeScreen (1000, 1900, 0, tp.GetTexture(Group_Photo) );
		// displays the map
		if (DisplayMap) cam.DisplayMap(width, height, tp.GetTexture(MAP));
		// display no exit sign (position check should really be in an object, but didn't have time)
		if (currLevel == 0) {
			if ((cam.GetLR() > 35500.0) && (cam.GetFB() < 25344.0) ||
				(cam.GetLR() > 34100.0) && (cam.GetFB() > 41127.0))
			{
				cam.DisplayNoExit(width, height, tp.GetTexture(NO_EXIT));
			}
		}
				// set the movement and rotation speed according to frame count
		IncrementFrameCount();
		cam.SetMoveSpeed (stepIncrement);
		cam.SetRotateSpeed (angleIncrement);
		// display images
		DrawBackdrop();
		
	glPopMatrix();
	glDisable (GL_TEXTURE_2D);

	//glDisable(GL_COLOR_MATERIAL);

		//Display GUI
	my_display_code();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	// clear buffers
	//glFlush();*/
	glutSwapBuffers();
}

//--------------------------------------------------------------------------------------
void reshape(int w, int h)
{
	ImGui_ImplGLUT_ReshapeFunc(w, h);
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
