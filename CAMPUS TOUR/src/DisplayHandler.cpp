//Aurthor: Peter Neve
//Version: 1
//Date: 29/08/2021
//Purpose: handle all object display, references 'DrawHandler' callList()

#include "DisplayHandler.h"

bool lightsOn;
//--------------------------------------------------------------------------------------
//  Called from the main display function to draw the backdrop (all images)
//--------------------------------------------------------------------------------------
void DrawBackdrop()
{
	if (!levelZeroClear() && currLevel == 0) {
		DisplayAboveWindowBlock();
		DisplayBench();
		DisplayBricks();
		DisplayChancPosts();
		DisplayCylinders();
		DisplayDoorPaving();
		DisplayDoorPosts();
		DisplayEntranceSteps();
		DisplayExtras();
		DisplayGrass();
		DisplayLargerTextures();
		DisplayLibraryPosts();
		DisplayMainPosts();
		DisplayPavement();
		DisplayPhysSciPosts();
		DisplayPurplePosts();
		DisplayRedPosts();
		DisplayRoof();
		DisplayStepBricks();
		if (lightsOn) DisplayLights();

		DisplayRoom();
		DisplayRoomStairs();
		DisplayHallway();
		DisplayDoors();
		DisplayHallwayStairs();

		DisplayDecorations();
	}
	else
	{
		displayMap();
	}
}

void DisplayEntities(){
	if (displayEnt) {
		/*
			glPushMatrix();
				glTranslatef(80, 9050, 80);
				glColor3f(1, 1, 0);
				glutSolidCube(100);
			glPopMatrix();
		*/

		int repeatX = mapList[currLevel].at(mapID).GetX();
		int repeatZ = mapList[currLevel].at(mapID).GetZ();

		int wallValX = 114.28 * repeatX;
		int wallValZ = 91.42 * repeatZ;
		int floorValX = 67.14 * repeatX;
		int floorValZ = 67.14 * repeatZ;
		//for each enemy
		for (int i = 0; i < nowEnemies.size(); i++) {
			//get x and z
			int posX = nowEnemies[i].getPosX();
			int posZ = nowEnemies[i].getPosZ();
			//get translated area on map
			//glTranslatef(-floorValX, 9000, -floorValZ);//(1,1)
			glTranslatef(-floorValX * posX, 9000, -floorValZ * posZ);
			//draw enemy
			//glColor3f(1, 0, 0);
			glutSolidCube(200);
		//endFor
		}
		//do same for players
		for (int i = 0; i < playerList.size(); i++) {
			//get x and z
			int posX = playerList[i].getPosX();
			int posZ = playerList[i].getPosZ();
			//get translated area on map
			//glTranslatef(-floorValX, 9000, -floorValZ);//(1,1)
			glTranslatef(-floorValX * posX, 9000, -floorValZ * posZ);
			//draw player
			//glColor3f(0, 0, 1);
			glutSolidCube(150);
			//endFor
		}
	}
}

//Made by Raymond Lua
void DisplayHallway() {
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));
	glCallList(777);	//right wall
	glCallList(778);	//left wall

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KURO));
	glCallList(779);	//Back wall 
	
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(HALLWAY_FLOOR_1)); // replacing SHADOW_BRICK to hallwayfloor
	glCallList(780);	//floor

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_STEPS_TOP));
	glCallList(781);	//roof
}
void DisplayHallwayStairs() {
	glPushMatrix();
		glTranslatef(100.0, 0.0, 0.0);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEP_PAVING_1));
		for (int i = 1000; i < 1320; i++) glCallList(i);

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SHADOW_BRICK));
		for (int i = 1320; i < 1640; i++) glCallList(i);
	glPopMatrix();

	//abyss
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KURO));
	glCallList(1641);
}


//--------------------------------------------------------------------------------------
// Display the chancellery windoe and door posts
//--------------------------------------------------------------------------------------
void DisplayChancPosts()
{
	// Windowposts Chanc (downstairs)
	step = 0.0;
	for (int i = 0; i < 14; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, 0.0, step);
		if ((i != 1) && (i != 2) && (i != 10) && (i != 11))
		{
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_CHANC_FRONT));
			glCallList(11);
		}
		if ((i != 1) && (i != 10))
		{
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_CHANC_RIGHT));
			glCallList(12);
		}
		if ((i != 2) && (i != 11))
		{
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_CHANC_LEFT));
			glCallList(13);
		}

		glPopMatrix();
		step += 960.0;
	}

	//  Windowledges Chanc (downstairs)
	step = 0.0;
	for (int i = 0; i < 11; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, 0.0, step);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_CHANC_FRONT));
		glCallList(14);

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_CHANC_TOP));
		glCallList(15);
		glPopMatrix();
		if ((i == 0) || (i == 8)) step += 960.0;
		step += 960.0;
	}

	// Windowposts & Ledges Chanc (upstairs)
	glPushMatrix();
	step = 0.0;
	glTranslatef(0.0, 1023.0, 0.0);
	for (int i = 0; i < 14; i++)
	{
		glTranslatef(0.0, 0.0, step);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_CHANC_FRONT));
		glCallList(11);

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_CHANC_RIGHT));
		glCallList(12);

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_CHANC_LEFT));
		glCallList(13);
		if (i != 13)
		{
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_CHANC_FRONT));
			glCallList(14);

			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_CHANC_TOP));
			glCallList(15);
		}
		step = +960.0;
	}
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LEDGE_END_1));
	glCallList(235);
	glPushMatrix();
	glTranslatef(0.0, 320.0, 7447.0);
	glCallList(235);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 1024.0, 0.0);
	glCallList(235);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 320.0, 5527);
	glCallList(235);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 320.0, 6551);
	glCallList(235);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 320.0, 8471);
	glCallList(235);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 1152.0, 19031.0);
	glCallList(235);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LEDGE_END_2));
	glCallList(236);
	glCallList(237);
	glPushMatrix();
	glTranslatef(0.0, 0.0, -960.0);
	glCallList(237);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, -8640.0);
	glCallList(237);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, -9600.0);
	glCallList(237);
	glPopMatrix();

	//glPushMatrix();
		//glTranslatef(0.0, 320.0, -9600.0);
		//glCallList(237);
//	glPopMatrix();

	// angled corner of window ledges
	glPushMatrix();
	glTranslatef(0.0, 1024.0, 0.0);
	glCallList(236);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 320.0, 7383.0);
	glCallList(236);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 320.0, 5463);
	glCallList(236);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 320.0, 6551);
	glCallList(236);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 320.0, 8471);
	glCallList(236);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 1152.0, 19031.0);
	glCallList(236);
	glPopMatrix();
}


