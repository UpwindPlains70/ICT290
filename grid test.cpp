#include <GL/glut.h>
#include <iostream>
#include "GridMove.h"

/*declare a point data type*/
static GLdouble viewer[] = { 10000, 10000, 10000, // initial camera location
                           2500, 0, 2500, // initial look at point
                           0.0, 1, 0.0  // initial  upvector
};

enum {
    ORTHO2D, PERSPECTIVE, FRUSTUM, ORTHO
} mode = PERSPECTIVE;

typedef GLfloat point3[3];

void myinit(void)
{

    /*attributes*/

    glClearColor(1.0, 1.0, 1.0, 1.0);  // draw on white background
    glColor3f(1.0, 0.0, 0.0);			// draw in red
    glLineWidth(5.0);				// draw line 5 px wide
    /*set up viewing*/
    /*500 x 500 pixel window with origin at lower left corner of display
    window*/
    glEnable(GL_DEPTH_TEST);

    /*switch matrix mode to 'projection' and load an identity matrix as the projection matrix*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    mode = PERSPECTIVE;

    /*set up orthographic projection in 2d with a clipping
    rectangle which has its lower left corner at the origin (0.0, 0.0)*/
    glMatrixMode(GL_PROJECTION);
    if (mode == PERSPECTIVE) {
        gluPerspective(60, 1, 0.1, 100000000.0);
    }
    else if (mode == ORTHO) {
        glOrtho(0.0, 500.0, 0.0, 500.0, 0.1, 100000000.0); //left, right, bottom, top, near, far
    }

}

void drawAxis() {
    point3 vertices[4] = {
        {0,0,0},{50000,0,0},{0,50000,0},{0,0,50000}
    };

    glBegin(GL_LINE_LOOP);
    glColor3f(1, 0, 0);
    glVertex3fv(vertices[0]);
    glVertex3fv(vertices[1]);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 1, 0);
    glVertex3fv(vertices[0]);
    glVertex3fv(vertices[2]);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 1);
    glVertex3fv(vertices[0]);
    glVertex3fv(vertices[3]);
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*switch matrix mode back to 'model view'*/
    glMatrixMode(GL_MODELVIEW);

    // Setting the camera location and viewewing volume
    glLoadIdentity();               // start with identity transformation
    gluLookAt(viewer[0], viewer[1], viewer[2],      // eye location
        viewer[3], viewer[4], viewer[5],      // looking at
        viewer[6], viewer[7], viewer[8]       // up vector
    );

    drawAxis();
    drawGrid();

    //initial position of 0,0
    glTranslatef(Dx, Dy, Dz);
    drawDum();

    glFlush(); //flushes buffers */
}

void keys(unsigned char key, int x, int y)
{
    //testDum 1025
    switch (key) {
    case('s'):
        moveDown();
        break;
    case('w'):
        moveUp();
        break;
    case('d'):
        moveRight();
        break;
    case('a'):
        moveLeft();
        break;
    case('j'):
        moveRight();
        moveRight();
        moveRight();
        moveDown();
        moveDown(); 
        moveDown();
        break;
    }
    //camera
    /* Use x, X, y, Y, z, and Z keys to move viewer */
    if (key == 'x') {
        viewer[0] -= 150;
    }
    if (key == 'X') {
        viewer[0] += 150;
    }
    if (key == 'y') viewer[1] -= 150;
    if (key == 'Y') viewer[1] += 150;
    if (key == 'z') viewer[2] -= 150;
    if (key == 'Z') viewer[2] += 150;

    if (key == 'Q') exit(0);
    if (key == 'q') exit(0);


    // Redisplay the window content
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    //Standard GLUT initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); //(GLUT_SINGLE|GLUT_RGB);


    glutInitWindowSize(2000, 2000); //500 * 500 pixel window
    glutInitWindowPosition(0, 0); //place window top left of display
    glutCreateWindow("Transformations pipeline"); //window title
    myinit(); //set attributes
    glutDisplayFunc(display); //display callback invoked when window is opened
    glutKeyboardFunc(keys); //keyboard response

    glutMainLoop(); //enter event loop

    return 0;

}