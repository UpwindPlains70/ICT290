#include "LevelHandler.h"

Point4 camPos = { -43.0, 10000, -987.68, 180.0 };

GLdouble currXPos;
GLdouble currYPos;
GLdouble currZPos;

LevelMap *tempLevelMap = nullptr;
map<int, vector<LevelMap>> mapList;
Object3D pillarObj;
Object3D floorObj;

const int wallScale = 80;
const int floorScale = 75;

int floorValX;
int floorValZ;

int currLevel = 0;
int mapID = 0;
bool firstTime = true;

float posOffset = 2.08;

void teleportToSpawn()
{
	cam.Position(32720.0, 10500.0, 37000.0, 90.0);
	//cam.lookatUD(0);
}

void teleportCamera()
{
	//Change background colour to black
	//glClearColor(0.1, 0.1, 0.1, 1.0);

	//change camera position
	cam.Position(camPos[0], camPos[1], camPos[2], camPos[3]);

	//change vertical rotation of camera
	cam.lookatUD(-45);
}

///UPDATE: make general function for new level
bool levelZeroClear()
{
	cam.getPosition(currXPos, currYPos, currZPos);

	if (currYPos < 9000.0)
	{
		//firstTime = false;
		++currLevel;
		teleportCamera();
		return true;
	}
	return false;
}

void drawLevelObjects()
{
	ReadOBJfile("data/3D Objects/DungeonPillar.obj", &pillarObj);
	ReadOBJfile("data/3D Objects/DungeonFloor.obj", &floorObj);
}
///draws and displays pillars in a wall structure
void displayWalls(bool neg)
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DungeonPillar));
	//wall on X axis
	if (!neg) {
		for (int i = 1; i <= mapList[currLevel].at(mapID).GetX() + 1; ++i)
		{
			glPushMatrix();
			glTranslatef(-2 * i, 0, 0);
			draw3DObject(pillarObj);
			glPopMatrix();
		}
		//Walls on Z axis
		for (int i = 1; i <= mapList[currLevel].at(mapID).GetZ() + 1; ++i)
		{
			glPushMatrix();
			glTranslatef(0, 0, -2 * i);
			glTranslatef(-2, 0, 0);
			draw3DObject(pillarObj);
			glPopMatrix();
		}
	}
	else {
		for (int i = 1; i <= mapList[currLevel].at(mapID).GetX() + 1; ++i)
		{
			glPushMatrix();
			glTranslatef(2 * i, 0, 0);
			draw3DObject(pillarObj);
			glPopMatrix();
		}
		//Walls on Z axis
		for (int i = 1; i <= mapList[currLevel].at(mapID).GetZ() + 1; ++i)
		{
			glPushMatrix();
			glTranslatef(0, 0, 2 * i);
			glTranslatef(2, 0, 0);
			draw3DObject(pillarObj);
			glPopMatrix();
		}
	}
}

void displayFloor()
{
	int mapVal;
	for (int x = 0; x < mapList[currLevel].at(mapID).GetX(); ++x)
	{
		for (int z = 0; z < mapList[currLevel].at(mapID).GetZ(); ++z)
		{
			mapVal = mapList[currLevel].at(mapID).GetValue(x, z);

			glPushMatrix();
				glTranslatef(2.1 * x, 0, 2.1 * z);
					//empty floor space
				if (mapVal == 0)
				{
					glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DungeonFloor));				
					draw3DObject(floorObj);
				}//pillar space (val == 1)
				else
				{
					glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DungeonPillar));
					draw3DObject(pillarObj);
				}
			glPopMatrix();
		}
	}
}