//--------------------------------------------------------------------------------------
// Display Door Posts
//--------------------------------------------------------------------------------------
void DisplayDoorPosts()
{
	// Door Posts Chanc
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DOOR_POST_SECURITY));
	glCallList(199);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DOOR_POST_CHANC));
	glPushMatrix();
	glTranslatef(0.0, 0.0, 8640.0);
	glCallList(25);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DOOR_POST_CHANC));
	glCallList(26);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 8640.0);
	glCallList(26);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DOOR_SIDEPOST_CHANC));
	glCallList(27);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 866.0);
	glCallList(27);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, 8640.0);
	glCallList(27);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, 9506.0);
	glCallList(27);
	glPopMatrix();
}


//--------------------------------------------------------------------------------------
// Display blocks above Windows and Posts
//--------------------------------------------------------------------------------------
void DisplayAboveWindowBlock()
{
	// Blocks Above Windows Chanc & Phys Sci
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_BLOCK));
	glCallList(20);
	glCallList(223);
	glCallList(229);
	// Blocks containing text
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_CHANC_TEXT));
	glCallList(224);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_CHANC_TEXT_2));
	glCallList(225);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_CHANC_TEXT_3));
	glCallList(230);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_PHYS_SCI_TEXT));
	glCallList(226);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 9728.0);
	glCallList(226);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_BLOCK_2));
	glCallList(44);
	glCallList(46);
	glCallList(96);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_BLOCK_CHANC));
	glCallList(22);
	glPushMatrix();
	glTranslatef(0.0, 1024.0, 0.0);
	glCallList(22);
	glPopMatrix();
	glCallList(24);
	glPushMatrix();
	glTranslatef(0.0, 1024.0, 0.0);
	glCallList(24);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_BLOCK_3));
	glCallList(227);
	glCallList(228);
	glCallList(21);
	glCallList(23);
	glCallList(95);
	glPushMatrix();
	glTranslatef(99.84, 0.0, 0.0);
	glCallList(95);
	glPopMatrix();
	glCallList(231);
	glCallList(43);
	glCallList(45);
	glCallList(53);	// aboves posts
	glPushMatrix();
	glTranslatef(128.0, 0.0, 0.0);
	glCallList(53);
	glPopMatrix();
	glCallList(68);
	glCallList(71);	// above post between chanc and phys sci

	glCallList(213);
	glPushMatrix();
	glTranslatef(0.0, 1024.0, 0.0);
	glCallList(213);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_EDGE_3B));
	glCallList(49);
	glPushMatrix();
	glTranslatef(0.0, 1024.0, 0.0);
	glCallList(49);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 1024.0, 15783.0);
	glCallList(49);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2068.0, 310.0, -17244.0);
	glCallList(49);
	glPopMatrix();
	glCallList(425);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_BLOCK_XY_3));
	glCallList(50);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 807.0);
	glCallList(50);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, 9567.0);
	glCallList(50);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, 11103.0);
	glCallList(50);
	glPopMatrix();
	for (int i = 64; i < 67; i++) glCallList(i);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 128.0);
	glCallList(66);
	glPopMatrix();
	glCallList(208);
	glCallList(233);
	glCallList(234);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_UNDER_POSTS));
	glCallList(54);
	glCallList(67);
	glCallList(72);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BELOW_ROOF_FILL));
	glCallList(39);

	// -------------------------------- Above under Mainpost by Library -----------------------
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_UNDER_POSTS_2));
	glCallList(69);
	glCallList(232);

	// -------------------------------- Above Library ------------------------------------
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_LIB));
	for (int i = 55; i < 57; i++) glCallList(i);
	glCallList(238);
	glCallList(415);
	glCallList(417);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_UNDER_LIB));
	for (int i = 70; i < 71; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_EDGE_3B_LIB));
	glCallList(209);
	step = 17536.0;
	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();
		glTranslatef(step, 0.0, 0.0);
		glCallList(209);
		glPopMatrix();
		step += 128.0;
	}

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_EDGE_4B_LIB));
	glCallList(210);
	step = 17536.0;
	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();
		glTranslatef(step, 0.0, 0.0);
		glCallList(210);
		glPopMatrix();
		step += 128.0;
	}

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_UNDER_4B));
	for (int i = 211; i < 213; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_LIB_TEXT));
	glCallList(239);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_LIB_TEXT_2));
	glCallList(416);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_TICKETS_TEXT));
	glCallList(418);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_CHANC_EDGE));
	glCallList(424);

}

//--------------------------------------------------------------------------------------
// Display Purple Posts by Guild Shop
//--------------------------------------------------------------------------------------
void DisplayPurplePosts()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PURPLE_POST));
	glCallList(29);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 4800.0);
	glCallList(29);
	glPopMatrix();
	glCallList(30);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 960.0);
	glCallList(30);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, 2880.0);
	glCallList(30);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PURPLE_POSTSIDE));
	glCallList(31);
	glPushMatrix();
	glTranslatef(0.0, 0.0, -112.0);
	glCallList(31);
	glPopMatrix();

	step = 865.0;
	for (int i = 0; i < 3; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, 0.0, step);
		glCallList(31);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, 0.0, step + 78.0);
		glCallList(31);
		glPopMatrix();
		step += 960.0;
		if (i == 1) step += 960.0;
	}
	glPushMatrix();
	glTranslatef(0.0, 0.0, 4688.0);
	glCallList(31);
	glPopMatrix();
	glCallList(32);
}

//--------------------------------------------------------------------------------------
// Display Red Posts by Sta Travel Shop
//--------------------------------------------------------------------------------------
void DisplayRedPosts()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(RED_POST));
	glCallList(33);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 1399.0);
	glCallList(33);
	glPopMatrix();
	glCallList(34);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(RED_POSTSIDE));
	glPushMatrix();
	glTranslatef(0.0, 0.0, 240.0);
	glCallList(35);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, 256.0);
	glCallList(35);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, 1639.0);
	glCallList(35);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, 1095.0);
	glCallList(35);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, 1191.0);
	glCallList(35);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, 1655.0);
	glCallList(35);
	glPopMatrix();
}


