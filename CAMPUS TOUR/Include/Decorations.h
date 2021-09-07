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

#endif // !DECORATIONS_H

