#ifndef DECORATIONS_H
#define DECORATIONS_H

/**
	 * @brief defines all functions for decoration generation
	 * i.e. draw/read objects, position generation, display objects & texture accordingly
	 *
	 * @author Peter Neve
	 * @version 01
	 * @date 6/09/2021, started
	 *
	 */

#include "TextureHandler.h"
#include "ReadOBJfile.h"
#include "Geometry.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
#include <time.h>

using std::vector;

extern vector<Object3D> decorationList;
extern vector<int> randXList;
extern vector<int> randZList;
extern vector<int> randScaleList;
extern vector<int> randIndexList;

void DrawDecorations();
void genDecorationsPositions();
int decorationTextureHelp(int index);
void DisplayDecorations();
extern Object3D portal;


//------- Drawing the players and the enemies ---------- // 

#include <iostream>
#include <map>
#include <string>
#include <cstring>


/**
	 * @brief defines all functions for reading, storing and displaying character model objects, 
	 * i.e. Display the characters, their effects and their textures 
	 *
	 * @author Jason Botterill
	 * @version 01
	 * @date 6/09/2021, started
	 *
	 */

//map<string, Object3D> characterModelMap;

extern map<string, Object3D> characterModelMap;
extern map<string, int> modelTextureMap;
extern bool displayCharacters;

void ReadObjectModels(vector<string>& fileNames);
void DisplayPlayerModel(string className, int posX, int posY, int posZ, float rot);
void getFileNames(vector<string>& fileNames, ifstream& inFile);
void initPlayerModels();
void playerEffects(Player &pc);
void enemyEffects(Enemy &ec);


#endif // !DECORATIONS_H