//--------------------------------------------------------------------------------------
// Display Main Posts
//--------------------------------------------------------------------------------------
void DisplayMainPosts()
{
	step = 0.0;
	stepLength = 0.0;
	step2 = 0.0;
	for (int j = 0; j < 2; j++)
	{
		glPushMatrix();
		glTranslatef(stepLength, 0.0, step2);
		for (int i = 0; i < 17; i++)
		{
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
			glPushMatrix();
			glTranslatef(0.0, 0.0, step);
			glCallList(18);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(0.0, 0.0, step + 128.0);
			glCallList(18);
			glPopMatrix();
			if ((i == 7) && (j == 0))	// between chanc and phys sci
			{
				glPushMatrix();
				glTranslatef(4008.0, 0.0, step);
				glCallList(18);
				glPopMatrix();
				glPushMatrix();
				glTranslatef(4008.0, 0.0, step + 128.0);
				glCallList(18);
				glPopMatrix();
			}

			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST_2));
			glPushMatrix();
			glTranslatef(0.0, 0.0, step);
			glCallList(19);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(128.0, 0.0, step);
			glCallList(19);
			glPopMatrix();
			if ((i == 7) && (j == 0))	// between chanc and phys sci
			{
				glPushMatrix();
				glTranslatef(4008.0, 0.0, step);
				glCallList(19);
				glPopMatrix();
			}
			step += 1930.0;
		}
		stepLength -= 27192.0;
		step2 -= 32810.0;
		glPopMatrix();
	}

	// library front
	step = -1940.0;
	for (int i = 0; i < 13; i++)
	{
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
		glPushMatrix();
		glTranslatef(step, 0.0, 30880.0);
		glCallList(18);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(step, 0.0, 31008.0);
		glCallList(18);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST_2));
		glPushMatrix();
		glTranslatef(step, 0.0, 30880.0);
		glCallList(19);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(step + 128.0, 0.0, 30880.0);
		glCallList(19);
		glPopMatrix();
		step -= 1940.0;
	}

	// first on chanc steps
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
	glCallList(51);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 128.0);
	glCallList(51);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST_2));
	glCallList(52);
	glPushMatrix();
	glTranslatef(128.0, 0.0, 0.0);
	glCallList(52);
	glPopMatrix();
}

//--------------------------------------------------------------------------------------
//  Display Window and Door Posts on Phys SCi Building
//--------------------------------------------------------------------------------------
void DisplayPhysSciPosts()
{
	step = 0.0;
	for (int i = 0; i < 16; i++)
	{
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_FRONT));
		glTranslatef(0.0, 0.0, step);
		glCallList(36);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_RIGHT));
		glCallList(37);
		glPopMatrix();
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_LEFT));
		glTranslatef(0.0, 0.0, step + 77);
		glCallList(38);
		glPopMatrix();
		step += 960.0;
	}

	step = 960.0;
	for (int i = 0; i < 4; i++)
	{
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_FRONT));
		glTranslatef(0.0, -1024.0, step);
		glCallList(36);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_RIGHT));
		glCallList(37);
		glPopMatrix();
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_LEFT));
		glTranslatef(0.0, -1024.0, step + 77);
		glCallList(38);
		glPopMatrix();
		step += 960.0;
	}
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_FRONT));
	glTranslatef(0.0, -1024.0, 7718.0);
	glCallList(36);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_RIGHT));
	glCallList(37);
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_LEFT));
	glTranslatef(0.0, -1024.0, 7718.0 + 77);
	glCallList(38);
	glPopMatrix();

	// WindowLedges Phys Sci (toilets downstairs)
	step = 960.0;
	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, -832.0, step);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_PS_FRONT));
		glCallList(16);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_PS_TOP));
		glCallList(17);
		glPopMatrix();
		step += 1920.0;
	}

	step = 6758.0;
	stepLength = -832.0;
	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, stepLength, step);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_PS_FRONT));
		glCallList(16);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_PS_TOP));
		if (i == 1) glCallList(17);
		glPopMatrix();
		step += 960.0;
		stepLength -= 256.0;
	}
	// shops downstairs phys sci
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_PS_BOTT));
	for (int i = 40; i < 42; i++) glCallList(i);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_PS_FRONT));
	glCallList(42);

	// WindowLedges Phys Sci (upstairs)
	step = 0.0;
	for (int i = 0; i < 15; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, 0.0, step);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_PS_FRONT));
		glCallList(16);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_PS_TOP));
		glCallList(17);
		glPopMatrix();
		step += 960.0;
	}
}

//--------------------------------------------------------------------------------------
//  Display Paving Around Shop Doorway
//--------------------------------------------------------------------------------------
void DisplayDoorPaving()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DOORPAVE_1));
	glCallList(47);
	glCallList(48);
}

//--------------------------------------------------------------------------------------
// Display window and door posts of library
//--------------------------------------------------------------------------------------
void DisplayLibraryPosts()
{
	stepLength = 0.0;
	for (int j = 0; j < 2; j++)
	{
		glPushMatrix();
		glTranslatef(0.0, stepLength, 0.0);
		step = 0.0;
		for (int i = 0; i < 15; i++)
		{
			if (!(i > 12 && j == 0))
			{
				glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_LIB_FRONT));
				glTranslatef(step, 0.0, 0.0);
				glCallList(57);
				glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_LIB_RIGHT));
				glCallList(58);
				glPopMatrix();
				glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_LIB_LEFT));
				glTranslatef(step + 77, 0.0, 0.0);
				glCallList(59);
				glPopMatrix();
				step -= 1088.0;
			}
		}
		glPopMatrix();
		stepLength += 1054;
	}
	stepLength = 0.0;
	for (int j = 0; j < 2; j++)
	{
		glPushMatrix();
		glTranslatef(0.0, stepLength, 0.0);
		// WINDOWLEDGE_LIB
		step = 0.0;
		for (int i = 0; i < 13; i++)
		{
			if (!(i > 10 && j == 0))
			{
				glPushMatrix();
				glTranslatef(step, 0.0, 0.0);
				glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_LIB_A));
				glCallList(60);
				glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_LIB_B));
				glCallList(61);
				glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_LIB_TOP_A));
				glCallList(62);
				glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_LIB_TOP_B));
				glCallList(63);
				glPopMatrix();
			}
			step -= 1088.0;
		}
		glPopMatrix();
		stepLength += 1024;
	}
	// first ledge upstairs
	glPushMatrix();
	glTranslatef(1088.0, 1024.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_LIB_A));
	glCallList(60);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_LIB_B));
	glCallList(61);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_LIB_TOP_A));
	glCallList(62);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_LIB_TOP_B));
	glCallList(63);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TICKET_COUNTER_TOP));
	glCallList(442);
	glCallList(444);
	glCallList(446);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TICKET_COUNTER_EDGE));
	glCallList(445);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TICKET_COUNTER_EDGE_2));
	glCallList(443);
	glPushMatrix();
	glTranslatef(1152.0, 0.0, 0.0);
	glCallList(443);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TICKET_COUNTER_EDGE_3));
	glCallList(447);
	glPushMatrix();
	glTranslatef(1152.0, 0.0, 0.0);
	glCallList(447);
	glPopMatrix();
}

