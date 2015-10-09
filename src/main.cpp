#include <iostream>
#include <string.h>
#include <ctime>
#include <cstdlib>
#include "Cube.h"


static RubikCube *g_Rubik = NULL;
static bool switch_on = false;


void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glPointSize(5);
    glLineWidth(3);

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_POINT_SMOOTH, GL_NICEST);
    glHint(GL_LINE_SMOOTH, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-5, 5, -5, 5, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(4, 4, 10, 0, 0, 0, 0, 1, 0);

    return;
}

void reshapeGLScene(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5, 5, -5*(float)height/(float)width, 5*(float)height/(float)width, 0.1, 100);
}

void OnTimer(int value)
{
    static int g_rotation_count;
    static int g_Rubik_layer = 0;
    static bool clockwise = true;
    g_rotation_count++;
    g_Rubik->transform(g_Rubik_layer, clockwise);
    glutPostRedisplay();
    if (g_rotation_count < 18)          // one complete layer rotation
        glutTimerFunc(10, OnTimer, 1);
    else                                // start another layer rotation
    {
        g_rotation_count = 0;
        g_Rubik_layer = rand() % 9;
        clockwise = rand() % 2;
        if (switch_on)
            glutTimerFunc(50, OnTimer, 1);
    }
}

void onKeyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'A':
        switch_on = true;
        OnTimer(1);
        break;
    case 'a':
        switch_on = false;
        break;
    case 27:
        exit(0);
    default:
        break;
    }
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
    glutCreateWindow("Rubik Cube");

    srand((int)time(0));

    RubikCube *Rubik = new RubikCube();
    g_Rubik = Rubik;
    g_Rubik->init();

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshapeGLScene);
    glutKeyboardFunc(onKeyboard);
    glutMainLoop();

    return 0;
}