///display the generated level map, uses set map X & Y value for size (length, width)
void displayMap()
{
	//NOTE: move to level load function, the function is only called when a level is finished i.e all enemies defeated
	//LIMIT: scale must not change (walls do not form rectangle)
	int repeatX = mapList[currLevel].at(mapID).GetX();
	int repeatZ = mapList[currLevel].at(mapID).GetZ();

	int wallValX = 114.28 * repeatX;
	int wallValZ = 91.42 * repeatZ;
	floorValX = 67.14 * repeatX;
	floorValZ = 67.14 * repeatZ;

		//Math for non 7x7 maps
	if (repeatX != 7)
		wallValX -= wallValX % wallScale;
	if(repeatZ != 7)
		wallValZ -= wallValZ % wallScale;

	if (repeatX != 7 || repeatZ != 7) {
		int floorRemZ = floorValX % floorScale;
		floorValX -= floorValX % floorScale;
		floorValZ -= floorRemZ;

		//Math for less rows than columns
		if (repeatX < repeatZ) {
			if (repeatX < 7)
				wallValX += wallScale;

			floorValX += (floorValX / floorScale * 0.3) * 10;
			floorValZ += (floorValZ / floorScale * 0.75) * 10;
		}
		else {
			if (repeatX < 7)
				wallValZ += wallScale;
			if (repeatZ > 7)
			{
				if(repeatX < 12)
					wallValX -= wallScale;
				else 
					wallValX -= wallScale * 2;

				floorValX += (floorValX / floorScale) * 13;
				floorValZ += (floorValZ / floorScale) * 15;
			}
			else {
				wallValX -= wallScale * 2;

				if (repeatZ != 7) {
					floorValZ -= (floorValZ / floorScale) * 5;
					floorValX += (floorValX / floorScale) * 3;
				}
				else
					floorValZ += (floorValZ / floorScale) * 7;
			}
		}
	}

	glPushMatrix();
		//glTranslatef(800, 9000, 640);
		glTranslatef(wallValX, 9000, wallValZ);
		glScalef(wallScale, wallScale, wallScale);
		displayWalls(false);
	glPopMatrix();
	glPushMatrix();
		//glTranslatef(-800, 9000, -640);
		glTranslatef(-wallValX, 9000, -wallValZ);
		glScalef(wallScale, wallScale, wallScale);
		displayWalls(true);
	glPopMatrix();

	//floor
	/*glPushMatrix();
		glTranslatef(-floorValX, 9000, -floorValZ);
		glScalef(floorScale, floorScale, floorScale);
		displayFloor();
	glPopMatrix();*/
}

void positionFloorObjects(vector<Enemy> nowEnemies, vector<Player> playerList)
{
	//Floor
	glPushMatrix();
		glTranslatef(-floorValX, 9000, -floorValZ);
		glScalef(floorScale, floorScale, floorScale);
		displayFloor();
		displayCharacterModels(nowEnemies, playerList);
	glPopMatrix();
}

void displayCharacterModels(vector<Enemy> nowEnemies, vector<Player> playerList) {
	if (playerList.size() > 0) {
		for (int i = 0; i < playerList.size(); i++) {
			//cout << "Player X: " << playerList[i].getPosX() << " Z: " << playerList[i].getPosZ() << endl;
			playerEffects(playerList[i]);
			if(playerList[i].getClassName() == "God")
				DisplayPlayerModel("Monk", playerList[i].getPosX() * posOffset, 0, playerList[i].getPosZ() * posOffset);
			else
				DisplayPlayerModel(playerList[i].getClassName(), playerList[i].getPosX() * posOffset, 0, playerList[i].getPosZ() * posOffset);
		}
	}
	if (nowEnemies.size() > 0) {
		for (int i = 0; i < nowEnemies.size(); i++) {
			//cout << "Name: " << nowEnemies[i].getName() << "  Eneemy X: " << nowEnemies[i].getPosX() << " Z: " << nowEnemies[i].getPosZ() << endl;
			enemyEffects(nowEnemies[i]);
			DisplayPlayerModel(nowEnemies[i].getName(), nowEnemies[i].getPosX() * posOffset, 0, nowEnemies[i].getPosZ() * posOffset);
		}
	}
}

void CreateMaps()
{
	fstream mapFile("data/Levels/maps.csv");
	string tmp;
	int tempLevel;
	int tempX;
	int tempZ;
	int tempInput;
	string tempString;
	if (!mapFile)
	{
		cout << "Error: loading level maps" << endl;
		return;
	}
	int out = 0;
	while (!mapFile.eof())
	{
		getline(mapFile, tmp);
		stringstream element(tmp);
		getline(element, tempString, ',');
		istringstream(tempString) >> tempLevel;
		getline(element, tempString, ',');
		istringstream(tempString) >> tempZ;
		getline(element, tempString);
		istringstream(tempString) >> tempX;

		tempLevelMap = new LevelMap(tempX, tempZ);
		//if level not found
		if (mapList.find(tempLevel) == mapList.end())
		{
			//add level to map
			vector<LevelMap> presetLMV;
			mapList[tempLevel] = presetLMV;
		}

		for (int i = 0; i < tempLevelMap->GetX(); i++)
		{
			getline(mapFile, tmp);
			stringstream element(tmp);
			for (int j = 0; j < tempLevelMap->GetZ(); j++)
			{
				getline(element, tempString, ',');
				istringstream(tempString) >> tempInput;
				tempLevelMap->SetValue(i, j, tempInput);
			}
		}
		mapList[tempLevel].push_back(*tempLevelMap);
	}
	mapFile.close();
		//Tesing only (ensure no level zero (0) exists
	/*if (mapList.find(0) == mapList.end())
		cout << "GOOOOOOOD\n";
	else
		cout << "BADDDD\n";*/
}