//--------------------------------------------------------------------------------------
//  Display Pavement
//--------------------------------------------------------------------------------------
void DisplayPavement()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT));
	for (int i = 72; i < 74; i++) glCallList(i);
	glCallList(28);
	for (int i = 81; i < 89; i++) glCallList(i);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 1920.0);
	glCallList(86);
	glPopMatrix();

	for (int i = 247; i < 250; i++) glCallList(i);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 8640.0);
	glCallList(248);
	glPopMatrix();
	glCallList(241);
	glCallList(428);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT_TOP));
	for (int i = 91; i < 93; i++) glCallList(i);
	glCallList(246);
	glCallList(243);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT_TOP_FLIP));
	glCallList(74);
	glCallList(245);
	glCallList(244);
	glCallList(242);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENTSIDE_LEFT));
	glCallList(75);
	glCallList(436);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENTSIDE_RIGHT));
	glCallList(76);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENTSIDE_TOP));
	glCallList(77);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT));
	glCallList(78);
	glCallList(79);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT_16));
	glCallList(80);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT_CORNER_1));
	glCallList(93);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT_CORNER_2));
	glCallList(94);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT_FLIP));
	for (int i = 89; i < 91; i++) glCallList(i);
	glCallList(240);
	glPushMatrix();
	glTranslatef(-26848.0, 0.0, 0.0);
	glCallList(240);
	glPopMatrix();
}


//--------------------------------------------------------------------------------------
//  New Room 
// 33993431 - Raymond Lau
//--------------------------------------------------------------------------------------
void DisplayRoom() {
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));
	glCallList(666);		//XY left left
	glCallList(667);		//XY left right
	glCallList(668);		//XY right right
	glCallList(669);		//XY right left

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_YZ));
	glCallList(670);
	glCallList(671);
	glCallList(672);
	glCallList(673);

	//floor
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SHADOW_BRICK));
	glCallList(674);		//main room floor
	glCallList(675);		//enterance floor

	//roof
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_STEPS_TOP));
	glCallList(676);		//main room roof
	glCallList(677);		//enterance roof

	// New Textures ( pinboard ) Jason
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PIN_BOARD_1));
	glCallList(782);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PIN_BOARD_2));
	glCallList(783);

	// Exit door on left side of room
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(EXIT_DOOR_1));
	glCallList(784);

	// Stairs wall once you walk up the stairs
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STAIRS_TOP));
	glCallList(785);

	// Window next to the right of the entrance door 
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ENTRANCE_DOOR_1));
	glCallList(786);

	// Floor level sign
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(FLOOR_LEVEL_SIGN));
	glCallList(787);

	//Hallway door1
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(HALLWAY_DOOR_1));
	glCallList(788);

	//Hallway door2
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(HALLWAY_DOOR_2));
	glCallList(789);

	//Graffiti 1
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GRAFFITI_1));
	glCallList(790);
}

void DisplayRoomStairs() { // Made by Jason
	glPushMatrix();
	glTranslatef(100.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEP_PAVING_1));
	for (int i = 678; i < 694; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEP_EDGE));
	for (int i = 694; i < 710; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEP_PAVING_1));
	for (int i = 710; i < 713; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEP_EDGE));
	for (int i = 713; i < 716; i++) glCallList(i);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_YZ));  // begins drawing the walls 
    glCallList(716);
	glPushMatrix();
		glTranslatef(-1500.0, 0.0, 0.0);
		glCallList(716);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1500.0, 0.0, 2000.0);
		glCallList(717);
	glPopMatrix();
	
}

//--------------------------------------------------------------------------------------
// Display Wall Bricks
//--------------------------------------------------------------------------------------
void DisplayBricks()
{
	// WALL_BRICK_YZ
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_YZ));
	for (int i = 101; i < 111; i++) glCallList(i);
	for (int i = 112; i < 126; i++) glCallList(i);
	for (int i = 191; i < 195; i++) glCallList(i);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 1920.0);
	glCallList(109);
	glCallList(110);
	glCallList(394);
	glPopMatrix();
	glCallList(222);
	glCallList(394);
	glCallList(396);
	glCallList(397);

	// bricks with security sign
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_SEC_SIGN));
	glCallList(398);

	// WALL_BRICK_USD_YZ
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_USD_YZ));
	for (int i = 200; i < 202; i++) glCallList(i);
	glCallList(188);


	// WALL_BRICK_XY
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));
	for (int i = 135; i < 165; i++) glCallList(i);
	for (int i = 217; i < 222; i++) glCallList(i);
	glPushMatrix();
	glTranslatef(0.0, 0.0, -1792.0);
	glCallList(136);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 1024.0, 0.0);
	glCallList(152);
	glPopMatrix();
	for (int i = 195; i < 198; i++) glCallList(i);
	glCallList(392);
	for (int i = 430; i < 434; i++) glCallList(i);

	// Brick with map on
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAP_2));
	glCallList(434);

	// WALL_BRICK_GAP_YZ
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_GAP_YZ));
	for (int i = 180; i < 182; i++) glCallList(i);
	glPushMatrix();
	glTranslatef(0.0, 1024.0, 0.0);
	glCallList(180);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, -1920.0);
	glCallList(181);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_GAP2_YZ));
	glCallList(182);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_GAP_1));
	for (int i = 183; i < 185; i++) glCallList(i);

	// WALL_BRICK_XY_END
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY_END));
	for (int i = 165; i < 168; i++) glCallList(i);
	glCallList(134);
	glCallList(185);
	glCallList(187);
	glCallList(399);
	glPushMatrix();
	glTranslatef(-32.0, 0.0, 640.0);
	glCallList(399);
	glPopMatrix();
	step = -832.0;
	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, 0.0, step);
		glCallList(166);
		glPopMatrix();
		step += 1920;
	}
	glPushMatrix();
	glTranslatef(0.0, 0.0, 321.0);
	glCallList(167);
	glPopMatrix();
	for (int i = 131; i < 132; i++) glCallList(i);
	glCallList(132);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 960.0);
	glCallList(132);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, 8640.0);
	glCallList(132);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, 9600.0);
	glCallList(132);
	glPopMatrix();
	glCallList(133);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY_87WIDTH));
	glCallList(130);
	glCallList(186);

	// WALL_BRICK_YZ_END
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_YZ_END));
	for (int i = 126; i < 130; i++) glCallList(i);
	glPushMatrix();
	glTranslatef(-896.0, 0.0, 0.0);
	glCallList(128);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 1088.0, 0.0);
	glCallList(129);
	glCallList(168);
	glPopMatrix();
	for (int i = 168; i < 170; i++) glCallList(i);
	glCallList(390);
	glCallList(391);
	glCallList(393);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_3_4));
	glCallList(189);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SHADOW_BRICK));
	glCallList(190);
}

