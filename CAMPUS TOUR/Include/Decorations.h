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



/**
* @brief This function reads the OBJ file and stores the vertices, normals, and textures.
* Store models into objects. Texture ID and model stored in the appropriate map structure.
*
*/
void ReadObjectModels(vector<string>& fileNames);


/**
 * @brief Display the player model
 * @param className
 * @param posX
 * @param posY
 * @param posZ
 * @param rot
 */
void DisplayPlayerModel(string className, int posX, int posY, int posZ, float rot);


void getFileNames(vector<string>& fileNames, ifstream& inFile);


/**
 * @brief Reads the object files and stores them in the vector of object models.
 */
void initPlayerModels();

/**
* @brief Draws the player effects.
* @param pc The player to see if they effects that need to be drawn.
*/
void playerEffects(Player &pc);

/**
* @brief Draws the enemy effects.
* @param ec The enemy to see if they effects that need to be drawn.
*/
void enemyEffects(Enemy &ec);


#endif // !DECORATIONS_H

