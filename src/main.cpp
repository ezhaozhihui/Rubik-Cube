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

void onKeyboard(unsigned char key, int x, int y)
{
    x = y;
    switch (key) {
    case '1':
        g_Rubik->updateCube(0);
        glutPostRedisplay();
        break;
    case '2':
        g_Rubik->updateCube(1);
        glutPostRedisplay();
        break;
    case '3':
        g_Rubik->updateCube(2);
        glutPostRedisplay();
        break;
    case '4':
        g_Rubik->updateCube(3);
        glutPostRedisplay();
        break;
    case '5':
        g_Rubik->updateCube(4);
        glutPostRedisplay();
        break;
    case '6':
        g_Rubik->updateCube(5);
        glutPostRedisplay();
        break;
    case '7':
        g_Rubik->updateCube(6);
        glutPostRedisplay();
        break;
    case '8':
        g_Rubik->updateCube(7);
        glutPostRedisplay();
        break;
    case '9':
        g_Rubik->updateCube(8);
        glutPostRedisplay();
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