//--------------------------------------------------------------------------------------
// Display Roof
//--------------------------------------------------------------------------------------
void DisplayRoof()
{
	// main roof planks
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_PLANKS));
	for (int i = 250; i < 253; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_BEAM_1));
	// corner beams
	for (int i = 1; i < 6; i++) glCallList(i);
	step = -1689.0;
	for (int i = 0; i < 85; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, 0.0, step);
		glCallList(253);
		glPopMatrix();
		step += 386.0;
	}
	glPushMatrix();
	glTranslatef(0.0, 0.0, -2005.0);
	glCallList(253);
	glPopMatrix();
	glCallList(254);

	step = 214.0;
	for (int i = 0; i < 8; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, 0.0, step);
		glCallList(254);
		glPopMatrix();
		step += 386.0;
	}

	glPushMatrix();
	glTranslatef(0.0, 0.0, 3216.0);
	glCallList(254);
	glPopMatrix();

	// Beams between library and phys sci
	step = 0.0;
	for (int i = 0; i < 5; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, 0.0, step);
		glCallList(298);
		glPopMatrix();
		step += 386.0;
	}

	glPushMatrix();
	glTranslatef(0.0, 0.0, -99.0);
	glCallList(298);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, 1798.0);
	glCallList(298);
	glPopMatrix();

	// Library Roof
	step = 281.0;
	for (int i = 0; i < 70; i++)
	{
		glPushMatrix();
		glTranslatef(step, 0.0, 0.0);
		glCallList(296);
		glPopMatrix();
		step += 388.0;
	}

	// spacers
	for (int i = 202; i < 204; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_BEAM_4));
	for (int i = 6; i < 11; i++)
	{
		glCallList(i);
		glPushMatrix();
		glTranslatef(0.0, 0.0, 32.0);
		glCallList(i);
		glPopMatrix();
	}

	step = -1689.0;
	for (int i = 0; i < 85; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, 0.0, step);
		glCallList(255);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, 0.0, step + 32.0);
		glCallList(255);
		glPopMatrix();
		step += 386.0;
	}

	glPushMatrix();
	glTranslatef(0.0, 0.0, -2005.0);
	glCallList(255);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, -1973.0);
	glCallList(255);
	glPopMatrix();

	step = 214.0;
	for (int i = 0; i < 8; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, 0.0, step);
		glCallList(256);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, 0.0, step + 32.0);
		glCallList(256);
		glPopMatrix();
		step += 386.0;
	}

	glPushMatrix();
	glTranslatef(0.0, 0.0, 3216.0);
	glCallList(256);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, 32.0);
	glCallList(256);
	glPopMatrix();

	// Beams between library and phys sci
	step = 0.0;
	for (int i = 0; i < 5; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, 0.0, step);
		glCallList(299);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, 0.0, step + 32.0);
		glCallList(299);
		glPopMatrix();
		step += 386.0;
	}

	glPushMatrix();
	glTranslatef(0.0, 0.0, -67.0);
	glCallList(299);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, 1798.0);
	glCallList(299);
	glPopMatrix();

	// Library Roof
	step = 281.0;
	for (int i = 0; i < 70; i++)
	{
		glPushMatrix();
		glTranslatef(step, 0.0, 0.0);
		glCallList(297);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(step + 32.0, 0.0, 0.0);
		glCallList(297);
		glPopMatrix();

		step += 388.0;
	}

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_PLANKS_2));
	glCallList(257);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_BEAM_3));
	// corner beams
	for (int i = 170; i < 175; i++)
	{
		glCallList(i + 5);
		glPushMatrix();
		glTranslatef(32.0, 0.0, 0.0);
		glCallList(i + 5);
		glPopMatrix();
	}
	glCallList(426);
	glCallList(427);
	glPushMatrix();
	glTranslatef(0.0, 49.0, 3248.0);
	glCallList(427);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 49.0, 19031.0);
	glCallList(427);
	glPopMatrix();

	// spacer top of chanc
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_BEAM_3_TOP));
	glCallList(204);
	glCallList(205);
	glPushMatrix();
	glTranslatef(64.0, 0.0, 0.0);
	glCallList(205);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_BEAM_2));
	// spacers
	for (int i = 97; i < 101; i++) glCallList(i);
	// corner beams
	for (int i = 170; i < 175; i++) glCallList(i);


	// Top of Roof
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_TOP));
	for (int i = 214; i < 216; i++) glCallList(i);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_TOP_LIB));
	glCallList(216);
}

//--------------------------------------------------------------------------------------
// Display Steps
//--------------------------------------------------------------------------------------
void DisplayEntranceSteps()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEP_PAVING_1));
	for (int i = 258; i < 274; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEP_EDGE));
	for (int i = 274; i < 290; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEP_PAVING_1));
	for (int i = 290; i < 293; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEP_EDGE));
	for (int i = 293; i < 296; i++) glCallList(i);


	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEPS_LIBRARY));
	step = 0.0;
	step2 = -51.0;
	for (int i = 0; i < 10; i++)
	{
		glPushMatrix();
		glTranslatef(step, step2, 0.0);
		glCallList(206);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(step, step2, 965.0);
		glCallList(206);
		glPopMatrix();
		step += 128.0;
		step2 += -51.0;
	}
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEPS_LIBRARY_TOP));
	glCallList(207);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 965.0);
	glCallList(207);
	glPopMatrix();
}

//--------------------------------------------------------------------------------------
// Display Bench
//--------------------------------------------------------------------------------------
void DisplayBench()
{
	step2 = 3860.0;
	for (int j = 0; j < 11; j++)
	{
		glPushMatrix();
		glTranslatef(0.0, 0.0, step2);

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_TOP));
		glCallList(400);

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_SIDE));
		glCallList(401);
		glPushMatrix();
		glTranslatef(0.0, 0.0, 480.0);
		glCallList(401);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_SIDE_2));
		glPushMatrix();
		glTranslatef(0.0, 0.0, 50.0);
		glCallList(402);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, 0.0, 430.0);
		glCallList(402);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_EDGE_TOP));
		step = 0.0;
		for (int i = 0; i < 2; i++)
		{
			glPushMatrix();
			glTranslatef(0.0, 0.0, step);
			glCallList(403);
			glPushMatrix();
			glTranslatef(192.0, 0.0, 0.0);
			glCallList(403);
			glPopMatrix();
			glPopMatrix();
			step += 430;
		}
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_EDGE_SIDE));
		step = 0.0;
		for (int i = 0; i < 2; i++)
		{
			glPushMatrix();
			glTranslatef(step, 0.0, 0.0);
			glCallList(404);
			glPopMatrix();;
			step += 192;
		}

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_EDGE));
		glCallList(405);
		glPushMatrix();
		glTranslatef(192.0, 0.0, 0.0);
		glCallList(405);
		glPopMatrix();
		glCallList(406);
		glPushMatrix();
		glTranslatef(192.0, 0.0, 0.0);
		glCallList(406);
		glPopMatrix();

		glPopMatrix();
		step2 += 1930.0;
		if (j == 4) step2 += 5790.0;
	}

	step2 = 1940.0;
	GLdouble vertStep = 0.0;
	for (int j = 0; j < 8; j++)
	{
		glPushMatrix();
		glTranslatef(step2, 0.0, vertStep);

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_TOP));
		glCallList(407);

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_SIDE));
		glCallList(408);
		glPushMatrix();
		glTranslatef(480.0, 0.0, 0.0);
		glCallList(408);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_SIDE_2));
		glPushMatrix();
		glTranslatef(50.0, 0.0, 0.0);
		glCallList(409);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(430.0, 0.0, 0.0);
		glCallList(409);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_EDGE_TOP_2));
		step = 0.0;
		for (int i = 0; i < 2; i++)
		{
			glPushMatrix();
			glTranslatef(step, 0.0, 0.0);
			glCallList(410);
			glPushMatrix();
			glTranslatef(0.0, 0.0, 192.0);
			glCallList(410);
			glPopMatrix();
			glPopMatrix();
			step += 430;
		}
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_EDGE_3));
		step = 0.0;
		for (int i = 0; i < 2; i++)
		{
			glPushMatrix();
			glTranslatef(0.0, 0.0, step);
			glCallList(411);
			glPopMatrix();;
			step += 192;
		}

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_EDGE_2));
		glCallList(412);
		glPushMatrix();
		glTranslatef(0.0, 0.0, 192.0);
		glCallList(412);
		glPopMatrix();
		glCallList(413);
		glPushMatrix();
		glTranslatef(0.0, 0.0, 192.0);
		glCallList(413);
		glPopMatrix();

		glPopMatrix();
		step2 += 1940.0;
		if (j == 1) step2 += 1940.0;
		if (j == 5) step2 += 9700.0;
		if (j == 6)
		{
			vertStep += 1848.0;
			step2 = 5926.0;
		}
	}
}


