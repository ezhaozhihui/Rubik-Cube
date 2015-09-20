#include <iostream>
#include <string.h>
#include <GL/glut.h>
#include "Cube.h"


static RubikCube *g_Rubik = NULL;
static int g_rotation_count = 0;
static int g_Rubik_layer = 0;


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
    gluPerspective(45, (float)width/(float)height, 0.1, 100);
    //glOrtho(-5, 5, -5 * (float)height/(float)width, 5 * (float)height/(float)width, 0.1, 100);
    //glOrtho(-5, 5, -5, 5, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OnTimer(int value)
{
    g_rotation_count++;
    g_Rubik->transform(g_Rubik_layer);
    glutPostRedisplay();
    if (g_rotation_count < 18)
        glutTimerFunc(10, OnTimer, 1);
    else
        g_rotation_count = 0;
}

void onKeyboard(unsigned char key, int x, int y)
{
    x = y;
    switch (key) {
    case '1':
        g_Rubik_layer = 0;
        OnTimer(1);
        break;
    case '2':
        g_Rubik_layer = 1;
        OnTimer(1);
        break;
    case '3':
        g_Rubik_layer = 2;
        OnTimer(1);
        break;
    case '4':
        g_Rubik_layer = 3;
        OnTimer(1);
        break;
    case '5':
        g_Rubik_layer = 4;
        OnTimer(1);
        break;
    case '6':
        g_Rubik_layer = 5;
        OnTimer(1);
        break;
    case '7':
        g_Rubik_layer = 6;
        OnTimer(1);
        break;
    case '8':
        g_Rubik_layer = 7;
        OnTimer(1);
        break;
    case '9':
        g_Rubik_layer = 8;
        OnTimer(1);
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

    RubikCube *Rubik = new RubikCube();
    g_Rubik = Rubik;
    g_Rubik->init();

    init();
    glutDisplayFunc(display);
    //glutReshapeFunc(reshapeGLScene);
    glutKeyboardFunc(onKeyboard);
    glutMainLoop();

    return 0;
}

