#include "LevelHandler.h"

enum levelStage { zero, one, two, three };
levelStage lvlStage = one;
Point4 camPos = { 0.0, 9500.0, 0.0, 90.0 };

GLdouble currXPos;
GLdouble currYPos;
GLdouble currZPos;

LevelMap level1Map(7,7);
LevelMap *tempLevelMap = nullptr;
map<int, vector<LevelMap>> mapList;

Point3D gameFloor[4] = { {1000, 9000, 1000},{1000, 9000, -1000},{-1000, 9000, -1000},{-1000, 9000, 1000} };
Point3D wall[4] = { {1000, 9000, 1000},{1000, 10000, 1000},{-1000, 10000, 1000},{-1000, 9000, 1000} };

Object3D pillarObj;

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
	//Floor
	

	//Lines
}

void drawPillar()
{
	printf("walls\n");
	ReadOBJfile("data/3D Objects/Pillar.obj", &pillarObj);
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
	}
}

///draws and displays pillars in a wall structure
void displayWalls(bool neg)
{
	//wall on X axis
	if (!neg) {
		for (int i = 1; i <= level1Map.GetX() + 1; ++i)
		{
			glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CobbleWall));
			glTranslatef(-2 * i, 0, 0);
			draw3DObject(pillarObj);
			glPopMatrix();
		}
		//Walls on Y axis (z-axis 2D)
		for (int i = 1; i < level1Map.GetZ() + 1; ++i)
		{
			glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CobbleWall));
			glTranslatef(0, 0, -2 * i);
			glTranslatef(-2, 0, 0);
			draw3DObject(pillarObj);
			glPopMatrix();
		}
	}
	else {
		for (int i = 1; i <= level1Map.GetX() + 1; ++i)
		{
			glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CobbleWall));
			glTranslatef(2 * i, 0, 0);
			draw3DObject(pillarObj);
			glPopMatrix();
		}
		//Walls on Y axis (z-axis 2D)
		for (int i = 1; i < level1Map.GetZ() + 1; ++i)
		{
			glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CobbleWall));
			glTranslatef(0, 0, 2 * i);
			glTranslatef(2, 0, 0);
			draw3DObject(pillarObj);
			glPopMatrix();
		}
	}
}

///display the generated level map, uses set map X & Y value for size (length, width)
void displayMap()
{
	glPushMatrix();
		glTranslatef(720, 9000, 640);
		glScalef(80, 80, 80);
		displayWalls(false);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-720, 9000, -640);
		glScalef(80, 80, 80);
		displayWalls(true);
	glPopMatrix();

	//Floor
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(gameFloor[0][0], gameFloor[0][1], gameFloor[0][2]);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(gameFloor[1][0], gameFloor[1][1], gameFloor[1][2]);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(gameFloor[2][0], gameFloor[2][1], gameFloor[2][2]);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(gameFloor[3][0], gameFloor[3][1], gameFloor[3][2]);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-460, 9000, -550);
	drawLines();
	glPopMatrix();
}

void drawLines()
{
	int size = gridSquareSize;
	glColor3f(1, 1, 1);
	glLineWidth(25);
	//x lines
	for (int i = 0; i < level1Map.GetX(); ++i) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(1500, 0, (size * i));
		glVertex3f(0, 0, (size * i));
		glEnd();
	}
	//y lines
	for (int i = 0; i < level1Map.GetZ(); ++i) {
		glBegin(GL_LINE_LOOP);
		glVertex3f((size * i), 0, 1500);
		glVertex3f((size * i), 0, 0);
		glEnd();
	}
}

void CreateMaps()
{
	//level 1 Map
	for (int a = 0; a < level1Map.GetX(); a++)
	{
		for (int b = 0; b < level1Map.GetZ(); b++)
		{
			level1Map.SetValue(a, b, 0);
		}
	}

	fstream mapFile("data/Levels/maps.csv");
	string tmp;
	int tempLevel;
	int tempX;
	int tempZ;
	int tempInput;
	string tempString;
	if (!mapFile)
	{
		cout << "Error" << endl;
		return;
	}
	while (!mapFile.eof())
	{
		getline(mapFile, tmp);
		stringstream element(tmp);
		getline(element, tempString, ',');
		istringstream(tempString) >> tempLevel;
		getline(element, tempString, ',');
		istringstream(tempString) >> tempX;
		getline(element, tempString);
		istringstream(tempString) >> tempZ;

		tempLevelMap = new LevelMap(tempX, tempZ);
		//if level not found
		if (mapList.find(tempLevel) == mapList.end())
		{
			//add level to map
			vector<LevelMap> presetLMV;
			mapList[tempLevel] = presetLMV;
		}
		
		for (int i = 0; i < tempZ; i++)
		{
			getline(mapFile, tmp);
			stringstream element(tmp);
			for (int j = 0; j < tempX - 1; j++)
			{
				getline(element, tempString, ',');
				istringstream(tempString) >> tempInput;
				tempLevelMap->SetValue(i, j, tempInput);
			}
			getline(element, tempString);
			istringstream(tempString) >> tempInput;
			tempLevelMap->SetValue(i, tempX - 1, tempInput);
		}

		mapList[tempLevel].push_back(*tempLevelMap);
	}

	mapFile.close();
}