//--------------------------------------------------------------------------------------
// Display Extras (signs etc)
//--------------------------------------------------------------------------------------
void DisplayExtras()
{
	// Rusty Man like Sculpture
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(RUSTY_MAN));
	glCallList(300);

	// Directions sign next to Sta Travel Shop
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SIGN_1));
	glCallList(301);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SIGN_1_SIDE_1));
	glCallList(302);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SIGN_1_SIDE_2));
	glCallList(303);

	// GCL1 Sign
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SIGN_2));
	glCallList(304);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SIGN_2_SIDE));
	glCallList(305);
	glPushMatrix();
	glTranslatef(384.0, 0.0, 0.0);
	glCallList(305);
	glPopMatrix();

	// KBLT
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KBLT_EDGE));
	glCallList(306);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KBLT_EDGE_2));
	glCallList(307);
	glCallList(308);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KBLT_EDGE_CORNER));
	glCallList(309);
	glPushMatrix();
	glTranslatef(2471.0, 0.0, 0.0);
	glCallList(309);
	glPopMatrix();

	// Nexus Sign
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(NEXUS_SIDE));
	glCallList(310);
	glPushMatrix();
	glTranslatef(1280.0, 0.0, 0.0);
	glCallList(310);
	glPopMatrix();

	// Glass Notice Board next to KBLT
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GLASS_B_SIDE));
	glCallList(311);
	glPushMatrix();
	glTranslatef(896.0, 0.0, 0.0);
	glCallList(311);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3904.0, 0.0, 0.0);
	glCallList(311);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(4800.0, 0.0, 0.0);
	glCallList(311);
	glPopMatrix();
	glCallList(435);
	glPushMatrix();
	glTranslatef(768.0, 0.0, 0.0);
	glCallList(435);
	glPopMatrix();

	// Security Sign on Chanc Doorway
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SECURITY_SIGN));
	glCallList(312);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SECURITY_SIGN_2));
	glCallList(313);

	//  Prospective Student Sign
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PSC_SIGN));
	glCallList(314);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PSC_SIGN_2));
	glCallList(315);

	// Staff Sign
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CO_SIGN));
	glCallList(316);

	// DRINKS MACINE
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DRINKS_SIDE_2));
	for (int i = 317; i < 319; i++) glCallList(i);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DRINKS_SIDE));
	glPushMatrix();
	glTranslatef(-1152.0, 0.0, 0.0);
	glCallList(317);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DRINKS_TOP));
	glCallList(319);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DRINKS_EDGE));
	glCallList(320);
	glPushMatrix();
	glTranslatef(-1136.0, 0.0, 0.0);
	glCallList(320);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MACHINE_SIDES));
	for (int i = 321; i < 323; i++) glCallList(i);
	glCallList(320);
	glPushMatrix();
	glTranslatef(317.12, 0.0, 0.0);
	glCallList(321);
	glPopMatrix();
	glCallList(320);
	glPushMatrix();
	glTranslatef(255.0, 0.0, 0.0);
	glCallList(322);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MACHINE_SIDES_2));
	glCallList(323);
	glPushMatrix();
	glTranslatef(350.0, 0.0, 0.0);
	glCallList(323);
	glPopMatrix();

	// Doorway Carpet
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CARPET));
	glCallList(324);
	glCallList(429);

	// No Smoking Sign
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(NO_SMOKE_SIGN));
	glCallList(326);
	glCallList(327);

	// Star Travel Sign
	step = 0.0;
	int sign = STA_TRAVEL;
	int signBack = STA_TRAVEL_2;
	int signEdge = STA_TRAVEL_EDGE;
	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, 0.0, step);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(sign));
		glCallList(328);

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(signEdge));
		glCallList(329);

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STA_TRAVEL_BRACKET));
		glCallList(330);
		glPushMatrix();
		glTranslatef(0.0, 0.0, 64.0);
		glCallList(330);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(signBack));
		glCallList(331);

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STA_TRAVEL_BOTTOM));
		glCallList(332);
		glPopMatrix();
		step -= 3840.0;
		sign = GS_SIGN;
		signBack = GS_SIGN_2;
		signEdge = GS_SIGN_EDGE;
	}

	// Telephone Boxes
	step = 0.0;
	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();
		glTranslatef(step, 0.0, 0.0);

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_BACK));
		glCallList(333);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_FRONT));
		glCallList(334);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_SIDE_1));
		glCallList(335);
		glPushMatrix();
		glTranslatef(285.0, 0.0, 0.0);
		glCallList(335);
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_FRONT_2));
		glCallList(336);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_MAIN_SIDE));
		glCallList(337);
		glPushMatrix();
		glTranslatef(285.0, 0.0, 0.0);
		glCallList(337);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_TOP_1));
		glCallList(338);
		glCallList(340);

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_SIDE_2));
		glCallList(339);
		glPushMatrix();
		glTranslatef(285.0, 0.0, 0.0);
		glCallList(339);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_TOP_2));
		glCallList(341);
		glCallList(342);

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_BOTTOM));
		glCallList(343);

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_FILL));
		glCallList(348);
		glCallList(349);
		glPushMatrix();
		glTranslatef(0.0, 0.0, 168.2);
		glCallList(349);
		glPopMatrix();
		glCallList(388);
		glPushMatrix();
		glTranslatef(275.2, 0.0, 0.0);
		glCallList(388);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_FRONT_3));
		glCallList(395);
		glPushMatrix();
		glTranslatef(269.0, 0.0, 0.0);
		glCallList(395);
		glPopMatrix();

		glPopMatrix();
		step += 384.0;
	}

	// Sides of KBLT
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KBLT_SIDE_1));
	glCallList(345);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KBLT_SIDE_2));
	glCallList(346);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KBLT_SIDE_1));
	glPushMatrix();
	glTranslatef(-2496.0, 0.0, 0.0);
	glCallList(345);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KBLT_SIDE_2));
	glPushMatrix();
	glTranslatef(-2316.0, 0.0, 0.0);
	glCallList(346);
	glPopMatrix();

	// Toilet Signs
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TOILET_WOMEN));
	glCallList(347);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TOILET_MEN));
	glPushMatrix();
	glTranslatef(0.0, 0.0, 1920.0);
	glCallList(347);
	glPopMatrix();

	// Ledge of Ticket Office
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TICKET_LEDGE));
	glCallList(419);
	glPushMatrix();
	glTranslatef(0.0, 32.0, 0.0);
	glCallList(419);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TICKET_LEDGE_EDGE));
	glCallList(420);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TICKET_LEDGE_EDGE_2));
	glCallList(421);
	glPushMatrix();
	glTranslatef(1208.0, 0.0, 0.0);
	glCallList(421);
	glPopMatrix();
}


