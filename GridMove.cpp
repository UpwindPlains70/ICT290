#include "GridMove.h"

//test grid
//draw grid 25x25
void drawGrid() {
    int size = moveSize;
    glColor3f(1, 0, 0);
    //x lines
    for (int i = 0; i < 100; i++) {
        glBegin(GL_LINE_LOOP);
        glVertex3f(50000, 0, (size * i));
        glVertex3f(0, 0, (size * i));
        glEnd();
    }
    //y lines
    for (int i = 0; i < 100; i++) {
        glBegin(GL_LINE_LOOP);
        glVertex3f((size * i), 0, 50000);
        glVertex3f((size * i), 0, 0);
        glEnd();
    }
}

//test dummy on 0,0 square
void drawDum() {
    glColor3f(0, 0, 0);
    glTranslatef(500, 500, 500);
    glutSolidCube(900);
    //glutSolidTeapot(500);
}

//call to move piece
void moveUp() {
    Dz -= moveSize;
}

void moveDown() {
    Dz += moveSize;
}

void moveLeft() {
    Dx -= moveSize;
}

void moveRight() {
    Dx += moveSize;
}