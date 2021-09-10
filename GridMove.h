#include <GL/glut.h>
#include <iostream>

//conceptual movement patterns based on the size of tiles/grid for movement
//size of grid + area to move 1
#define moveSize 1000;

//for testing
////presumes indivudual characters will have this
/*Weird bug here, program claims multiple declarations of dx, dy and dz from unknown sources
solved with DECLSPEC_SELECTANY
*/
DECLSPEC_SELECTANY GLfloat Dx = 0, Dy = 0, Dz = 0;

//testing for scale
////created assets should either be created with scale in mind or scaled during its creation
void drawGrid();
////add glTranslatef(Dx, Dy, Dz); above selected ofject to move it
void drawDum();

//movement [TEMP]
void moveUp();
void moveDown();
void moveLeft();
void moveRight();

//move to player|melee proximity
////check prox
////pathing?
////execution