// --------------------------------------------------------------------------------------
// Display larger textures such as windows and doors
// --------------------------------------------------------------------------------------
void DisplayLargerTextures()
{
	//Gap betweem chanc and phys sci
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_1));
	glCallList(350);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_1B));
	glCallList(351);

	// Chanc Windows Downstairrs
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_2));
	step = 1920.0;
	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, 0.0, step);
		glCallList(352);
		glPopMatrix();
		step += 2880;
	}

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_2B));
	step = 2880.0;
	for (int i = 0; i < 3; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, 0.0, step);
		glCallList(352);
		glPopMatrix();
		step += 2880;
		if (i == 2) step -= 960.0;
	}

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_2C));
	step = 6720.0;
	for (int i = 1; i < 3; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, 0.0, step);
		glCallList(352);
		glPopMatrix();
		step += 2880;
		if (i == 1) step += 1920.0;
	}

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_2D));
	glPushMatrix();
	glTranslatef(0.0, 0.0, 3840.0);
	glCallList(352);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, 10560.0);
	glCallList(352);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_2E));
	glCallList(352);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 7680.0);
	glCallList(352);
	glPopMatrix();

	//Chanc Windows Upstairs
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_2US));
	glPushMatrix();
	glTranslatef(0.0, 1023.0, 0.0);
	glCallList(352);
	glPopMatrix();
	step = 9600.0;
	for (int i = 0; i < 3; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, 1023.0, step);
		glCallList(352);
		glPopMatrix();
		step += 960;
	}

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_2USB));
	step = 960;
	for (int i = 0; i < 9; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, 1023.0, step);
		glCallList(352);
		glPopMatrix();
		step += 960;
	}

	// Physical Science upstairs
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_3));
	step = 3840.0;
	for (int i = 4; i < 14; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, 0.0, step);
		glCallList(353);
		glPopMatrix();
		step += 960;
	}
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_3B));
	step = 0.0;
	for (int i = 0; i < 6; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, 0.0, step);
		glCallList(353);
		glPopMatrix();
		step += 960.0;
		if (i == 4) step = 13440.0;
	}//--------------------------------------------------------------

	// toilets
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_4));
	step = 0.0;
	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, 0.0, step);
		glCallList(354);
		glPopMatrix();
		step += 1920;
	}
	// See draw function for details of below
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_5));
	glCallList(355);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_6));
	glCallList(356);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_7));
	glCallList(357);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_8));
	glCallList(358);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_9));
	glCallList(359);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_10));
	glCallList(360);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_11));
	glCallList(361);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_12));
	glCallList(362);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(NEXUS_SIGN));
	glCallList(363);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GLASS_BOARD));
	glCallList(364);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GLASS_BOARD_2));
	glCallList(365);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GLASS_BOARD_3));
	glCallList(366);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KBLT));
	glCallList(367);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ENTRANCE));
	glCallList(368);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ENTRANCE_2));
	glCallList(369);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(COKE_MACHINE));
	glCallList(370);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(COFFEE_MACHINE));
	glCallList(371);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SWEET_MACHINE));
	glCallList(372);

	// Phys sci door 1
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_13));
	glCallList(373);
	// Phys sci toilets
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_14));
	glCallList(374);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_14B));
	glPushMatrix();
	glTranslatef(0.0, 0.0, 1920.0);
	glCallList(374);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CHANC_DOOR_1));
	glCallList(375);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_16));
	glCallList(379);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_17));
	glCallList(380);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(EXIT_EAST));
	glCallList(381);

	// Chanc Doorways
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CHANC_DOOR_1));
	glCallList(382);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CHANC_DOOR_2));
	glPushMatrix();
	glTranslatef(0.0, 0.0, 8640.0);
	glCallList(382);
	glPopMatrix();

	// Library windows downstairs
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_1A));
	glCallList(383);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_1));
	step = 1088.0;
	for (int i = 0; i < 4; i++)
	{
		glPushMatrix();
		glTranslatef(step, 0.0, 0.0);
		glCallList(383);
		glPopMatrix();
		step += 3264;
	}

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_1B));
	step = 2176.0;
	for (int i = 0; i < 3; i++)
	{
		glPushMatrix();
		glTranslatef(step, 0.0, 0.0);
		glCallList(383);
		glPopMatrix();
		step += 3264;
	}

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_1C));
	step = 3264.0;
	for (int i = 0; i < 3; i++)
	{
		glPushMatrix();
		glTranslatef(step, 0.0, 0.0);
		glCallList(383);
		glPopMatrix();
		step += 3264.0;
	}

	// library windows upstairs
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_US_B));
	step = 2176.0;
	for (int i = 0; i < 9; i++)
	{
		glPushMatrix();
		glTranslatef(step, 0.0, 0.0);
		glCallList(384);
		glPopMatrix();
		step += 1088.0;
	}

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_US_A));
	step = 0.0;
	glCallList(384);
	glPushMatrix();
	glTranslatef(1088.0, 0.0, 0.0);
	glCallList(384);
	glPopMatrix();

	step = 11968.0;
	for (int i = 0; i < 3; i++)
	{
		glPushMatrix();
		glTranslatef(step, 0.0, 0.0);
		glCallList(384);
		glPopMatrix();
		step += 1088;
	}

	// library doorways
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_DOOR_1));
	glCallList(385);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_DOOR_2));
	glCallList(386);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_LONG));
	glCallList(387);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_LIB_FRONT));
	glCallList(389);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DOOR_POST_LIB));
	glCallList(414);
	glPushMatrix();
	glTranslatef(77.0, 0.0, 0.0);
	glCallList(414);
	glPopMatrix();

	// top of toilet door
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TOILET_DOOR_TOP));
	glCallList(422);
	glCallList(423);

	// West Exit
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(EXIT_WEST));
	glCallList(450);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_BLOCK_CHANC));
	glCallList(451);
	// window next to steps
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEP_WINDOW));
	glCallList(452);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CARPET));
	glCallList(453);

}

