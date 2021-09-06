//Aurthor: Peter Neve
//Version: 1
//Date: 29/08/2021
//Purpose: handle all object geometry drawing, populate callList()


#include "DrawHandler.h"

GLUquadricObj* glu_cylinder;

GLdouble stairsWidth = 0.80; GLdouble Xx = 36310.0; GLdouble Xe = 37391.0; // temporary variables i added to test the size of the stairs, increasing it increases stair width

//--------------------------------------------------------------------------------------
//  Create display lists
//	Numbers indicate list numbers
//--------------------------------------------------------------------------------------
void CreateTextureList()
{
	DrawGrass();				// 79, 111, 198, 460-477
	DrawChancPosts();			// 11-15, 235-237
	DrawDoorPosts();			// 25-27, 199
	DrawAboveWindowBlock();	// 20-24, 39, 43-46, 49-50, 53-56, 64-72, 95-96 208-213, 223-234, 238-239, 415, 424-425
	DrawPurplePosts();			// 29-32
	DrawRedPosts();			// 33-35
	DrawPhysSciPosts();		// 16-17, 36-38, 40-42
	DrawDoorPaving();			// 47-48
	DrawLibraryPosts();		// 57-63, 442-447
	DrawMainPosts();			// 18-19, 51-52
	DrawPavement();			// 28, 73-94, 240-249, 428, 436
	DrawBricks();				// 101-110, 112-169, 180-197, 200-201, 390-399, 430-434
	DrawRoof();					// 1-10, 97-100, 170-179, 202-205, 214-222, 250-257, 296-299, 426-427
	DrawEntranceSteps();		// 258-295, 206-207
	DrawExtras();				// 300-349, 388, 395, 419-421, 429, 435
	DrawLargerTextures();		// 350-375, 379-387, 389, 414-418, 422-423, 450-453
	DrawLights();				// 376-378
	DrawBench();				// 400-413
	DrawStepBricks();			// 478-507
	DrawCylinders();			// 437-441
	DrawMapExit();				// 448-449, 454
	DrawRoom();					// 666 - 677 and 782 -792
	DrawRoomStairs();			// 678 - 714
	DrawHallway();				// 777 - 781 
	// 455-459
	DrawHallwayStairs();
}

//--------------------------------------------------------------------------------------
// Set up co-ordinates of different plains
//--------------------------------------------------------------------------------------
void CreatePlains()
{
	// grass slope
	cam.SetPlains(ZY_PLAIN, 4848.0, 31568.0, 9536.0, 10450.0, 6200.0, 10000.0);

	// flat land (pavement and grass)
	cam.SetPlains(FLAT_PLAIN, 0.0, 36000.0, 10450.0, 10450.0, 10000.0, 17000.0);
	cam.SetPlains(FLAT_PLAIN, 0.0, 6500.0, 10450.0, 10450.0, 17000.0, 40000.0);
	cam.SetPlains(FLAT_PLAIN, 27000.0, 36000.0, 10450.0, 10450.0, 17000.0, 40000.0);
	cam.SetPlains(FLAT_PLAIN, 0.0, 36000.0, 10450.0, 10450.0, 40000.0, 50000.0);

	// top of lower hill
	cam.SetPlains(FLAT_PLAIN, 9000.0, 22000.0, 10650.0, 10650.0, 19000.0, 23000.0);
	cam.SetPlains(FLAT_PLAIN, 9000.0, 10000.0, 10650.0, 10650.0, 28000.0, 33000.0);
	cam.SetPlains(FLAT_PLAIN, 9000.0, 22000.0, 10650.0, 10650.0, 36000.0, 37000.0);
	// sides of lower hill
	cam.SetPlains(ZY_PLAIN, 6500.0, 27000.0, 10450.0, 10650.0, 17000.0, 19000.0);
	cam.SetPlains(ZY_PLAIN, 6500.0, 27000.0, 10650.0, 10450.0, 37000.0, 40000.0);
	cam.SetPlains(XY_PLAIN, 6500.0, 9000.0, 10450.0, 10650.0, 17000.0, 40000.0);
	cam.SetPlains(XY_PLAIN, 22000.0, 27000.0, 10650.0, 10450.0, 17000.0, 40000.0);

	// top of higher hill
	cam.SetPlains(FLAT_PLAIN, 14000.0, 18000.0, 10875.0, 108075.0, 28000.0, 33000.0);
	// sides of higher hill
	cam.SetPlains(ZY_PLAIN, 10000.0, 22000.0, 10650.0, 10875.0, 23000.0, 28000.0);
	cam.SetPlains(ZY_PLAIN, 10000.0, 22000.0, 10875.0, 10650.0, 33000.0, 36000.0);
	cam.SetPlains(XY_PLAIN, 10000.0, 14000.0, 10650.0, 10875.0, 23000.0, 36000.0);
	cam.SetPlains(XY_PLAIN, 18000.0, 22000.0, 10875.0, 10650.0, 23000.0, 36000.0);

	//entance steps
	step = 10450.0;
	stepLength = 9808.0;
	for (int i = 0; i < 18; i++)
	{
		cam.SetPlains(FLAT_PLAIN, 31582.0, 33835, step, step, stepLength, stepLength + 42.0);
		step -= 48.0;
		stepLength -= 142.0;
		if ((i + 3) % 5 == 0)
		{
			stepLength -= 500.0;
			step -= 48.0;
		}
	}

	// temp plain to take down to ECL1
	cam.SetPlains(ZY_PLAIN, 3200.0, 4800.0, 10450.0, 9370.0, 53400.0, 57900.0);

	// new room stairs ( actually model for the new stairs is in displayroom 
	cam.SetPlains(ZY_PLAIN, 36310.0, 37391.0, 10450.0, 11000.0, 38997.0, 40503.0);

	//hallway stairs
	cam.SetPlains(XY_PLAIN, 43200.0, 63500.0, 10450.0, 3200, 37350.0, 47350.0);
}


