#include "Decorations.h"

Object3D deadTreeObj;
Object3D brown_ShroomObj;
Object3D red_ShroomObj;
Object3D bushObj;
Object3D rockObj;
Object3D treeObj;
Object3D chainTreeObj;

vector<Object3D> decorationList;

int maxDecorations = 50;
vector<int> randXList;
vector<int> randZList;
vector<int> randIndexList;
vector<int> randScaleList;

/// Variables for displaying decorations
int scale;
int index;
void DrawDecorations()
{
	ReadOBJfile("data/3D Objects/Decorations/Dead_Tree.obj", &deadTreeObj);
	ReadOBJfile("data/3D Objects/Decorations/Red_Mushroom.obj", &red_ShroomObj);
	ReadOBJfile("data/3D Objects/Decorations/Brown_Mushroom.obj", &brown_ShroomObj);
	ReadOBJfile("data/3D Objects/Decorations/Bush.obj", &bushObj);
	ReadOBJfile("data/3D Objects/Decorations/Rock.obj", &rockObj);
	ReadOBJfile("data/3D Objects/Decorations/Tree.obj", &treeObj);
	ReadOBJfile("data/3D Objects/Decorations/Chained_Tree.obj", &chainTreeObj);

	decorationList.push_back(deadTreeObj);
	decorationList.push_back(red_ShroomObj);
	decorationList.push_back(brown_ShroomObj);
	decorationList.push_back(bushObj);
	decorationList.push_back(rockObj);
	decorationList.push_back(treeObj);
	decorationList.push_back(treeObj);//for dying tree texture
	decorationList.push_back(chainTreeObj);
}

//Future mod: limit no. of trees
void genDecorationsPositions()
{
	int xRand;
	int zRand;
	int index;
	int scale;
	srand(time(NULL));
	for (int i = 0; i < 50; ++i)
	{
		xRand = rand() % 24200 + 6431;
		zRand = rand() % 29000 + 10600;
		index = rand() % 8;
		scale = rand() % 300 + 100;

		if (index == 5)
			index += rand() % 1;

		randXList.push_back(xRand);
		randZList.push_back(zRand);
		randIndexList.push_back(index);
		randScaleList.push_back(scale);
		//printf("xRand = %d, zRand = %d, scale = %d, index = %d\n", xRand, zRand, scale, index);
	}
}

void DisplayDecorations()
{
	for (int i = 0; i < randIndexList.size(); ++i)
	{
		index = randIndexList.at(i);
		scale = randScaleList.at(i);
		glPushMatrix();
		glTranslatef(randXList.at(i), 10000.0, randZList.at(i));
		glScalef(scale, scale, scale);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(decorationTextureHelp(index)));
		draw3DObject(decorationList.at(index));
		glPopMatrix();
	}
}

int decorationTextureHelp(int index)
{
	switch (index)
	{
	case 0:
		return Dead_Tree;
	case 1:
		return Red_Mushroom;
	case 2:
		return Brown_Mushroom;
	case 3:
		return Bush;
	case 4:
		return Rock;
	case 5:
		return Tree;
	case 6:
		return Dying_Tree;
	case 7:
		return Chained_Tree;
	}
}