// --------------------------------------------------------------------------------------
// Display grass and slopes
// --------------------------------------------------------------------------------------
void DisplayGrass()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GRASS));
	glCallList(79);
	glCallList(111);
	glCallList(460);
	glCallList(477);
	for (int i = 461; i < 477; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GRASS_2));
	glCallList(198);

	// USED IF REQUIRED DARKER HILL
	//glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GRASS_HILL));
	//for (int i = 461; i < 477; i++) glCallList(i);
}

// --------------------------------------------------------------------------------------
// Display Light Fittings
// --------------------------------------------------------------------------------------
void DisplayLights()
{
	// Light Fitting
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(LIGHT));
	GLdouble beamstep = 0.0;
	for (int i = 0; i < 4; i++)
	{
		glPushMatrix();
		glTranslatef(32905.0, 11200.0, 11134.0 + beamstep);
		glRotatef(90.0, 1.0f, 0.0f, 0.0f);
		glRotatef(-90.0, 0.0f, 0.0f, 1.0f);
		glCallList(376);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(32905.0, 11265.0, 11134.0 + beamstep);
		glRotatef(90.0, 1.0f, 0.0f, 0.0f);
		glRotatef(-90.0, 0.0f, 0.0f, 1.0f);
		glCallList(376);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(32905.0, 11330.0, 11134.0 + beamstep);
		glRotatef(90.0, 1.0f, 0.0f, 0.0f);
		glRotatef(-90.0, 0.0f, 0.0f, 1.0f);
		glCallList(376);
		glPopMatrix();
		beamstep += 8492.0;
	}

	// Light Supports
	beamstep = 0.0;
	for (int i = 0; i < 4; i++)
	{
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(LIGHT_SUPPORT_2));
		step = -40.0;
		for (int k = 0; k < 2; k++)
		{
			for (int j = 0; j < 2; j++)
			{
				glPushMatrix();
				glTranslatef(step, 0.0, 0.0 + beamstep);
				glCallList(377);
				glPopMatrix();
				glPushMatrix();
				glTranslatef(step, 0.0, -40.0 + beamstep);
				glCallList(377);
				glPopMatrix();
				step += 8.0;
			}
			step += 64.0;
		}

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(LIGHT_SUPPORT));
		step = -40.0;
		for (int k = 0; k < 2; k++)
		{
			step2 = 0.0;
			for (int j = 0; j < 2; j++)
			{
				glPushMatrix();
				glTranslatef(step, 0.0, 0.0 + step2 + beamstep);
				glCallList(378);
				glPopMatrix();
				glPushMatrix();
				glTranslatef(step, 0.0, -40.0 + step2 + beamstep);
				glCallList(378);
				glPopMatrix();
				step2 += 8.0;
			}
			step += 80.0;
		}
		beamstep += 8492.0;
	}

}

// --------------------------------------------------------------------------------------
// Display drainpipe and tuckshop serving counter
// --------------------------------------------------------------------------------------
void DisplayCylinders()
{
	// drainpipe
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DRAINPIPE));
	glPushMatrix();
	glTranslatef(24200.0, 9850.0, 43090.0);
	glRotatef(90.0, 1.0f, 0.0f, 0.0f);
	glRotatef(-90.0, 0.0f, 0.0f, 1.0f);
	glRotatef(-180.0, 0.0f, 1.0f, 0.0f);
	glScalef(1.0, 1.0f, 1125.0f);
	glCallList(437);
	glPopMatrix();

	// serving counter
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(COUNTER_TOP));
	glCallList(439);
	glPushMatrix();
	glTranslatef(33800.0, 10340.0, 34848.0);
	glRotatef(90.0, 1.0f, 0.0f, 0.0f);
	glRotatef(-90.0, 0.0f, 0.0f, 1.0f);
	glCallList(441);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(COUNTER_SIDE));
	glCallList(438);
	glTranslatef(0.0, 0.0, 10.0);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(COUNTER_TOP));
	glCallList(441);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(COUNTER_SIDE));
	glCallList(440);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 276.0);
	glCallList(440);
	glPopMatrix();

}

// --------------------------------------------------------------------------------------
// Display Wall by Entrance
// --------------------------------------------------------------------------------------
void DisplayStepBricks()
{
	step = 0.0;

	for (int j = 0; j < 2; j++)
	{
		glPushMatrix();
		glTranslatef(step, 0.0, 0.0);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_STEPS));
		for (int i = 478; i < 487; i++) glCallList(i);

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_STEPS_TOP));
		for (int i = 488; i < 493; i++) glCallList(i);

		glPushMatrix();
		glTranslatef(31572.0, 9222.0, 6126.0);
		glRotatef(-18.69, 1.0f, 0.0f, 0.0f);
		glTranslatef(-31572.0, -9222.0, -6126.0);
		glCallList(493);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(31572.0, 9461.0, 7213.0);
		glRotatef(-20.31, 1.0f, 0.0f, 0.0f);
		glTranslatef(-31572.0, -9462.0, -7213.0);
		glCallList(494);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(31572.0, 9722.0, 8302.0);
		glRotatef(-17.35, 1.0f, 0.0f, 0.0f);
		glTranslatef(-31572.0, -9722.0, -8302.0);
		glCallList(495);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(31572.0, 9939.0, 9332.4);
		glRotatef(-19.83, 1.0f, 0.0f, 0.0f);
		glTranslatef(-31572.0, -9942.0, -9332.4);
		glCallList(496);
		glPopMatrix();
		glPopMatrix();
		step += -64.0;
	}

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_STEPS_COVER));
	for (int i = 497; i < 502; i++) glCallList(i);
	glPushMatrix();
	glTranslatef(31572.0, 9222.0, 6126.0);
	glRotatef(-18.69, 1.0f, 0.0f, 0.0f);
	glTranslatef(-31572.0, -9222.0, -6126.0);
	glCallList(502);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(31572.0, 9462.0, 7213.0);
	glRotatef(-20.21, 1.0f, 0.0f, 0.0f);
	glTranslatef(-31572.0, -9462.0, -7213.0);
	glCallList(503);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(31572.0, 9722.0, 8302.0);
	glRotatef(-17.35, 1.0f, 0.0f, 0.0f);
	glTranslatef(-31572.0, -9722.0, -8302.0);
	glCallList(504);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(31572.0, 9939.0, 9332.4);
	glRotatef(-19.83, 1.0f, 0.0f, 0.0f);
	glTranslatef(-31572.0, -9942.0, -9332.4);
	glCallList(505);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_STEPS_EDGE));
	glCallList(506);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_STEPS_EDGE_2));
	glCallList(507);
}