void DrawChancPosts()
{
	// Front of Window Post Chanc
	tp.CreateDisplayList(YZ, 11, 1024.0, 128.0, 33848.0, 10237.0, 9505.0, 0.586, 0.7344);
	// Right side of Window Post Chanc
	tp.CreateDisplayList(XY, 12, 64.0, 1024.0, 33848.0, 10237.0, 9599, 0.7344, 0.585);
	// Left side of Window Post Chanc
	tp.CreateDisplayList(XY, 13, 64.0, 1024.0, 33848.0, 10237.0, 9505.0, 0.7344, 0.585);

	// Window ledges of Chanc
	tp.CreateDisplayList(YZ, 14, 32.0, 1024.0, 33808.0, 10192.0, 9552.0, 1.0, 0.9375); // front ledge
	glNewList(15, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(33808.0, 10224.0, 9552.0);
	glTexCoord2f(0.0, 0.9375);
	glVertex3f(33808.0, 10224.0, 9552.0 + (1024.0 * 0.9375));
	glTexCoord2f(1.0, 0.9375);
	glVertex3f(33928.0, 10268.0, 9552.0 + (1024.0 * 0.9375));
	glTexCoord2f(1.0, 0.0);
	glVertex3f(33928.0, 10268.0, 9552.0);
	glEnd();
	glEndList();
	tp.CreateDisplayList(YZ, 235, 32.0, 64.0, 33808.0, 10192.0, 22032.0, 1.0, 1.0); // front ledge
	tp.CreateDisplayList(XY, 236, 64.0, 64.0, 33808.0, 10192.0, 22096.0, 1.35, 0.5); // front ledge

	// Window Edges
	glNewList(237, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(33808.0, 10225.0, 20112.0);
	glTexCoord2f(0.0, 0.5);
	glVertex3f(33808.0, 10192.0, 20112.0);
	glTexCoord2f(0.5, 0.5);
	glVertex3f(33872.0, 10192.0, 20112.0);
	glTexCoord2f(0.5, 0.0);
	glVertex3f(33872.0, 10247.0, 20112.0);
	glEnd();
	glEndList();


}

void DrawDoorPosts()
{
	// DOORPOSTS_CHANC
	tp.CreateDisplayList(YZ_FLIP, 25, 1024.0, 128.0, 33848.0, 10000.0, 10465.0, 0.83, 0.7344);	// post
	tp.CreateDisplayList(YZ, 26, 1024.0, 128.0, 33848.0, 10000.0, 11425.0, 0.83, 0.7344);
	tp.CreateDisplayList(XY, 27, 64.0, 1024.0, 33848.0, 10000.0, 10559.0, 1.0, 1.0);	// sidepost
	tp.CreateDisplayList(YZ_FLIP, 199, 1024.0, 128.0, 33848.0, 10000.0, 10465.0, 0.83, 0.7344);	// post
}

void DrawAboveWindowBlock()
{
	tp.CreateDisplayList(YZ, 20, 128.0, 256.0, 33808.0, 10832.0, 9552.0, 1.0, 4.0);		// chanc above bottom window
	tp.CreateDisplayList(YZ, 223, 128.0, 256.0, 33808.0, 10832.0, 11600.0, 1.0, 30.0);		// chanc above bottom window
	tp.CreateDisplayList(YZ, 229, 128.0, 256.0, 33808.0, 10832.0, 20304.0, 1.0, 3.0);		// chanc above bottom window
	tp.CreateDisplayList(YZ, 230, 128.0, 1024.0, 33808.0, 10832.0, 19280.0, 1.0, 1.0);		// chanc above bottom window
	tp.CreateDisplayList(YZ, 224, 128.0, 1024.0, 33808.0, 10832.0, 10576.0, 1.0, 1.0);		// chanc above bottom window
	tp.CreateDisplayList(YZ, 225, 128.0, 1024.0, 33808.0, 10832.0, 21072.0, 1.0, 1.0);		// chanc above bottom window
	tp.CreateDisplayList(XY, 424, 128.0, 128.0, 33808.0, 10832.0, 22096.0, 0.68, 1.0);		// chanc end edge downstairs
	tp.CreateDisplayList(XY, 425, 128.0, 256.0, 33808.0, 11856.0, 22096.0, 0.68, 0.5625);	// 3 bricks high to edge


	tp.CreateDisplayList(YZ, 21, 256.0, 256.0, 33808.0, 11856.0, 9552.0, 0.56, 49.0);		// chanc above top window chanc
	tp.CreateDisplayList(XZ, 22, 128.0, 256.0, 33808.0, 10832.0, 9552.0, 0.70, 49.0);		// chanc above under bottom window chanc

	tp.CreateDisplayList(YZ, 23, 256.0, 256.0, 33808.0, 10832.0, 25344.0, 0.75, 5.0);		// phys sci above bottom window
	tp.CreateDisplayList(YZ, 231, 256.0, 256.0, 33808.0, 11856.0, 25344.0, 0.75, 61.652);	// phys sci above bottom window

	tp.CreateDisplayList(YZ, 226, 256.0, 1024.0, 33808.0, 10832.0, 26624.0, 0.75, 1.0);	// phys sci text
	tp.CreateDisplayList(YZ, 227, 256.0, 256.0, 33808.0, 10832.0, 27648.0, 0.75, 34.0);	// phys sci above bottom window
	tp.CreateDisplayList(YZ, 228, 256.0, 256.0, 33808.0, 10832.0, 37376.0, 0.75, 14.652);	// phys sci above bottom window
	tp.CreateDisplayList(XZ, 24, 128.0, 256.0, 33808.0, 10832.0, 25344.0, 0.78, 61.652);	// phys sci above under bottom window

	tp.CreateDisplayList(YZ, 95, 256.0, 256.0, 33835.0, 11856.0, 41127.0, 1.0, 7.6);		// phys sci above top window
	tp.CreateDisplayList(XZ, 96, 128.0, 256.0, 33835.0, 11856.0, 41127.0, 0.78, 7.6);		// phys sci above under bottom

	tp.CreateDisplayList(YZ, 43, 256.0, 256.0, 34256.0, 10832.0, 26752.0, 0.75, 3.25);		// phys sci above 1st door
	tp.CreateDisplayList(XZ, 44, 128.0, 256.0, 34256.0, 10832.0, 26752.0, 0.70, 2.25);		// phys sci above under 1st door
	tp.CreateDisplayList(YZ, 45, 256.0, 256.0, 34256.0, 10832.0, 36319.0, 0.75, 6.125);	// phys sci above 2nd door
	tp.CreateDisplayList(XZ, 46, 128.0, 256.0, 34256.0, 10832.0, 36319.0, 0.70, 6.125);	// phys sci above under 2nd door

	tp.CreateDisplayList(YZ, 53, 256.0, 256.0, 31740.0, 11142.0, 8100.0, 0.75, 128.955);	// above posts chanc and canteen sides
	tp.CreateDisplayList(XZ, 54, 128.0, 256.0, 31740.0, 11142.0, 8100.0, 1.0, 128.955);	// above under main posts
	tp.CreateDisplayList(XZ, 67, 128.0, 256.0, 35920.0, 10832.0, 41127.0, 1.0, 7.6);		// above under steps at end of phys sci
	tp.CreateDisplayList(YZ, 68, 256.0, 256.0, 35920.0, 10832.0, 41127.0, 0.75, 7.6);		// above steps at end of phys sci
	tp.CreateDisplayList(YZ, 39, 128.0, 256.0, 35990.0, 11002.0, 41127.0, 0.75, 7.6);		// above steps at end of phys sci (darker back bit)
	tp.CreateDisplayList(XZ, 69, 256.0, 128.0, 4580.0, 11142.0, 40985.0, 106.094, 1.0);	// ABOVE_UNDER_POSTS_2 main posts by library
	tp.CreateDisplayList(YZ, 71, 256.0, 256.0, 35748.0, 11142.0, 22096.0, 0.75, 12.69);	// above post between chanc and phys sci
	tp.CreateDisplayList(XZ, 72, 128.0, 256.0, 35748.0, 11142.0, 22096.0, 1.0, 12.69);		// above under post between chanc and phys sci

	glNewList(232, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(31768.0 + 45, 11162, 41011.2 - 45);
	glTexCoord2f(10.54, 0.0);
	glVertex3f(33848 + 45, 11920, 43095.2 - 45);
	glTexCoord2f(10.54, 1.0);
	glVertex3f(33848.0 - 45, 11920, 43095.2 + 45);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(31768.0 - 45, 11162, 41011.2 + 45);
	glEnd();
	glEndList();

	glNewList(233, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(31768.0 - 45, 11162, 41011.2 + 45);
	glTexCoord2f(10.54, 0.0);
	glVertex3f(33848 - 45, 11920, 43095.2 + 45);
	glTexCoord2f(10.54, 0.75);
	glVertex3f(33848.0 - 45, 11920 + 192, 43095.2 + 45);
	glTexCoord2f(0.0, 0.75);
	glVertex3f(31768.0 - 45, 11162 + 192, 41011.2 + 45);
	glEnd();
	glEndList();


	glNewList(234, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(31768.0 + 45, 11162, 41011.2 - 45);
	glTexCoord2f(10.54, 0.0);
	glVertex3f(33848 + 45, 11920, 43095.2 - 45);
	glTexCoord2f(10.54, 0.75);
	glVertex3f(33848.0 + 45, 11920 + 192, 43095.2 - 45);
	glTexCoord2f(0.0, 0.75);
	glVertex3f(31768.0 + 45, 11162 + 192, 41011.2 - 45);
	glEnd();
	glEndList();

	// ABOVE_WINDOW_EDGE_3B
	tp.CreateDisplayList(XY, 49, 128.0, 256.0, 33808.0, 10832.0, 25344.0, 1.0, 0.75);		// 3 bricks high

	// ABOVE_WINDOW_BLOCK_XY_3
	tp.CreateDisplayList(XY, 50, 256.0, 256.0, 33888.0, 10832.0, 26752.0, 1.5, 1.0);
	tp.CreateDisplayList(XY, 64, 256.0, 256.0, 33808.0, 10832.0, 41127.0, 8.5, 0.75);		// above end phys sci
	tp.CreateDisplayList(XY, 65, 256.0, 256.0, 6600.0, 11856.0, 43056.0, 68.5, 0.75);		// top of library
	tp.CreateDisplayList(XY, 208, 256.0, 256.0, 24264.0, 11856.0, 43056.0, 38.5, 0.75);	// top of library
	tp.CreateDisplayList(XY, 66, 256.0, 256.0, 4548.0, 11142.0, 40985.0, 106.72, 0.75);	// above library main posts

	// ABOVE_LIB
	tp.CreateDisplayList(XY, 239, 1024.0, 256.0, 31504.96, 10768.0, 43056.0, 1.0, 1.0);	// (above KBLT)
	tp.CreateDisplayList(XY, 238, 256.0, 256.0, 32528.96, 10768.0, 43056.0, 13.75, 1.0);	// (above KBLT)
	tp.CreateDisplayList(XY, 55, 256.0, 256.0, 24264.0, 10768.0, 43056.0, 28.285, 1.0);	// (above KBLT)
	tp.CreateDisplayList(XY, 416, 1024.0, 256.0, 9416.0, 10768.0, 43056.0, 1.0, 1.0);		// (above library text)
	tp.CreateDisplayList(XY, 415, 256.0, 256.0, 10440.0, 10768.0, 43056.0, 49.0, 1.0);		// (above library)
	tp.CreateDisplayList(XY, 417, 256.0, 256.0, 23240.0, 10768.0, 43056.0, 3.5, 1.0);		// (above library)
	tp.CreateDisplayList(XY, 418, 256.0, 256.0, 22984.0, 10768.0, 43056.0, 1.0, 1.0);		// (above library ticket text)
	tp.CreateDisplayList(XY, 56, 256.0, 256.0, 6600.0, 10768.0, 43056.0, 11.0, 1.0);		// (above library)
	tp.CreateDisplayList(XZ, 70, 256.0, 128.0, 8189.0, 11856.0, 43056.0, 62.3, 0.75);		// above under upstairs
	tp.CreateDisplayList(YZ, 209, 256.0, 64.0, 6600.0, 11856.0, 43056.0, 1.2, 1.0);
	tp.CreateDisplayList(YZ, 210, 256.0, 64.0, 6600.0, 10768.0, 43056.0, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 211, 256.0, 128.0, 8189.0, 10768.0, 43056.0, 62.3, 0.75);		// above under downstairs
	tp.CreateDisplayList(XZ, 212, 256.0, 128.0, 32720.0, 10768.0, 43056.0, 3.5, 0.75);		// above under gcl1

	// ABOVE CANTEEN
	tp.CreateDisplayList(YZ, 213, 256.0, 256.0, 2608.0, 10896.0, 10000.0, 0.78, 139.25);

}

void DrawPurplePosts()
{
	tp.CreateDisplayList(YZ, 29, 64.0, 128.0, 33802.0, 10000.0, 31407.0, 13.0, 0.875);	// front
	tp.CreateDisplayList(YZ, 30, 64.0, 128.0, 33802.0, 10000.0, 32384.0, 13.0, 0.61);	// front
	tp.CreateDisplayList(XY, 31, 128.0, 64.0, 33802.0, 10000.0, 31519.0, 0.75, 13.0);	// side
	tp.CreateDisplayList(XY, 32, 128.0, 64.0, 33802.0, 10000.0, 36319.0, 0.58, 13.0);	// side
}

void DrawRedPosts()
{
	tp.CreateDisplayList(YZ, 33, 64.0, 128.0, 33802.0, 10000.0, 39200.0, 13.0, 0.125);	// front
	tp.CreateDisplayList(YZ, 34, 64.0, 128.0, 33802.0, 10000.0, 40055.0, 13.0, 0.75);	// front
	tp.CreateDisplayList(XY, 35, 64.0, 64.0, 33802.0, 10000.0, 38960.0, 1.0, 13.0);	// side
}

void DrawMainPosts()
{
	tp.CreateDisplayList(XY, 18, 128.0, 256.0, 31740.0, 9995.0, 10105.0, 1.0, 4.48);
	tp.CreateDisplayList(YZ, 19, 256.0, 128.0, 31740.0, 9995.0, 10105.0, 4.48, 1.0);
	tp.CreateDisplayList(XY, 51, 128.0, 256.0, 31740.0, 9555.0, 8100.0, 1.0, 6.2);		// 1st by steps
	tp.CreateDisplayList(YZ, 52, 256.0, 128.0, 31740.0, 9555.0, 8100.0, 6.2, 1.0);		// 1st by steps
}

void DrawPhysSciPosts()
{
	// WINDOWPOST_PS
	tp.CreateDisplayList(YZ, 36, 512.0, 128.0, 33848.0, 11347.0, 26625.0, 1.0, 0.6016);
	tp.CreateDisplayList(XY, 37, 64.0, 512.0, 33848.0, 11347.0, 26625.0, 1.0, 1.0);
	tp.CreateDisplayList(XY, 38, 64.0, 512.0, 33848.0, 11347.0, 26625.0, 1.0, 1.0);


	// WINDOWLEDGE_PS_FRONT & TOP (shorter phys sci ds)
	// first shop
	glNewList(40, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(33808.0, 10544.0, 33421.0);
	glTexCoord2f(0.0, 0.9375);
	glVertex3f(33808.0, 10544.0, 33421.0 + (1024.0 * 0.9375));
	glTexCoord2f(1.0, 0.9375);
	glVertex3f(33928.0, 10588.0, 33421.0 + (1024.0 * 0.9375));
	glTexCoord2f(1.0, 0.0);
	glVertex3f(33928.0, 10588.0, 33421.0);
	glEnd();
	glEndList();

	// small window
	glNewList(41, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(33808.0, 10288.0, 38239.0);
	glTexCoord2f(0.0, 0.315);
	glVertex3f(33808.0, 10288.0, 38239.0 + (1024.0 * 0.315));
	glTexCoord2f(1.0, 0.315);
	glVertex3f(33928.0, 10332.0, 38239.0 + (1024.0 * 0.315));
	glTexCoord2f(1.0, 0.0);
	glVertex3f(33928.0, 10332.0, 38239.0);
	glEnd();
	glEndList();
	tp.CreateDisplayList(YZ, 42, 32.0, 1024.0, 33808.0, 10256.0, 38239.0, 1.0, 0.315);

	// WINDOWLEDGE_PS_FRONT & TOP
	tp.CreateDisplayList(YZ, 16, 32.0, 1024.0, 33808.0, 11344.0, 26663.0, 1.0, 0.9375);
	glNewList(17, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(33808.0, 11376.0, 26663.0);
	glTexCoord2f(0.0, 0.9375);
	glVertex3f(33808.0, 11376.0, 26663.0 + (1024.0 * 0.9375));
	glTexCoord2f(1.0, 0.9375);
	glVertex3f(33928.0, 11420.0, 26663.0 + (1024.0 * 0.9375));
	glTexCoord2f(1.0, 0.0);
	glVertex3f(33928.0, 11420.0, 26663.0);
	glEnd();
	glEndList();
}

void DrawDoorPaving()
{
	tp.CreateDisplayList(XZ, 47, 128.0, 256.0, 33808.0, 10000.0, 31508.0, 0.75, 7.5);	// phy sci 1st doorway
	tp.CreateDisplayList(XZ, 48, 128.0, 256.0, 33808.0, 10000.0, 35324.0, 0.75, 3.5);	// phy sci 2nd doorway
}

void DrawLibraryPosts()
{
	// WINDOWPOST_LIB_FRONT
	tp.CreateDisplayList(XY, 57, 128.0, 512.0, 24035.0, 10304.0, 43096.0, 0.6016, 1.0);
	tp.CreateDisplayList(YZ, 58, 512.0, 64.0, 24035.0, 10304.0, 43096.0, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 59, 512.0, 64.0, 24035.0, 10304.0, 43096.0, 1.0, 1.0);

	// WINDOWLEDGE_LIB
	tp.CreateDisplayList(XY, 61, 1024.0, 32.0, 21896.0, 10320.0, 43056.0, 0.5313, 1.0);
	tp.CreateDisplayList(XY, 60, 1024.0, 32.0, 22440.0, 10320.0, 43056.0, 0.5313, 1.0);
	glNewList(62, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(21896.0, 10352.0, 43056.0);
	glTexCoord2f(0.5313, 0.0);
	glVertex3f(21896.0 + (1024.0 * 0.5313), 10352.0, 43056.0);
	glTexCoord2f(0.5313, 1.0);
	glVertex3f(21896.0 + (1024.0 * 0.5313), 10396.0, 43176.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(21896.0, 10396.0, 43176.0);
	glEnd();
	glEndList();
	glNewList(63, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(22440.0, 10352.0, 43056.0);
	glTexCoord2f(0.5313, 0.0);
	glVertex3f(22440.0 + (1024.0 * 0.5313), 10352.0, 43056.0);
	glTexCoord2f(0.5313, 1.0);
	glVertex3f(22440.0 + (1024.0 * 0.5313), 10396.0, 43176.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(22440.0, 10396.0, 43176.0);
	glEnd();
	glEndList();

	// Ticket Counter
	tp.CreateDisplayList(XZ, 442, 128.0, 256.0, 22984.0, 10305.0, 42992.0, 9.0, 0.625);
	tp.CreateDisplayList(YZ, 443, 64.0, 64.0, 22984.0, 10256.0, 43056.0, 0.766, 1.0);
	tp.CreateDisplayList(XY, 444, 128.0, 256.0, 22984.0, 10256.0, 43056.0, 9.0, 0.1914);

	tp.CreateDisplayList(XY, 445, 128.0, 32.0, 22984.0, 10286.0, 42992.0, 9.0, 0.59);

	tp.CreateAngledPolygon(446, 128.0, 256.0, 22984.0, 24136.0, 24136.0, 22984.0,
		10286.0, 10286.0, 10276.0, 10276.0,
		42992.0, 42992.0, 43088.0, 43088.0, 5, 1);

	tp.CreateAngledPolygon(447, 64.0, 64.0, 22984.0, 22984.0, 22984.0, 22984.0,
		10286.0, 10276.0, 10305.0, 10305.0,
		42992.0, 43056.0, 43056.0, 42992.0, 6, 1);
}

void DrawPavement()
{
	// PAVEMENT
	tp.CreateDisplayList(XZ, 87, 128.0, 64.0, 2608.0, 10000.0, 10000.0, 17.0, 482.5);
	tp.CreateDisplayList(XZ, 73, 128.0, 64.0, 31632.0, 10000.0, 10000.0, 17.0, 482.5);
	tp.CreateDisplayList(XZ, 88, 128.0, 64.0, 33744.0, 10000.0, 41104.0, 4.75, 30.5);	// by steps between phys sci and library
	tp.CreateDisplayList(XZ, 428, 128.0, 64.0, 34256.0, 10000.0, 26704.0, 1.0, 9.5); // phys sci doorway (behind carpet)
	//

	// PAVEMENT_TOP
	tp.CreateDisplayList(XZ, 74, 64.0, 128.0, 4912.0, 10000.0, 40880.0, 416.5, 17.0);
	tp.CreateDisplayList(XZ, 246, 64.0, 128.0, 32656.0, 10000.0, 42928.0, 15.0, 2.0); // gcl1 door way
	tp.CreateDisplayList(XZ, 245, 64.0, 128.0, 24080.0, 10000.0, 42928.0, 3.0, 1.5); // gcl1 door way
	tp.CreateDisplayList(XZ, 244, 64.0, 128.0, 8189.0, 10000.0, 42928.0, 44.8, 1.80); // library door way
	tp.CreateDisplayList(XZ, 243, 64.0, 128.0, 2576.0, 10000.0, 42928.0, 36.0, 21.0);	// entrance to IT block
	tp.CreateDisplayList(XZ, 242, 64.0, 128.0, 4848.0, 10000.0, 42928.0, 27.5, 21.0);	// entrance to IT block
	tp.CreateDisplayList(XZ, 241, 128.0, 64.0, 2096.0, 10000.0, 41168.0, 4.5, 29.0);	// entance to psch block
	tp.CreateDisplayList(XZ, 240, 128.0, 64.0, 31568.0, 10000.0, 40816.0, 1.0, 1.0);	// corner space filler

	// PAVEMENT_JOINS
	glNewList(89, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(31568.0, 10000.0, 40816.0);
	glTexCoord2f(17.5, 0.0);
	glVertex3f(33808.0, 10000.0, 40816.0);
	glTexCoord2f(17.5, 35.0);
	glVertex3f(33808.0, 10000.0, 43056.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(31568.0, 10000.0, 40816.0);
	glEnd();
	glEndList();
	glNewList(91, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(31504.0, 10000.0, 40880.0);
	glTexCoord2f(34.0, 17.0);
	glVertex3f(33680.0, 10000.0, 43056.0);
	glTexCoord2f(34.0, 17.0);
	glVertex3f(33680.0, 10000.0, 43056.0);
	glTexCoord2f(0.0, 17.0);
	glVertex3f(31504.0, 10000.0, 43056.0);
	glEnd();
	glEndList();
	glNewList(93, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(31504.0, 10000.0, 40880.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(31632.0, 10000.0, 40880.0);
	glTexCoord2f(18.0, 17.0);
	glVertex3f(33808.0, 10000.0, 43056.0);
	glTexCoord2f(17.0, 17.0);
	glVertex3f(33680.0, 10000.0, 43056.0);
	glEnd();
	glEndList();

	glNewList(90, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(2608.0, 10000.0, 40816.0);
	glTexCoord2f(17.5, 0.0);
	glVertex3f(4848.0, 10000.0, 40816.0);
	glTexCoord2f(17.5, 0.0);
	glVertex3f(4848.0, 10000.0, 40816.0);
	glTexCoord2f(0.0, 35.0);
	glVertex3f(2608.0, 10000.0, 43056.0);
	glEnd();
	glEndList();

	glNewList(92, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(4912.0, 10000.0, 40880.0);
	glTexCoord2f(34.0, 17.0);
	glVertex3f(2736.0, 10000.0, 43056.0);
	glTexCoord2f(34.0, 17.0);
	glVertex3f(2736.0, 10000.0, 43056.0);
	glTexCoord2f(0.0, 17.0);
	glVertex3f(4912.0, 10000.0, 43056.0);
	glEnd();
	glEndList();

	glNewList(94, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(17.0, 0.0);
	glVertex3f(4784.0, 10000.0, 40880.0);
	glTexCoord2f(18.0, 0.0);
	glVertex3f(4912.0, 10000.0, 40880.0);
	glTexCoord2f(1.0, 17.0);
	glVertex3f(2736.0, 10000.0, 43056.0);
	glTexCoord2f(0.0, 17.0);
	glVertex3f(2608.0, 10000.0, 43056.0);
	glEnd();
	glEndList();

	// PAVEMENTSIDE_LEFT
	tp.CreateDisplayList(XZ, 75, 64.0, 64.0, 31568.0, 10000.0, 10096.0, 1.0, 480.0);
	tp.CreateDisplayList(XZ, 436, 64.0, 64.0, 31568.0, 9086.0, 3408.0, 1.0, 45.0);	// Side paving at entrance
	// PAVEMENTSIDE_RIGHT
	tp.CreateDisplayList(XZ, 76, 64.0, 64.0, 4784.0, 10000.0, 10000.0, 1.0, 481.5);
	// PAVEMENTSIDE_TOP
	tp.CreateDisplayList(XZ, 77, 64.0, 64.0, 4848.0, 10000.0, 40816.0, 417.5, 1.0);
	// PAVEMENT_STEPS_CORNER
	tp.CreateDisplayList(XZ, 78, 128.0, 64.0, 31568.0, 10000.0, 10000.0, 1.0, 1.5);   // corner above chanc steps
	tp.CreateDisplayList(XZ, 80, 32.0, 64.0, 31568.0, 10000.0, 9950.0, 70.0, 0.797);  // strip along top of chanc steps
	tp.CreateDisplayList(XZ, 28, 128.0, 64.0, 33744.0, 10000.0, 22096.0, 17.2, 52.0); // between chanc and phy sci
	tp.CreateDisplayList(XZ, 248, 128.0, 64.0, 33744.0, 10000.0, 10449.0, 1.5, 16.0); // doorway to chanc
	tp.CreateDisplayList(XZ, 247, 128.0, 64.0, 33744.0, 10000.0, 39185.0, 1.5, 23.0); // doorway to red posts
	tp.CreateDisplayList(XZ, 249, 128.0, 64.0, 31632.0, 9086.0, 3408.0, 18.0, 45.0);	//entry (bottom of steps)
	tp.CreateDisplayList(XZ, 81, 128.0, 64.0, 33744.0, 10000.0, 26704.0, 2.5, 11.0);	//phys sci doorway 1
	tp.CreateDisplayList(XZ, 82, 128.0, 64.0, 33744.0, 10000.0, 27344.0, 4.5, 3.5);	//phys sci doorway 1
	tp.CreateDisplayList(XZ, 83, 128.0, 64.0, 33744.0, 10000.0, 36304.0, 5.0, 5.3);	//phys sci doorway 2
	tp.CreateDisplayList(XZ, 84, 128.0, 64.0, 33744.0, 10000.0, 36624.0, 2.5, 9.0);	//phys sci doorway 2
	tp.CreateDisplayList(XZ, 85, 128.0, 64.0, 33744.0, 10000.0, 37200.0, 5.0, 10.5);	//phys sci doorway 2
	tp.CreateDisplayList(XZ, 86, 128.0, 64.0, 33744.0, 10000.0, 28624.0, 2.5, 13.5);	//phys sci toilet doorways
}

//Made by Raymond Lua
void DrawHallway() {
	//XY
	tp.CreateDisplayList(XY, 777, 10000, 1000.0, 37550.0, 4000.0, 39000.0, 3.0, 7.0);
	tp.CreateDisplayList(XY, 778, 10000, 1000.0, 37550.0, 4000.0, 37500.0, 3.0, 7.0);

	//YZ
	tp.CreateDisplayList(YZ, 779, 2500, 215.0, 67550.0, 4000.0, 37500.0, 3.0, 7.0);

	//XZ
	tp.CreateDisplayList(XZ, 780, 500, 1505 , 37610.0, 9936.0, 37500.0, 12.0, 1.0); // 3.0, 7.0 // 10000 215
	tp.CreateDisplayList(XZ, 781, 10000 /4, 215.0 * 3.5, 37610.0, 10936.0, 37500.0, 12.0, 2.0); // 3.0 , 7.0

}

void DrawHallwayStairs() {
	GLdouble xCord = 43500.0; // x coord   //31582.0  is original cord  // new value ( value of the second x coord for its corresponding plain  - 400) 
	step = 9936.0; // effectively the y coordinate  // 10000.0 original // new value ( value of first y value + 225 ) 
	stepLength = 37350.0; // z coordinate   // 9808.0 original     // new value ( value of second z value + 700 )
	for (int i = 1000; i < 1320; i++)
	{
		tp.CreateDisplayList(XZ, i,512.0, 2050.0, xCord, step, stepLength,0.277, 1.0 * stairsWidth); // original xTimes was 2.2 // 1.0 // 0.277
		//tp.CreateDisplayList(XY, i + 16, 64.0, 64.0, xCord, step - 64.0, stepLength, 16.0 * stairsWidth, 1.0); // original xTimes was 35.0
		tp.CreateDisplayList(YZ, i + 320, 5.0, 1800.0, xCord + 142.0, step - 64.0, stepLength, 16.0 * stairsWidth, 1.0); // original xTimes was 35.0
		//tp.CreateDisplayList(XZ, i, 1024.0, 512.0, xCord, step, stepLength, 1.0 * stairsWidth, 0.277);

		step -= 48.0;
		//stepLength -= 142.0;
		xCord += 142.0;
	}
}

//Made by Raymond Lau
void DrawRoom() {
	//XY
    tp.CreateDisplayList(XY, 666, 300, 143.0, 35500.0, 9936.0, 35319.0, 3.0, 7.0);
	tp.CreateDisplayList(XY, 667, 50, 143.0, 37400.0, 9936.0, 35319.0, 3.0, 7.0);
	tp.CreateDisplayList(XY, 668, 300, 143.0, 35390.0, 9936.0, 39000.0, 3.0, 7.0);
	tp.CreateDisplayList(XY, 669, 50, 143.0, 37400.0, 9936.0, 39000.0, 3.0, 7.0);

	//ZY
	tp.CreateDisplayList(YZ, 670, 333, 145.0, 35500.0, 9936.0, 35319.0, 3.0, 7.0);
	tp.CreateDisplayList(YZ, 671, 333, 370.0, 37550.0, 9936.0, 35319.0, 3.0, 7.0);
	tp.CreateDisplayList(YZ, 672, 333, 200.0, 35390.0, 9936.0, 37850.0, 3.0, 7.0);
	tp.CreateDisplayList(YZ, 673, 333, 40.0, 37528.0, 9936.0, 38720.0, 3.0, 7.0);

	//XZ
	tp.CreateDisplayList(XZ, 674, 770, 700, 35300.0, 9936.0, 35319.0, 3.0, 9.0); //the main floor in new room  chaning zTimes to 9.0 from 7.0
	tp.CreateDisplayList(XZ, 675, 435, 500, 34000.0, 9936.0, 35319.0, 3.0, 7.0);

	tp.CreateDisplayList(XZ, 676, 770, 700 * 0.76, 35300.0, 10936.0, 35319.0, 3.0, 7.0); 
	tp.CreateDisplayList(XZ, 677, 435, 500, 34000.0, 10936.0, 35319.0, 3.0, 7.0);

	// Pin Boards in the entrance room (782 - 783)       ( 792) max // 209, 157
	tp.CreateDisplayList(XY, 782, 409, 257, 35728.0, 10250.0, 38995.0, 1.0, 1.0); // pinboard 1
	tp.CreateDisplayList(XY, 783, 409, 257, 35000.0, 10250.0, 36325.0, 1.0, 1.0); // pinboard 2
	// Exit door leftside of room
	tp.CreateDisplayList(XY, 784, 300 * 3.34, 143.0 * 7, 36400.0, 9936.0, 35319.0, 1.0, 1.0);
	// Image at the top of the stairs 
	tp.CreateDisplayList(XY, 785, 409 * 2, 257 * 4, 36428.0, 10550.0, 40975.0, 1.0, 1.0);
	// Right window next to the entrance door 
	tp.CreateDisplayList(YZ, 786, 333 * 3, 145.0 * 5, 34300.0, 9936.0, 37100.0, 1.0, 1.0);
	// Floor level sign next to the stairs
	tp.CreateDisplayList(YZ, 787, 333 , 145.0 , 37450.0, 10200.0, 39100.0, 1.0, 1.0);
	// Door1 in the hallway 
	tp.CreateDisplayList(XY, 788, 409 , 257 * 3 , 39300.0, 9936.0, 38990.0, 1.0, 1.0);
	// Door2 in the hallway 
	tp.CreateDisplayList(XY, 789, 409, 257 * 3, 41000.0, 9936.0, 37510.0, 1.0, 1.0);
}

void DrawRoomStairs() { // Made by Jason
	GLdouble xCord = 36730.0 - 400; // x coord   //31582.0  is original cord  // new value ( value of the second x coord for its corresponding plain  - 400) 
	step = 10450.0 + 225.0; // effectively the y coordinate  // 10000.0 original // new value ( value of first y value + 225 ) 
	stepLength = 40503.0 + 700.0; // z coordinate   // 9808.0 original     // new value ( value of second z value + 700 )
	for (int i = 678; i < 694; i++)
	{
		tp.CreateDisplayList(XZ, i, 1024.0, 512.0, xCord, step, stepLength, 1.0 * stairsWidth, 0.277); // original xTimes was 2.2 // 1.0 // 0.277
		tp.CreateDisplayList(XY, i + 16, 64.0, 64.0, xCord, step - 64.0, stepLength, 16.0 * stairsWidth, 1.0); // original xTimes was 35.0
		step -= 48.0;
		stepLength -= 142.0;
	}
	// creating the walls in the sub room that has stairs 
	tp.CreateDisplayList(YZ, 716, 666, 300.0, 37528.0, 9936.0, 39000.0, 3.0, 7.0);
	tp.CreateDisplayList(XY, 717, 600, 300.0, 37528.0, 9936.0, 39000.0, 3.0, 7.0);
}

void DrawBricks()
{
	// WALL_BRICK_YZ
	// --------  (Face of Cancerllary Building) --------
	tp.CreateDisplayList(YZ, 101, 128.0, 128.0, 33808.0, 9872.0, 9552.0, 2.5, 7.5);		// panel 1 (above steps)
	tp.CreateDisplayList(YZ, 222, 128.0, 128.0, 33840.0, 8976.0, 5840.0, 23.625, 5.0);		// panel 1 (before steps)
	tp.CreateDisplayList(YZ, 102, 128.0, 128.0, 33808.0, 8976.0, 6480.0, 23.625, 24.0);	// panel 2 (below steps)
	tp.CreateDisplayList(YZ, 103, 128.0, 128.0, 33808.0, 10000.0, 11472.0, 1.5, 60.0);		// panel 3 (below window 1)
	tp.CreateDisplayList(YZ, 104, 128.0, 128.0, 33808.0, 10000.0, 20112.0, 1.5, 15.5);		// panel 4 (below window 2)
	tp.CreateDisplayList(YZ_FLIP, 105, 128.0, 128.0, 33808.0, 10960.0, 9552.0, 2.0, 97.5);	// us panel 4
	tp.CreateDisplayList(YZ, 120, 128.0, 128.0, 33808.0, 10960.0, 22032.0, 2.0, 0.5);		// us panel 4 (last 1/2 brick)

	// -------- (Face of Physical Science/Shops Block) --------
	tp.CreateDisplayList(YZ, 106, 128.0, 128.0, 33808.0, 10000.0, 25344.0, 4.525, 11.0);	// panel 1 (around rusty man)
	tp.CreateDisplayList(YZ, 107, 128.0, 128.0, 33808.0, 11024.0, 25344.0, 6.5, 10.0);		// us panel 1
	tp.CreateDisplayList(YZ, 108, 128.0, 128.0, 33808.0, 11024.0, 26624.0, 2.5, 113.305);	// us panel 2
	tp.CreateDisplayList(YZ, 109, 128.0, 128.0, 33808.0, 10000.0, 27559.0, 3.5, 8.5);		// panel 3 (toilets window)
	tp.CreateDisplayList(YZ, 394, 128.0, 128.0, 33808.0, 10384.0, 27559.0, 1.0, 7.5);		// panel 3 (toilets window)
	tp.CreateDisplayList(YZ, 110, 128.0, 128.0, 33872.0, 9936.0, 28967.0, 6.5, 4.5);		// panel 4 (toilets door)
	tp.CreateDisplayList(YZ, 112, 128.0, 128.0, 33808.0, 10000.0, 33422.0, 2.0, 14.4);		// panel 5 (booth)
	tp.CreateDisplayList(YZ, 113, 128.0, 128.0, 33808.0, 10128.0, 33422.0, 3.0, 5.5);		// panel 5 (booth below window)
	tp.CreateDisplayList(YZ, 188, 128.0, 128.0, 33808.0, 10128.0, 34254.0, 3.0, 1.0);		// panel 5 (booth below window)
	tp.CreateDisplayList(YZ, 115, 128.0, 128.0, 34260.0, 10000.0, 36319.0, 2.5, 2.5);		// panel 6 (phys sci doorway)
	tp.CreateDisplayList(YZ, 191, 128.0, 128.0, 34260.0, 10256.0, 36319.0, 4.5, 1.5);		// panel 6 (phys sci doorway)
	tp.CreateDisplayList(YZ, 192, 128.0, 128.0, 34260.0, 10576.0, 36383.0, 2.0, 2.0);		// panel 6 (phys sci doorway)
	tp.CreateDisplayList(YZ, 114, 128.0, 128.0, 33808.0, 10000.0, 37855.0, 2.05, 10.51);	// panel 7 (with window)
	tp.CreateDisplayList(YZ, 116, 128.0, 128.0, 33808.0, 10128.0, 37855.0, 5.5, 1.05);		// panel 7 (with window)
	tp.CreateDisplayList(YZ, 396, 128.0, 128.0, 33808.0, 10128.0, 38111.0, 5.5, 1.0);		// panel 7 (with window)
	tp.CreateDisplayList(YZ, 397, 128.0, 128.0, 33808.0, 10512.0, 37855.0, 2.5, 3.0);		// panel 7 (with window)
	tp.CreateDisplayList(YZ, 398, 256.0, 128.0, 33808.0, 10256.0, 37983.0, 1.05, 1.1);		// panel 7 (with sign)
	tp.CreateDisplayList(YZ_FLIP, 117, 128.0, 128.0, 33808.0, 10128.0, 38560.0, 5.5, 0.5);	// panel 7 (with window)
	tp.CreateDisplayList(YZ, 118, 128.0, 128.0, 33808.0, 10128.0, 38624.0, 5.5, 4.5);		// panel 7 (with window)
	tp.CreateDisplayList(YZ, 119, 128.0, 128.0, 33808.0, 10000.0, 40615.0, 6.5, 4.0);		// panel 8 (end panel)
	tp.CreateDisplayList(YZ, 121, 128.0, 128.0, 34256.0, 9936.0, 27303.0, 3.0, 2.0);		// first doorway panel
	tp.CreateDisplayList(YZ, 193, 128.0, 128.0, 34256.0, 10576.0, 27303.0, 2.0, 2.0);		// first doorway panel
	tp.CreateDisplayList(YZ, 194, 128.0, 128.0, 34256.0, 10192.0, 27431.0, 3.5, 1.0);		// first doorway panel

	// -------- (Face of Canteen Block) --------
	tp.CreateDisplayList(YZ, 122, 128.0, 128.0, 2608.0, 10000.0, 10000.0, 7.0, 243.5);		// long downstairs panel
	tp.CreateDisplayList(YZ, 123, 128.0, 128.0, 2608.0, 10000.0, 42960.0, 7.0, 21.0);		// end downstairs panel
	tp.CreateDisplayList(YZ, 124, 128.0, 128.0, 2608.0, 11088.0, 10000.0, 7.0, 278.5);		// long upstairs panel
	tp.CreateDisplayList(XY, 136, 128.0, 128.0, 2096.0, 10000.0, 42960.0, 4.0, 7.0);		// corner exit to psc block from canteen

	// WALL_BRICK_USD_YZ
	tp.CreateDisplayList(YZ, 200, 128.0, 128.0, 33808.0, 10576.0, 25344.0, 2.0, 1.0);		// panel 1 (around rusty man)
	tp.CreateDisplayList(YZ, 201, 128.0, 128.0, 33808.0, 10576.0, 26496.0, 2.0, 2.0);		// panel 1 (around rusty man)

	// WALL_BRICK_XY
	// --------  (Cancerllary Building) --------
	tp.CreateDisplayList(XY, 399, 128.0, 128.0, 33840.0, 8976.0, 5840.0, 0.5, 23.625);	// first corner edge (bottom of steps)
	tp.CreateDisplayList(XY, 130, 128.0, 128.0, 33808.0, 10960.0, 22096.0, 0.68, 2.0);	// below us window (end wall)
	tp.CreateDisplayList(XY, 131, 128.0, 128.0, 33808.0, 10192.0, 9552.0, 0.68, 15.5);	// above steps
	tp.CreateDisplayList(XY, 132, 128.0, 128.0, 33808.0, 10000.0, 10512.0, 0.68, 1.5);	// first door (others)
	tp.CreateDisplayList(XY, 133, 128.0, 128.0, 33808.0, 11344.0, 26624.0, 0.68, 4.0);	// next us window phys sci
	tp.CreateDisplayList(XY, 143, 128.0, 128.0, 33895.0, 10000.0, 22096.0, 15.5, 16.0);	// end wall
	tp.CreateDisplayList(XY, 186, 128.0, 128.0, 33808.0, 10000.0, 22096.0, 0.68, 1.5);	// end wall
	// --------  (Phys Science Block) -------
	tp.CreateDisplayList(XY, 197, 128.0, 128.0, 33808.0, 10640.0, 25344.0, 1.5, 1.5);		// end wall above telephones
	tp.CreateDisplayList(XY, 196, 128.0, 128.0, 33936.0, 10640.0, 25344.0, 6.0, 1.505);	// end wall above telephones
	tp.CreateDisplayList(XY, 195, 128.0, 128.0, 34576.0, 10128.0, 25344.0, 1.0, 6.5);		// next to telephones
	tp.CreateDisplayList(XY, 190, 128.0, 128.0, 34704.0, 10000.0, 25344.0, 9.5, 5.75);	// end wall behind drinks machine
	tp.CreateDisplayList(XY, 189, 128.0, 128.0, 34704.0, 10736.0, 25344.0, 9.5, 0.75);	// end wall above drinks machine
	tp.CreateDisplayList(XY, 144, 128.0, 128.0, 33808.0, 10000.0, 25344.0, 7.0, 1.6);		// end wall
	tp.CreateDisplayList(XY, 145, 550, 143.0, 33876.0, 9936.0, 36319.0, 3.0, 7.0);		// ps 2nd door(leftside entrance)

	tp.CreateDisplayList(XY, 146, 375.0, 143.0, 33808.0, 9936.0, 37855.0, 4.25, 7.0);		// ps 2nd door(rightside entrance)
	tp.CreateDisplayList(XY, 147, 128.0, 128.0, 33808.0, 9936.0, 26752, 4.0, 7.0);		// ps first door (left bottom)
	tp.CreateDisplayList(XY, 148, 128.0, 128.0, 33808.0, 9936.0, 27559.0, 3.5, 4.5);		// ps first door (right bottom)
	tp.CreateDisplayList(XY, 149, 128.0, 128.0, 33872.0, 10384.0, 27559.0, 3.0, 3.5);		// ps first door (right top)
	tp.CreateDisplayList(XY, 185, 128.0, 128.0, 34256.0, 10000.0, 27303.0, 0.5, 6.5);		// ps first door (1/2 inner brick)
	tp.CreateDisplayList(XY, 166, 128.0, 128.0, 33808.0, 10000.0, 29479.0, 0.5, 4.0);		// side of toilet doors phys sci
	tp.CreateDisplayList(XY, 167, 128.0, 128.0, 33808.0, 10256.0, 38239.0, 0.75, 4.5);	// side of small window phys sci
	tp.CreateDisplayList(XY_FLIP, 152, 128.0, 128.0, 33936.0, 10832.0, 25344.0, 15.5, 2.5);	// end wall panel 2 phys sci
	tp.CreateDisplayList(XY, 153, 128.0, 128.0, 33808.0, 11024.0, 25344.0, 17.5, 6.5);	// end wall panel 3 phys sci
	tp.CreateDisplayList(XY, 165, 128.0, 128.0, 34260.0, 10000.0, 36639.0, 0.7, 6.5);		// ps 2nd door(inner 1/2 brick)
	tp.CreateDisplayList(XY, 187, 128.0, 128.0, 33808.0, 10256.0, 34382.0, 0.5, 2.0);		// side of toilet doors phys sci

	// --------  (Library Block) --------
	tp.CreateDisplayList(XY, 154, 128.0, 128.0, 33616.0, 10000.0, 43056.0, 19.0, 6.0);	// first panel
	tp.CreateDisplayList(XY, 155, 128.0, 128.0, 30800.0, 10000.0, 43056.0, 15.0, 6.0);	// 2nd panel
	tp.CreateDisplayList(XY, 156, 128.0, 128.0, 27976.0, 9936.0, 43056.0, 12.0, 3.0);		// 3rd panel (next to KBLT)
	tp.CreateDisplayList(XY, 217, 128.0, 128.0, 29512.0, 9936.0, 43056.0, 10.0, 2.75);	// 3rd panel (below nexus sign)
	tp.CreateDisplayList(XY, 157, 128.0, 128.0, 24264.0, 10256.0, 43056.0, 1.5, 4.0);		// 4th panel (next to KBLT)
	tp.CreateDisplayList(XY, 218, 128.0, 128.0, 24264.0, 10000.0, 43056.0, 11.5, 2.5);	// around glass boards
	tp.CreateDisplayList(XY, 219, 128.0, 128.0, 25352.0, 10192.0, 43056.0, 3.0, 4.5);		// around glass boards
	tp.CreateDisplayList(XY, 220, 128.0, 128.0, 27976.0, 10192.0, 43056.0, 3.0, 4.5);		// around glass boards
	tp.CreateDisplayList(XY, 221, 128.0, 128.0, 29256.0, 10192.0, 43056.0, 2.0, 4.5);		// around glass boards
	tp.CreateDisplayList(XY, 158, 128.0, 128.0, 30800.0, 11024.0, 43056.0, 41.0, 6.5);	// US 1st panel
	tp.CreateDisplayList(XY, 159, 128.0, 128.0, 24264.0, 11024.0, 43056.0, 51.0, 6.5);	// US 2nd panel
	tp.CreateDisplayList(XY, 160, 128.0, 128.0, 22984.0, 10000.0, 43056.0, 9.0, 2.0);		// US 3rd panel (start of ds library)
	tp.CreateDisplayList(XY, 161, 128.0, 128.0, 10952.0, 10000.0, 43056.0, 94.0, 2.5);	// US 4th panel (under of ds library)
	tp.CreateDisplayList(XY, 162, 128.0, 128.0, 6600.0, 11024.0, 43056.0, 137.0, 2.5);	// US 4th panel (under of ds library)
	tp.CreateXtoYWindowList(434, 43056.0, 6856.0, 256.0, 10256.0, 512.0, 1.0, 1.0);		// End of DS (Map)
	tp.CreateDisplayList(XY, 433, 128.0, 128.0, 7112.0, 10640.0, 43056.0, 8.0, 1.0);		// End DS
	tp.CreateDisplayList(XY, 432, 128.0, 128.0, 7112.0, 10128.0, 43056.0, 1.5, 5.0);		// End DS
	tp.CreateDisplayList(XY, 431, 128.0, 128.0, 8072.0, 10064.0, 43056.0, 0.914, 5.5);		// End DS
	tp.CreateDisplayList(XY, 430, 128.0, 128.0, 6600.0, 10128.0, 43056.0, 2.0, 5.0);		// End DS
	tp.CreateDisplayList(XY, 163, 128.0, 128.0, 6600.0, 10000.0, 43056.0, 12.414, 2.0);	// End DS
	tp.CreateDisplayList(XY, 164, 128.0, 128.0, 6600.0, 11024.0, 43056.0, 17.29, 6.5);		// End US
	tp.CreateDisplayList(YZ, 126, 128.0, 128.0, 6600.0, 10000.0, 43056.0, 6.0, 0.5);		// end panel corner
	tp.CreateDisplayList(YZ, 125, 128.0, 128.0, 6514.0, 10000.0, 43120.0, 14.5, 20.5);		// end panel
	tp.CreateDisplayList(YZ, 127, 128.0, 128.0, 6600.0, 11024.0, 43056.0, 6.5, 0.5);		// end panel top
	tp.CreateDisplayList(YZ, 128, 128.0, 128.0, 33616.0, 9936.0, 43056.0, 6.5, 0.75);		// cgl1 side panel
	tp.CreateDisplayList(YZ, 129, 128.0, 128.0, 24264.0, 9936.0, 43056.0, 6.5, 0.5);		// gap in middle of library
	tp.CreateDisplayList(YZ, 168, 128.0, 128.0, 24136.0, 9936.0, 43056.0, 2.5, 0.5);		// gap in middle of library
	tp.CreateDisplayList(YZ, 169, 128.0, 128.0, 8813.12, 11344.0, 43056.0, 4.0, 0.5);		// edge of first us window post
	tp.CreateDisplayList(XY, 135, 128.0, 128.0, 24072.0, 10000.0, 43120.0, 1.5, 17.0);		// middle of gap
	tp.CreateDisplayList(XY, 134, 128.0, 128.0, 6514.0, 10000.0, 43120.0, 0.75, 14.5);		// end corner
	tp.CreateDisplayList(XY, 141, 128.0, 128.0, 33104.0, 10000.0, 43152.0, 1.0, 6.0);		// brick between gcl1 doors
	tp.CreateDisplayList(XY, 140, 128.0, 128.0, 34448.0, 9424.0, 43056.0, 12.5, 4.5);		// end below stairs
	tp.CreateDisplayList(YZ, 390, 128.0, 128.0, 10952.0, 10000.0, 43056.0, 2.5, 0.75);		// side of library door
	tp.CreateDisplayList(YZ, 391, 128.0, 128.0, 8189.0, 10000.0, 43056.0, 6.0, 0.5);		// side of library door
	tp.CreateDisplayList(XY, 392, 128.0, 128.0, 10952.0, 10320.0, 43152.0, 0.25, 3.5);		// side edge of library door

	// --------  (Phys Sci Building very end wall by steps) --------
	tp.CreateDisplayList(XY, 142, 128.0, 128.0, 33808.0, 10000.0, 41127.0, 11.5, 6.5);
	tp.CreateDisplayList(XY, 150, 128.0, 128.0, 33808.0, 11024.0, 41127.0, 16.5, 2.5);
	tp.CreateDisplayList(XY, 151, 128.0, 128.0, 34448.0, 9360.0, 41127.0, 6.5, 5.5);		// below window
	tp.CreateDisplayList(XY, 137, 128.0, 128.0, 35280.0, 9296.0, 41127.0, 6.0, 6.5);		// below window
	tp.CreateDisplayList(XY, 138, 128.0, 128.0, 35600.0, 10000.0, 41127.0, 3.5, 6.5);
	tp.CreateDisplayList(XY, 139, 128.0, 128.0, 33872.0, 11216.0, 41127.0, 12.5, 6.0);
	tp.CreateDisplayList(YZ_FLIP, 393, 128.0, 128.0, 33872.0, 11344.0, 41063.0, 4.0, 0.5);	// upstairs edge of window

	// WALL_BRICK_GAP_YZ
	tp.CreateDisplayList(YZ, 180, 128.0, 32.0, 33895.0, 10192.0, 22079.0, 5.0, 0.530);	// end chanc
	tp.CreateDisplayList(YZ, 181, 128.0, 32.0, 33872.0, 10512.0, 30542.0, 2.5, 0.80);	// toilets phys sci
	// WALL_BRICK_GAP2_YZ
	tp.CreateDisplayList(YZ, 182, 128.0, 32.0, 33872.0, 10512.0, 27559.0, 2.5, 0.80);	// toilets phys sci
	// WALL_GAP_1
	tp.CreateDisplayList(XY, 183, 8.0, 128.0, 30792.0, 10000.0, 43056.0, 1.0, 6.0);	// near KBLT
	tp.CreateDisplayList(XY, 184, 8.0, 128.0, 30792.0, 11024.0, 43056.0, 1.0, 6.5);	// as above but upstairs
}

void DrawRoof()
{
	// Chanc Top of Roof
	glNewList(214, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(31740.0, 11364.0, 8100.0);
	glTexCoord2f(0.0, 257.9);
	glVertex3f(31740.0, 11364.0, 8100.0 + (128.0 * 257.9));
	glTexCoord2f(2.0, 273.4);
	glVertex3f(33848.0, 12140.72, 8100.0 + (128.0 * 273.4));
	glTexCoord2f(2.0, 0.0);
	glVertex3f(33848.0, 12140.72, 8100.0);
	glEnd();
	glEndList();
	// Canteen Top of Roof
	glNewList(215, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(2608.0, 12140.72, 8100.0);
	glTexCoord2f(0.0, 273.4);
	glVertex3f(2608.0, 12140.72, 8100.0 + (128.0 * 273.4));
	glTexCoord2f(2.0, 257.9);
	glVertex3f(4716.0, 11364.0, 8100.0 + (128.0 * 257.9));
	glTexCoord2f(2.0, 0.0);
	glVertex3f(4716.0, 11364.0, 8100.0);
	glEnd();
	glEndList();
	// Library Top of Roof
	glNewList(216, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(4716.0, 11364.0, 40983.2);
	glTexCoord2f(211.125, 0.0);
	glVertex3f(4716.0 + (128.0 * 211.125), 11364.0, 40983.2);
	glTexCoord2f(227.59, 16.15);
	glVertex3f(4716.0 + (128.0 * 227.59), 12140.72, 43095.2);
	glTexCoord2f(-16.47, 16.15);
	glVertex3f(2608.0, 12140.72, 43095.2);
	glEnd();
	glEndList();
	// Chanc Side Planks
	glNewList(250, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(31868.0, 11366.0, 8100.0);
	glTexCoord2f(0.0, 257.9);
	glVertex3f(31868.0, 11366.0, 8100.0 + (128.0 * 257.9));
	glTexCoord2f(16.48, 273.4);
	glVertex3f(33848.0, 12094.72, 8100.0 + (128.0 * 273.4));
	glTexCoord2f(16.48, 0.0);
	glVertex3f(33848.0, 12094.72, 8100.0);
	glEnd();
	glEndList();
	// Chanc Side Beams Bottom
	glNewList(253, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(31868.0, 11284.0, 10105.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(31868.0, 11284.0, 10137.0);
	glTexCoord2f(16.48, 1.0);
	glVertex3f(33848.0, 12012.72, 10137.0);
	glTexCoord2f(16.48, 0.0);
	glVertex3f(33848.0, 12012.72, 10105.0);
	glEnd();
	glEndList();
	// Chanc Side Beams Side
	glNewList(255, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(31868.0, 11284.0, 10105.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(31868.0, 11284.0 + 82.0, 10105.0);
	glTexCoord2f(16.48, 1.0);
	glVertex3f(33848.0, 12012.72 + 82.0, 10105.0);
	glTexCoord2f(16.48, 0.0);
	glVertex3f(33848.0, 12012.72, 10105.0);
	glEnd();
	glEndList();
	// Chanc Side Planks (between chanc and phys sci)
	glNewList(251, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(35748.0, 11366.0, 22046.0);
	glTexCoord2f(0.0, 25.79);
	glVertex3f(35748.0, 11366.0, 22046.0 + (128.0 * 25.79));
	glTexCoord2f(15.82, 25.79);
	glVertex3f(33848.0, 12065.28, 22046.0 + (128.0 * 25.79));
	glTexCoord2f(15.82, 0.0);
	glVertex3f(33848.0, 12065.28, 22046.0);
	glEnd();
	glEndList();
	// Chanc Side Beams Bottom (between phys sci and chanc)
	glNewList(254, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(35748.0, 11284.0, 22096.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(35748.0, 11284.0, 22096.0 + 32.0);
	glTexCoord2f(15.82, 1.0);
	glVertex3f(33848.0, 11983.28, 22096.0 + 32.0);
	glTexCoord2f(15.82, 0.0);
	glVertex3f(33848.0, 11983.28, 22096.0);
	glEnd();
	glEndList();
	// Chanc Side Beams Side (between phys sci and chanc)
	glNewList(256, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(35748.0, 11284.0, 22096.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(35748.0, 11284.0 + 82.0, 22096.0);
	glTexCoord2f(15.82, 1.0);
	glVertex3f(33848.0, 11983.28 + 82.0, 22096.0);
	glTexCoord2f(15.82, 0.0);
	glVertex3f(33848.0, 11983.28, 22096.0);
	glEnd();
	glEndList();
	// Chanc Side Planks (between phys sci and library)
	glNewList(252, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(36108.0, 11019.68, 41127.0);
	glTexCoord2f(0.0, 15.1);
	glVertex3f(36108.0, 11019.68, 41127.0 + (128.0 * 15.1));
	glTexCoord2f(19.44, 15.1);
	glVertex3f(33848.0, 12061.55, 41127.0 + (128.0 * 15.1));
	glTexCoord2f(19.44, 0.0);
	glVertex3f(33848.0, 12061.55, 41127.0);
	glEnd();
	glEndList();
	// Chanc Side Beams Bottom (between phys sci and library)
	glNewList(298, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(36108.0, 10937.68, 41226.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(36108.0, 10937.68, 41226.0 + 32.0);
	glTexCoord2f(19.44, 1.0);
	glVertex3f(33848.0, 11979.55, 41226.0 + 32.0);
	glTexCoord2f(19.44, 0.0);
	glVertex3f(33848.0, 11979.55, 41226.0);
	glEnd();
	glEndList();
	// Chanc Side Beams Side (between phys sci and library)
	glNewList(299, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(36108.0, 10937.68, 41226.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(36108.0, 10937.68 + 82.0, 41226.0);
	glTexCoord2f(19.44, 1.0);
	glVertex3f(33848.0, 11979.55 + 82.0, 41226.0);
	glTexCoord2f(19.44, 0.0);
	glVertex3f(33848.0, 11979.55, 41226.0);
	glEnd();
	glEndList();
	// Library Side Planks
	glNewList(257, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(4541.0, 11366.0, 43056.0 - 1942.0);
	glTexCoord2f(213.45, 0.0);
	glVertex3f(4541.0 + (128.0 * 213.45), 11366.0, 43056.0 - 1942.0);
	glTexCoord2f(228.6, 16.15);
	glVertex3f(4541.0 + (128.0 * 213.45) + 1940.0, 12080.0, 43056.0);
	glTexCoord2f(-15.1, 16.15);
	glVertex3f(2608.0, 12080.0, 43056.0);
	glEnd();
	glEndList();
	// Library Side Beams Bottom
	glNewList(296, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(4541.0, 11283.0, 41114.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(4573.0, 11283.0, 41114.0);
	glTexCoord2f(16.15, 1.0);
	glVertex3f(4573.0, 11997.0, 43056.0);
	glTexCoord2f(16.15, 0.0);
	glVertex3f(4541.0, 11997.0, 43056.0);
	glEnd();
	glEndList();
	// Library Side Beams
	glNewList(297, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(4541.0, 11283.0, 41114.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(4541.0, 11365.0, 41114.0);
	glTexCoord2f(16.15, 1.0);
	glVertex3f(4541.0, 12079.0, 43056.0);
	glTexCoord2f(16.15, 0.0);
	glVertex3f(4541.0, 11997.0, 43056.0);
	glEnd();
	glEndList();

	// spacer between phys sci
	tp.CreateDisplayList(YZ, 97, 32.0, 128.0, 33808.0, 12048.0, 25344.0, 1.0, 123.3);
	// spacer between phys sci amd chanc blocks
	tp.CreateDisplayList(YZ, 98, 32.0, 128.0, 35748.0, 11334.0, 22096.0, 1.0, 25.38);
	// spacer above main posts (chanc side)
	tp.CreateDisplayList(YZ, 99, 32.0, 128.0, 31868.0, 11334.0, 8100.0, 1.0, 257.9);
	// spacer above library
	tp.CreateDisplayList(XY, 202, 128.0, 32.0, 4541.0, 12048.0, 43056.0, 230.0, 1.0);
	// spacer above main posts (library side)
	tp.CreateDisplayList(XY, 203, 128.0, 32.0, 4541.0, 11332.0, 41114.0, 213.5, 1.08);
	// spacer above chanc
	tp.CreateDisplayList(YZ, 204, 128.0, 128.0, 33808.0, 11999.0, 8100.0, 0.64, 109.35);
	tp.CreateYtoZWindowList(205, 33848.0, 11954.0, 144.0, 22096.0, 3248.0, 0.64, 25.375);
	// centre beam between chanc and phys sci
	tp.CreateDisplayList(XZ, 426, 64.0, 128.0, 33848.0, 11954.0, 22096.0, 1.0, 25.375);
	// top corner spacer
	tp.CreateDisplayList(XY, 427, 64.0, 128.0, 33808.0, 11999.0, 22096.0, 0.75, 0.75);

	// Joins where roof slants
	DrawAngledRoofBeam(1, 33848.0 - 1867.0, 12012.72 - 687.13, 41226.0, 15.21);
	DrawAngledRoofBeam(2, 33848.0 - 1481.0, 12012.72 - 545.07, 41612.0, 12.0);
	DrawAngledRoofBeam(3, 33848.0 - 1095.0, 12012.72 - 403.01, 41998.0, 8.78);
	DrawAngledRoofBeam(4, 33848.0 - 709.0, 12012.72 - 260.94, 42384.0, 5.57);
	DrawAngledRoofBeam(5, 33848.0 - 323.0, 12012.72 - 118.88, 42770.0, 2.36);
	DrawAngledRoofBeam2(170, 31980.0, 11998.0 - 672.41, 43056.0 - 1827.0, 15.21);
	DrawAngledRoofBeam2(171, 32366.0, 11998.0 - 530.35, 43056.0 - 1441.0, 12.0);
	DrawAngledRoofBeam2(172, 32752.0, 11998.0 - 388.28, 43056.0 - 1055.0, 8.78);
	DrawAngledRoofBeam2(173, 33138.0, 11998.0 - 246.22, 43056.0 - 669.0, 5.57);
	DrawAngledRoofBeam2(174, 33524.0, 11998.0 - 104.16, 43056.0 - 283.0, 2.36);
}

// --------------------------------------------------------------------------------------
//  Creates Angled Roof Beams
// --------------------------------------------------------------------------------------
void DrawAngledRoofBeam(int listNo, GLdouble x, GLdouble y, GLdouble z, GLdouble beamSize)
{
	glNewList(listNo, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x, y, z + 32.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x, y, z);
	glTexCoord2f(beamSize, 1.0);
	glVertex3f(33848.0, 12012.72, z);
	glTexCoord2f(beamSize, 0.0);
	glVertex3f(33848.0, 12012.72, z + 32.0);
	glEnd();
	glEndList();
	glNewList(listNo + 5, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x, y, z);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x, y + 82.0, z);
	glTexCoord2f(beamSize, 1.0);
	glVertex3f(33848.0, 12012.72 + 82.0, z);
	glTexCoord2f(beamSize, 0.0);
	glVertex3f(33848.0, 12012.72, z);
	glEnd();
	glEndList();
}

void DrawAngledRoofBeam2(int listNo, GLdouble x, GLdouble y, GLdouble z, GLdouble beamSize)
{
	glNewList(listNo, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x, y, z);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x + 32.0, y, z);
	glTexCoord2f(1.0, beamSize);
	glVertex3f(x + 32.0, 11998.0, 43056);
	glTexCoord2f(0.0, beamSize);
	glVertex3f(x, 11998.0, 43056);
	glEnd();
	glEndList();
	glNewList(listNo + 5, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x, y, z);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x, y + 82.0, z);
	glTexCoord2f(1.0, beamSize);
	glVertex3f(x, 11998.0 + 82.0, 43056);
	glTexCoord2f(0.0, beamSize);
	glVertex3f(x, 11998.0, 43056);
	glEnd();
	glEndList();
}

void DrawEntranceSteps()
{
	step = 10000.0;
	stepLength = 9808.0;
	for (int i = 258; i < 274; i++)
	{
		tp.CreateDisplayList(XZ, i, 1024.0, 512.0, 31582.0, step, stepLength, 2.2, 0.277);
		tp.CreateDisplayList(XY, i + 16, 64.0, 64.0, 31582.0, step - 64.0, stepLength, 35.0, 1.0);
		step -= 48.0;
		stepLength -= 142.0;
		if ((i + 3) % 4 == 0)
		{
			stepLength -= 500.0;
			step -= 48.0;
		}
	}
	step = 9808.0;
	stepLength = 8882.0;
	for (int i = 290; i < 293; i++)
	{
		tp.CreateDisplayList(XZ, i, 1024.0, 512.0, 31582.0, step, stepLength, 2.2, 1.0);
		tp.CreateDisplayList(XY, i + 3, 64.0, 64.0, 31582.0, step - 64.0, stepLength, 35.0, 1.0);
		step -= 239.0;
		stepLength -= 1068.0;
	}

	// steps next to GCL1
	tp.CreateDisplayList(XZ, 206, 128.0, 1024.0, 34508.0, 10000.0, 41127, 1.0, 0.942);
	tp.CreateDisplayList(XZ, 207, 256.0, 1024.0, 34352.0, 10000.0, 41127, 0.609, 0.942);

}

void DrawBench()
{
	tp.CreateDisplayList(XZ, 400, 64.0, 64.0, 31760.0, 10147.0, 10894.0, 3.0, 7.5);
	tp.CreateDisplayList(XY, 401, 64.0, 64.0, 31760.0, 10000.0, 10894.0, 3.0, 2.3);
	tp.CreateDisplayList(XY, 402, 64.0, 64.0, 31760.0, 10000.0, 10894.0, 3.0, 1.72);
	tp.CreateDisplayList(YZ, 403, 64.0, 64.0, 31760.0, 10000.0, 10894.0, 1.72, 0.78);
	tp.CreateDisplayList(YZ, 404, 64.0, 64.0, 31760.0, 10107.0, 10944.0, 0.625, 5.938);
	tp.CreateDisplayList(YZ, 405, 64.0, 64.0, 31760.0, 10107.0, 10894.0, 0.625, 0.78);
	tp.CreateDisplayList(YZ_FLIP, 406, 64.0, 64.0, 31760.0, 10107.0, 11324.0, 0.625, 0.78);

	tp.CreateDisplayList(XZ, 407, 64.0, 64.0, 5410.0, 10147.0, 41008.0, 7.5, 3.0);
	tp.CreateDisplayList(YZ, 408, 64.0, 64.0, 5410.0, 10000.0, 41008.0, 2.3, 3.0);
	tp.CreateDisplayList(YZ, 409, 64.0, 64.0, 5410.0, 10000.0, 41008.0, 1.72, 3.0);
	tp.CreateDisplayList(XY, 410, 64.0, 64.0, 5410.0, 10000.0, 41008.0, 0.78, 1.72);
	tp.CreateDisplayList(XY, 411, 64.0, 64.0, 5460.0, 10107.0, 41008.0, 5.938, 0.625);
	tp.CreateDisplayList(XY, 412, 64.0, 64.0, 5410.0, 10107.0, 41008.0, 0.78, 0.625);
	tp.CreateDisplayList(XY_FLIP, 413, 64.0, 64.0, 5410.0 + 430.0, 10107.0, 41008.0, 0.78, 0.625);
}

void DrawExtras()
{
	tp.CreateDisplayList(YZ, 300, 256.0, 1024.0, 33808.0, 10576.0, 25472.0, 1.0, 1.0);		// Rusty Man

	tp.CreateDisplayList(YZ, 301, 512.0, 256.0, 33792.0, 10320.0, 40794.0, 0.75, 0.609);	// Sign 1 (end of phys sci)
	tp.CreateDisplayList(XY, 302, 16.0, 512.0, 33792.0, 10320.0, 40794.0, 1.0, 0.75);		// side of sign 1
	tp.CreateDisplayList(XY, 303, 16.0, 512.0, 33792.0, 10320.0, 40950.0, 1.0, 0.75);		// side of sign 1
	tp.CreateDisplayList(XY, 304, 512.0, 512.0, 33637.0, 10410.0, 43040.0, 0.75, 0.574);	// Sign 2 (GCL1)

	tp.CreateDisplayList(YZ, 305, 512.0, 16.0, 33637.0, 10410.0, 43040.0, 0.574, 1.0);		// side of sign 2

	tp.CreateDisplayList(XY, 306, 16.0, 32.0, 25633.0, 10902.0, 42756.0, 152.88, 1.0);		// KBLT edge top
	tp.CreateDisplayList(XY, 307, 32.0, 16.0, 25608.0, 10000.0, 42756.0, 1.0, 56.375);		// KBLT edge left
	tp.CreateDisplayList(XY_FLIP, 308, 32.0, 16.0, 28072.0, 10000.0, 42756.0, 1.0, 56.375);// KBLT right
	tp.CreateDisplayList(XY, 309, 1.0, 1.0, 25608.0, 10902.0, 42756.0, 25.0, 32.0);		// KBLT corner
	tp.CreateDisplayList(YZ, 310, 2.0, 16.0, 29512.0, 10288.0, 43040.0, 240.0, 1.0);		// Side of Nexus

	tp.CreateDisplayList(YZ, 311, 2.0, 16.0, 24456.0, 10320.0, 43040.0, 224.0, 1.0);		// Side of Glassboards
	tp.CreateDisplayList(YZ, 435, 2.0, 16.0, 7304.0, 10256.0, 43040.0, 192.0, 1.0);		// Side of Glassboards

	tp.CreateDisplayList(XY, 312, 128.0, 128.0, 33752.0, 10659.0, 10511.0, 0.75, 0.75);	// security sign
	tp.CreateDisplayList(XY, 313, 128.0, 128.0, 33752.0, 10659.0, 10513.0, 0.75, 0.75);	// security sign

	tp.CreateDisplayList(XY, 314, 256.0, 128.0, 33660.0, 10836.0, 20111.0, 0.578, 0.561);	// PSC sign
	tp.CreateDisplayList(XY, 315, 256.0, 128.0, 33660.0, 10836.0, 20113.0, 0.578, 0.561);	// PSC sign

	tp.CreateDisplayList(YZ, 316, 256.0, 128.0, 33808.0, 10256.0, 34126.0, 1.0, 1.0);		// CO sign

	tp.CreateDisplayList(YZ, 317, 64.0, 64.0, 35856.0, 10000.0, 24996.0, 11.5, 5.47);		// Drinks Machine
	tp.CreateDisplayList(XY, 319, 64.0, 64.0, 34704.0, 10672.0, 24996.0, 18.0, 1.0);		// Drinks Machine
	tp.CreateDisplayList(XZ, 318, 64.0, 64.0, 34704.0, 10736.0, 24996.0, 18.0, 5.5);		// Drinks Machine
	tp.CreateDisplayList(XY, 320, 16.0, 2.0, 35840.0, 10000.0, 24996.0, 1.0, 336.0);		// Drinks Machine
	tp.CreateDisplayList(YZ, 321, 1.0, 1.0, 35458.0, 10000.0, 25016.0, 660.0, 300.0);		// Drinks Machine Sides
	tp.CreateDisplayList(YZ, 322, 1.0, 1.0, 35163.0, 10000.0, 25016.0, 586.2, 300.0);		// Drinks Machine Sides
	tp.CreateDisplayList(YZ, 323, 1.0, 1.0, 34778.0, 10000.0, 25016.0, 593.22, 300.0);		// Drinks Machine Sides

	tp.CreateDisplayList(XZ, 324, 32.0, 32.0, 34064.0, 10000.0, 26704.0, 6.0, 20.0);		// Carpet 1st doorway
	tp.CreateDisplayList(XZ, 429, 32.0, 32.0, 34064.0, 10000.0, 36643.2, 9.0, 17.4);		// Carpet 2nd doorway

	tp.CreateDisplayList(YZ, 326, 256.0, 128.0, 34260.0, 10320.0, 36511.0, 1.1, 1.0);		// No smoke sign doorway 2
	tp.CreateDisplayList(YZ, 327, 256.0, 128.0, 34256.0, 10320.0, 27303.0, 1.1, 1.1);		// No smoke sign doorway 1

	tp.CreateDisplayList(XY, 328, 256.0, 256.0, 33595.0, 10828.0, 40071.0, 0.773, 0.855);	// Sta Travel sign
	tp.CreateDisplayList(YZ, 329, 256.0, 64.0, 33595.0, 10828.0, 40071.0, 0.855, 1.0);		// Sta Travel sign edge
	tp.CreateDisplayList(XY, 330, 16.0, 2.0, 33792.0, 10854.0, 40071.0, 1.0, 76.0);		// Sta Travel sign bracket
	tp.CreateDisplayList(XY, 331, 256.0, 256.0, 33595.0, 10828.0, 40135.0, 0.773, 0.855);	// Sta Travel sign 2
	tp.CreateDisplayList(XZ, 332, 2.0, 64.0, 33595.0, 10828.0, 40071.0, 99.0, 1.0);		// Sta Travel bottom

	tp.CreateDisplayList(XY, 333, 512.0, 512.0, 33808.0, 10192.0, 25344.0, 0.752, 1.05);	// Telephone Back
	tp.CreateDisplayList(XY, 334, 512.0, 32.0, 33882.0, 10598.0, 25173.0, 0.557, 0.719);	// Telephone front
	tp.CreateDisplayList(YZ, 335, 32.0, 256.0, 33882.0, 10598.0, 25173.0, 0.719, 0.7);	// Telephone side top
	tp.CreateDisplayList(XY, 336, 512.0, 16.0, 33882.0, 10621.0, 25173.0, 0.557, 0.75);	// Telephone front
	tp.CreateDisplayList(YZ, 339, 16.0, 256.0, 33882.0, 10621.0, 25173.0, 0.75, 0.7);		// Telephone side
	tp.CreateDisplayList(XZ, 343, 512.0, 128.0, 33882.0, 10268.0, 25250.0, 0.558, 0.75);	// Telephone bottom
	tp.CreateDisplayList(XZ, 348, 2.0, 2.0, 33918.0, 10697.84, 25201.6, 107.0, 56.9);		// telephone roof
	tp.CreateDisplayList(XZ, 349, 2.0, 2.0, 33882.0, 10633.0, 25173.0, 142.6, 2.5);		// telephone roof
	tp.CreateDisplayList(XZ, 388, 2.0, 2.0, 33882.0, 10633.0, 25173.0, 5.0, 89.6);			// telephone roof

	tp.CreateDisplayList(YZ, 345, 2.0, 128.0, 28104.0, 10000.0, 42756.0, 467.0, 1.0); // KBLT side
	tp.CreateDisplayList(YZ, 346, 2.0, 2.0, 28014.0, 10000.0, 42866.0, 416.0, 98.0); // KBLT side


	// TELEPHONE ROOF
	tp.CreateAngledPolygon(337, 512.0, 256.0, 33882.0, 33882.0, 33882.0, 33882.0,
		10268.0, 10268.0, 10598.24, 10598.24,
		25250.0, 25345.34, 25345.34, 25173.0, 6, 4);
	glNewList(338, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(33890.0, 10633.0, 25178.0);
	glTexCoord2f(0.527, 0.0);
	glVertex3f(34160.0, 10633.0, 25178.0);
	glTexCoord2f(0.473, 0.54);
	glVertex3f(34132.0, 10697.84, 25201.6);
	glTexCoord2f(0.055, 0.54);
	glVertex3f(33918.0, 10697.84, 25201.6);
	glEnd();
	glEndList();
	glNewList(341, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(33891.0, 10633.0, 25178.0);
	glTexCoord2f(0.0, 0.637);
	glVertex3f(33891.0, 10633.0, 25341.0);
	glTexCoord2f(0.54, 0.538);
	glVertex3f(33918.5, 10697.84, 25315.6);
	glTexCoord2f(0.54, 0.1);
	glVertex3f(33918.5, 10697.84, 25201.6);
	glEnd();
	glEndList();
	glNewList(342, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(34159.5, 10633.0, 25178.0);
	glTexCoord2f(0.0, 0.637);
	glVertex3f(34159.5, 10633.0, 25341.0);
	glTexCoord2f(0.54, 0.538);
	glVertex3f(34132.0, 10697.84, 25315.6);
	glTexCoord2f(0.54, 0.1);
	glVertex3f(34132.0, 10697.84, 25201.6);
	glEnd();
	glEndList();
	glNewList(340, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(33890.0, 10631.0, 25341.0);
	glTexCoord2f(0.527, 0.0);
	glVertex3f(34160.0, 10631.0, 25341.0);
	glTexCoord2f(0.473, 0.535);
	glVertex3f(34132.0, 10697.84, 25315.4);
	glTexCoord2f(0.055, 0.535);
	glVertex3f(33918.0, 10697.84, 25315.4);
	glEnd();
	glEndList();
	glNewList(395, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(33882.0, 10268.0, 25250.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(33898.0, 10268.0, 25250.0);
	glTexCoord2f(1.0, 0.729);
	glVertex3f(33898.0, 10598.24, 25173.0);
	glTexCoord2f(0.0, 0.729);
	glVertex3f(33882.0, 10598.24, 25173.0);
	glEnd();
	glEndList();

	tp.CreateDisplayList(YZ, 347, 128.0, 128.0, 33808.0, 10384.0, 28519.0, 1.0, 1.0);	// toilets sign

	tp.CreateDisplayList(XZ, 419, 2.0, 128.0, 22928.0, 10870.0, 42960.0, 604.0, 0.78);	// ticket box ledge
	tp.CreateDisplayList(XY, 420, 2.0, 32.0, 22928.0, 10870.0, 42960.0, 604.0, 1.0);	// ticket box ledge edge
	tp.CreateDisplayList(YZ, 421, 32.0, 2.0, 22928.0, 10870.0, 42960.0, 1.0, 49);		// ticket box ledge edge side



}

void DrawLargerTextures()
{
	// CHANC
	// Gap between chanc and phy sci y1142 z3248
	tp.CreateYtoZWindowList(350, 35879.0, 10000.0, 1147.0, 22096, 1540.0, 0.714, 0.95);	// w190.63  245
	tp.CreateYtoZWindowList(351, 35879.0, 10000.0, 1147.0, 23740, 1605.0, 0.714, 0.98);	// w183
	// chanc windows
	tp.CreateYtoZWindowList(352, 33895.0, 10256.0, 576.0, 9599.0, 867.0, 0.664, 1.0);		// w170
	// chanc doors
	tp.CreateYtoZWindowList(382, 33895.0, 10000.0, 832.0, 10559.0, 867.0, 0.96, 1.0);		// w246

	// PHYS SCI
	// phys sci upstairs
	tp.CreateYtoZWindowList(353, 33895.0, 11411.0, 445.0, 26702.0, 883.0, 0.504, 1.0);		// 129x256
	// phys sci toilets
	tp.CreateYtoZWindowList(354, 33895.0, 10576.0, 255.0, 27662.0, 883.0, 0.578, 1.0);		// 73.93x256
	// phys sci toilets 3rd
	tp.CreateYtoZWindowList(355, 33895.0, 10576.0, 255.0, 33422.0, 919.0, 0.57, 1.0);		// 71.04x256
	// serving window
	tp.CreateYtoZWindowList(356, 33895.0, 10320.0, 511.0, 34419.0, 845.0, 0.605, 1.0);		// 155x256
	// last window
	tp.CreateYtoZWindowList(357, 33895.0, 10320.0, 511.0, 38239.0, 320.0, 1.0, 0.626);		// 256x160.3
	// first purple post window
	tp.CreateYtoZWindowList(358, 33895.0, 10000.0, 832.0, 31519.0, 865.0, 0.96, 1.0);		// 246.2x256
	// second purple post window
	tp.CreateYtoZWindowList(359, 33895.0, 10000.0, 832.0, 32461.0, 883.0, 0.94, 1.0);		// 241.2x256
	// third purple post window
	tp.CreateYtoZWindowList(360, 33895.0, 10000.0, 832.0, 35341.0, 867.0, 0.96, 1.0);		// 246.2x256
	// first red window
	tp.CreateYtoZWindowList(361, 33865.0, 10000.0, 832.0, 39216.0, 839.0, 0.992, 1.0);		// 254.5x256
	// second red window
	tp.CreateYtoZWindowList(362, 33865.0, 10000.0, 832.0, 40151.0, 448.0, 1.0, 0.54);		// 256x138

	tp.CreateXtoYWindowList(363, 43040.0, 29512.0, 1280.0, 10288.0, 480.0, 1.0, 0.745);	// NEXUS
	tp.CreateXtoYWindowList(364, 43040.0, 28360.0, 896.0, 10320.0, 448.0, 1.0, 1.0);		// Glassboard 1
	tp.CreateXtoYWindowList(365, 43040.0, 24456.0, 896.0, 10320.0, 448.0, 1.0, 1.0);		// Glassboard 2
	tp.CreateXtoYWindowList(366, 43040.0, 7304.0, 768.0, 10256.0, 384.0, 1.0, 1.0);		// Glassboard 2
	tp.CreateXtoYWindowList(367, 42756.0, 25640.0, 2432.0, 10000.0, 902.0, 1.0, 0.742);	// KBLT

	tp.CreateYtoZWindowList(368, 33840.0, 9086.0, 2200.0, 4688.0, 1100.0, 1.0, 1.0);
	tp.CreateXtoYWindowList(369, 4688.0, 31632.0, 2208.0, 9086.0, 2208.0, 1.0, 1.0);

	tp.CreateXtoYWindowList(370, 25016.0, 35458.0, 317.12, 10000.0, 660.0, 0.96, 1.0);		// Coke Machine
	tp.CreateXtoYWindowList(371, 25016.0, 35163.0, 255.0, 10000.0, 586.2, 0.867, 1.0);		// Coffee Machine
	tp.CreateXtoYWindowList(372, 25016.0, 34778.0, 350.0, 10000.0, 593.22, 0.59, 1.0);		// Sweet Machine
	// phys sci door 1
	tp.CreateYtoZWindowList(373, 34320.0, 10000.0, 832.0, 26752.0, 552.0, 1.0, 0.66);		// 256x169.85
	// phys sci toilets
	tp.CreateYtoZWindowList(374, 33872.0, 10000.0, 768.0, 28646.0, 322.0, 1.0, 0.833);		// 256x106.67 toilet doors
	//////////////////////// phys sci door 2
	tp.CreateYtoZWindowList(375, 37600.0, 10000.0, 832.0, 36639.0, 1216, 0.68, 1.0);		// 256x175.16

	tp.CreateXtoYWindowList(379, 43152.0, 33232.0, 384.0, 10000.0, 768.0, 1.0, 1.0);		// GCL1 doorway
	tp.CreateXtoYWindowList(380, 43152.0, 32720.0, 384.0, 10000.0, 768.0, 1.0, 1.0);		// GCL1 doorway

	tp.CreateYtoZWindowList(381, 36047, 9422.0, 1410.0, 41127.0, 1929.0, 0.725, 1.0);	// Exit East  375x512

	tp.CreateXtoYWindowList(383, 43152.0, 11055.0, 1014.0, 10388.0, 380.0, 1.0, 0.75);	// 256x96 Library Window downstairs
	tp.CreateXtoYWindowList(384, 43152.0, 8879.0, 1014.0, 11412.0, 444.0, 1.0, 0.876);	// 256x112 Library Window upstairs
	tp.CreateXtoYWindowList(385, 43120.0, 8189.0, 614.0, 10000.0, 768.0, 0.781, 1.0);	// library door 1
	tp.CreateXtoYWindowList(386, 43152.0, 8880.0, 2072.0, 9998.0, 770.0, 1.0, 0.742);	// 256x136 library door 2
	tp.CreateXtoYWindowList(387, 43152.0, 23023.0, 1014.0, 10305.0, 464.0, 1.0, 0.914);// silver long library window
	tp.CreateXtoYWindowList(389, 43096.0, 8803.0, 77.0, 9998.0, 775.0, 0.6, 1.0);		// library post
	tp.CreateYtoZWindowList(414, 8803.0, 9998.0, 775.0, 43096.0, 77.0, 1.0, 0.5625);	// library post
	tp.CreateYtoZWindowList(422, 33872.0, 10768.0, 64.0, 28646.0, 856.0, 1.0, 1.0);	// top of toilet door female
	tp.CreateYtoZWindowList(423, 33872.0, 10768.0, 64.0, 30566.0, 840.0, 1.0, 1.0);	// top of toilet door male
	tp.CreateYtoZWindowList(450, 2352.0, 10000.0, 896.0, 41168.0, 1792.0, 1.0, 1.0);	// west exit
	tp.CreateDisplayList(XZ, 451, 400.0, 256.0, 2352.0, 10896.0, 41168.0, 0.64, 7.0);  // above west exit
	tp.CreateXtoYWindowList(452, 41127.0, 35280.0, 320.0, 10128.0, 704.0, 0.91, 1.0);	// w 233 window by steps (end of phys sci)
	tp.CreateDisplayList(XZ, 453, 2.0, 2.0, 35856.0, 9400.0, 40500.0, 180.0, 1380.0);  // block at bottom of steps
}

void DrawGrass()
{
	tp.CreateDisplayList(XZ, 79, 64.0, 64.0, 4848.0, 9086.0, 3408.0, 417.5, 45.0);
	tp.CreateDisplayList(XZ, 111, 64.0, 64.0, 4848.0, 10000.0, 10000.0, 417.5, 481.5);

	// Slope ate the entrance
	tp.CreateAngledPolygon(198, 64.0, 64.0, 4848.0, 31568.0, 31568.0, 4848.0,
		9086.0, 9086.0, 10000.0, 10000.0,
		6200.0, 6200.0, 10000.0, 10000.0, 1, 1);
	// Lower hill in the centre
	tp.CreateDisplayList(XZ, 460, 64.0, 64.0, 9000.0, 10200.0, 19000.0, 203.125, 281.25);
	tp.CreateAngledPolygon(461, 64.0, 64.0, 9000.0, 22000.0, 22000.0, 9000.0,
		10000.0, 10000.0, 10200.0, 10200.0,
		17000.0, 17000.0, 19000.0, 19000.0, 1, 1);

	tp.CreateAngledPolygon(462, 64.0, 64.0, 9000.0, 22000.0, 22000.0, 9000.0,
		10200.0, 10200.0, 10000.0, 10000.0,
		37000.0, 37000.0, 40000.0, 40000.0, 1, 1);

	tp.CreateAngledPolygon(463, 64.0, 64.0, 22000.0, 27000.0, 27000.0, 22000.0,
		10200.0, 10000.0, 10000.0, 10200.0,
		19000.0, 19000.0, 37000.0, 37000.0, 1, 1);

	tp.CreateAngledPolygon(464, 64.0, 64.0, 6500.0, 9000.0, 9000.0, 6500.0,
		10000.0, 10200.0, 10200.0, 10000.0,
		19000.0, 19000.0, 37000.0, 37000.0, 1, 1);

	tp.CreateAngledPolygon(465, 64.0, 64.0, 9000.0, 9000.0, 9000.0, 6500.0,
		10000.0, 10000.0, 10200.0, 10000.0,
		17000.0, 17000.0, 19000.0, 19000.0, 4, 1);

	tp.CreateAngledPolygon(466, 64.0, 64.0, 22000.0, 22000.0, 27000.0, 22000.0,
		10000.0, 10000.0, 10000.0, 10200.0,
		17000.0, 17000.0, 19000.0, 19000.0, 1, 1);

	tp.CreateAngledPolygon(467, 64.0, 64.0, 22000.0, 27000.0, 22000.0, 22000.0,
		10200.0, 10000.0, 10000.0, 10000.0,
		37000.0, 37000.0, 40000.0, 40000.0, 4, 1);

	tp.CreateAngledPolygon(468, 64.0, 64.0, 6500.0, 9000.0, 9000.0, 9000.0,
		10000.0, 10200.0, 10000.0, 10000.0,
		37000.0, 37000.0, 40000.0, 40000.0, 1, 1);

	// higher hilltop
	tp.CreateDisplayList(XZ, 477, 64.0, 64.0, 14000.0, 10425.0, 28000.0, 62.5, 78.125);

	tp.CreateAngledPolygon(469, 64.0, 64.0, 14000.0, 18000.0, 18000.0, 14000.0,
		10200.0, 10200.0, 10425.0, 10425.0,
		23000.0, 23000.0, 28000.0, 28000.0, 1, 1);

	tp.CreateAngledPolygon(470, 64.0, 64.0, 14000.0, 18000.0, 18000.0, 14000.0,
		10425.0, 10425.0, 10200.0, 10200.0,
		33000.0, 33000.0, 36000.0, 36000.0, 1, 1);

	tp.CreateAngledPolygon(471, 64.0, 64.0, 10000.0, 14000.0, 14000.0, 10000.0,
		10200.0, 10425.0, 10425.0, 10200.0,
		28000.0, 28000.0, 33000.0, 33000.0, 1, 1);

	tp.CreateAngledPolygon(472, 64.0, 64.0, 18000.0, 22000.0, 22000.0, 18000.0,
		10425.0, 10200.0, 10200.0, 10425.0,
		28000.0, 28000.0, 33000.0, 33000.0, 1, 1);

	tp.CreateAngledPolygon(473, 64.0, 64.0, 14000.0, 14000.0, 14000.0, 10000.0,
		10200.0, 10200.0, 10425.0, 10200.0,
		23000.0, 23000.0, 28000.0, 28000.0, 4, 1);

	tp.CreateAngledPolygon(474, 64.0, 64.0, 18000.0, 18000.0, 22000.0, 18000.0,
		10200.0, 10200.0, 10200.0, 10425.0,
		23000.0, 23000.0, 28000.0, 28000.0, 1, 1);

	tp.CreateAngledPolygon(475, 64.0, 64.0, 18000.0, 22000.0, 18000.0, 18000.0,
		10425.0, 10200.0, 10200.0, 10200.0,
		33000.0, 33000.0, 36000.0, 36000.0, 1, 1);

	tp.CreateAngledPolygon(476, 64.0, 64.0, 10000.0, 14000.0, 14000.0, 14000.0,
		10200.0, 10425.0, 10200.0, 10200.0,
		33000.0, 33000.0, 36000.0, 36000.0, 1, 1);
}

void DrawLights()
{
	// Fittings
	glNewList(376, GL_COMPILE);
	glBegin(GL_QUADS);
	gluQuadricDrawStyle(glu_cylinder, GLU_LINE);
	gluCylinder(glu_cylinder, 75.0, 75.0, 60.0, 15, 100);
	glEnd();
	glEndList();

	tp.CreateDisplayList(YZ, 377, 2.0, 8.0, 32900.0, 11330.0, 11150.0, 220.0, 1.0);	// supports
	tp.CreateDisplayList(XY, 378, 8.0, 2.0, 32900.0, 11330.0, 11150.0, 1.0, 220.0);	// supports
}

void DrawCylinders()
{
	// Drainpipe
	glNewList(437, GL_COMPILE);
	glBegin(GL_QUADS);
	gluQuadricDrawStyle(glu_cylinder, GLU_FILL);
	gluCylinder(glu_cylinder, 10.0, 10.0, 2.0, 15, 15);
	glEnd();
	glEndList();

	// Serving Counter
	glNewList(438, GL_COMPILE);
	glBegin(GL_QUADS);
	gluQuadricDrawStyle(glu_cylinder, GLU_FILL);
	gluCylinder(glu_cylinder, 138.0, 138.0, 16.0, 20, 50);
	glEnd();
	glEndList();
	glNewList(441, GL_COMPILE);
	glBegin(GL_QUADS);
	gluQuadricDrawStyle(glu_cylinder, GLU_FILL);
	gluDisk(glu_cylinder, 0.0, 138.0, 20, 50);
	glEnd();
	glEndList();

	tp.CreateDisplayList(XZ, 439, 1.0, 1.0, 33800.0, 10340.0, 34710.0, 120.0, 276.0);
	tp.CreateDisplayList(XY, 440, 4.0, 16.0, 33800.0, 10324.0, 34710.0, 30.0, 1.0);

}

void DrawStepBricks()
{
	tp.CreateDisplayList(YZ, 478.0, 128.0, 128.0, 31582.0, 9914.0, 9872.0, 1.7188, 1.75);
	tp.CreateDisplayList(YZ, 488.0, 32.0, 128.0, 31582.0, 10134.0, 9868.0, 1.0, 1.78);

	tp.CreateDisplayList(YZ, 479.0, 128.0, 128.0, 31582.0, 9530.0, 9006.0, 3.21875, 6.0);
	tp.CreateDisplayList(YZ, 489.0, 32.0, 128.0, 31582.0, 9942.0, 9004.0, 1.0, 2.55);

	tp.CreateDisplayList(YZ, 480.0, 128.0, 128.0, 31582.0, 9350.0, 7918.0, 2.90625, 6.0);
	tp.CreateDisplayList(YZ, 490.0, 32.0, 128.0, 31582.0, 9722.0, 7916.0, 1.0, 3.0);

	tp.CreateDisplayList(YZ, 481.0, 128.0, 128.0, 31582.0, 9158.0, 6830.0, 2.375, 6.0);
	tp.CreateDisplayList(YZ, 491.0, 32.0, 128.0, 31582.0, 9462.0, 6830.0, 1.0, 2.99);

	tp.CreateDisplayList(YZ, 482.0, 128.0, 128.0, 31582.0, 8966.0, 4590.0, 2.0, 15.0);
	tp.CreateDisplayList(YZ, 492.0, 32.0, 128.0, 31582.0, 9222.0, 4590.0, 1.0, 12.0);

	tp.CreateAngledPolygon(483, 128.0, 128.0, 31582.0, 31582.0, 31582.0, 31582.0,
		9094.0, 9094.0, 9462.0, 9094.0,
		5742.0, 6830.0, 6830.0, 5742.0, 5, 1);
	tp.CreateDisplayList(YZ, 493.0, 32.0, 128.0, 31582.0, 9222.0, 6126.0, 1.0, 5.92);

	tp.CreateAngledPolygon(484, 128.0, 128.0, 31582.0, 31582.0, 31582.0, 31582.0,
		9414.0, 9414.0, 9722.0, 9414.0,
		7086.0, 7918.0, 7918.0, 7086.0, 5, 1);
	tp.CreateDisplayList(YZ, 494.0, 32.0, 128.0, 31582.0, 9462.0, 7213.0, 1.0, 5.93);

	tp.CreateAngledPolygon(485, 128.0, 128.0, 31582.0, 31582.0, 31582.0, 31582.0,
		9594.0, 9594.0, 9942.0, 9722.0,
		8302.0, 9006.0, 9006.0, 8302.0, 5, 1);
	tp.CreateDisplayList(YZ, 495.0, 32.0, 128.0, 31582.0, 9722.0, 8302.0, 1.0, 5.82);


	tp.CreateAngledPolygon(486, 128.0, 128.0, 31582.0, 31582.0, 31582.0, 31582.0,
		9914.0, 9914.0, 10134.0, 9914.0,
		9262.0, 9872.0, 9872.0, 9262.0, 5, 1);
	tp.CreateDisplayList(YZ, 496.0, 32.0, 128.0, 31582.0, 9942.0, 9332.4, 1.0, 4.545);

	tp.CreateDisplayList(XZ, 497.0, 64.0, 128.0, 31518.0, 10166.0, 9868.0, 1.0, 1.78);
	tp.CreateDisplayList(XZ, 498.0, 64.0, 128.0, 31518.0, 9974.0, 9004.0, 1.0, 2.55);
	tp.CreateDisplayList(XZ, 499.0, 64.0, 128.0, 31518.0, 9754.0, 7916.0, 1.0, 3.0);
	tp.CreateDisplayList(XZ, 500.0, 64.0, 128.0, 31518.0, 9494.0, 6830.0, 1.0, 2.99);
	tp.CreateDisplayList(XZ, 501.0, 64.0, 128.0, 31518.0, 9254.0, 4590.0, 1.0, 12.0);
	tp.CreateDisplayList(XZ, 502.0, 64.0, 128.0, 31518.0, 9254.0, 6126.0, 1.0, 5.92);
	tp.CreateDisplayList(XZ, 503.0, 64.0, 128.0, 31518.0, 9494.0, 7213.0, 1.0, 5.95);
	tp.CreateDisplayList(XZ, 504.0, 64.0, 128.0, 31518.0, 9754.0, 8302.0, 1.0, 5.82);
	tp.CreateDisplayList(XZ, 505.0, 64.0, 128.0, 31518.0, 9974.0, 9332.4, 1.0, 4.545);
	tp.CreateDisplayList(XY, 506.0, 64.0, 32.0, 31518.0, 10134.0, 10095.84, 1.0, 1.0);
	tp.CreateDisplayList(XY, 507.0, 64.0, 64.0, 31518.0, 9914.0, 10095.84, 1.0, 3.4376);
}

//--------------------------------------------------------------------------------------
//  Map and Welcome screens
//--------------------------------------------------------------------------------------
void DrawMapExit()
{
	tp.CreateDisplayList(0, 448, 256.0, 256.0, 10.0, 10.0, 0.0, 0.855, 1.0); // map
	tp.CreateDisplayList(0, 449, 512.0, 512.0, 0.0, 0.0, 0.0, 1.0, 1.0);	  // welcome screen
	tp.CreateDisplayList(0, 454, 256.0, 64.0, 0.0, 0.0, 0.0, 1.0, 1.0);	  // welcome screen
}
