//Aurthor: Peter Neve
//Version: 1
//Date: 26/08/2021
//Reads .obj file with UV coordinates only

//Future update - allow for non UV .obj files


#ifndef READOFFfile_H
#define READOFFfile_H

#include "Geometry.h"

void ReadOBJfile(char* fileName, Object3D* newObject);
void setArrays(char* fileName, Object3D* newObject);
void reIndex(Object3D* obj);
void freeObj(Object3D* obj);
void printObjContent(Object3D* newObj);

int const bufferLength = 255;

#endif //READOFFfile_H
