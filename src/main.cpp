#include <iostream>
#include <string.h>
#include <GL/glut.h>
#include "Cube.h"


static RubikCube *g_Rubik = NULL;


void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-5, 5, -5, 5, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(3, 3, 10, 0, 0, 0, 0, 1, 0);

    return;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    g_Rubik->draw();
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("An Example OpenGL Program");

    RubikCube *Rubik = new RubikCube();
    g_Rubik = Rubik;
    g_Rubik->init();

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

