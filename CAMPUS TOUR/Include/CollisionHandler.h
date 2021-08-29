//Aurthor: Peter Neve
//Version: 1
//Date: 29/08/2021
//Purpose: defines wall collision for environment

#ifndef COLLISONHANDLER_H
#define COLLISONHANDLER_H

#include "camera.h"

//Objects
extern Camera cam;

// creates bounding boxes for collsion detection
void CreateBoundingBoxes();

#endif // COLLISONHANDLER_H
