#include <iostream>
#include <string.h>
#include <GL/glut.h>
#include "Cube.h"


static Cube *g_cube = NULL;


void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-5, 5, -5, 5, 0.1, 15);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(5, 5, 10, 0, 0, 0, 0, 1, 0);

    return;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);
    g_cube->draw();
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(400, 300);
    glutCreateWindow("An Example OpenGL Program");

    Cube *cube = new Cube();
    g_cube = cube;

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

