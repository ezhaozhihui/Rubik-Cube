/*
 * =====================================================================================
 *
 *       Filename:  Cube.cpp
 *
 *    Description:  define Rubik's cube
 *
 *        Version:  1.0
 *        Created:  2015年09月10日 22时08分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhihui09@hotmail.com
 *
 * =====================================================================================
 */
#include "Cube.h"
#include <GL/glut.h>

static GLubyte color[][3] =
{
    {243, 0, 0},    // red
    {6, 250, 0},    // green
    {102, 105, 255},// blue
    {254, 255, 70}, // yellow
    {253, 98, 0},   // orange
    {255, 255, 255},// white
    {0, 0, 0},      // black
};

Cube::Cube()
{
    m_vertex[0][0] = 1; m_vertex[0][1] = 1; m_vertex[0][2] = 1;
    m_vertex[1][0] = 0; m_vertex[1][1] = 1; m_vertex[1][2] = 1;
    m_vertex[2][0] = 0; m_vertex[2][1] = 0; m_vertex[2][2] = 1;
    m_vertex[3][0] = 1; m_vertex[3][1] = 0; m_vertex[3][2] = 1;
    m_vertex[4][0] = 1; m_vertex[4][1] = 0; m_vertex[4][2] = 0;
    m_vertex[5][0] = 1; m_vertex[5][1] = 1; m_vertex[5][2] = 0;
    m_vertex[6][0] = 0; m_vertex[6][1] = 1; m_vertex[6][2] = 0;
    m_vertex[7][0] = 0; m_vertex[7][1] = 0; m_vertex[7][2] = 0;

    face_color[front]   = white;
    face_color[back]    = black;
    face_color[left]    = yellow;
    face_color[right]   = orange;
    face_color[top]     = green;
    face_color[bottom]  = blue;
}

void Cube::draw()
{
    glBegin(GL_TRIANGLES);

    // front face
    glColor3ubv(color[face_color[front]]);
    glNormal3f(0, 0, 1);
    glVertex3fv(m_vertex[0]);
    glVertex3fv(m_vertex[1]);
    glVertex3fv(m_vertex[2]);

    glColor3ubv(color[face_color[front]]);
    glNormal3f(0, 0, 1);
    glVertex3fv(m_vertex[2]);
    glVertex3fv(m_vertex[3]);
    glVertex3fv(m_vertex[0]);

    // right face
    glColor3ubv(color[face_color[right]]);
    glNormal3f(1, 0, 0);
    glVertex3fv(m_vertex[0]);
    glVertex3fv(m_vertex[3]);
    glVertex3fv(m_vertex[4]);

    glColor3ubv(color[face_color[right]]);
    glNormal3f(1, 0, 0);
    glVertex3fv(m_vertex[4]);
    glVertex3fv(m_vertex[5]);
    glVertex3fv(m_vertex[0]);

    // top face
    glColor3ubv(color[face_color[top]]);
    glNormal3f(0, 1, 0);
    glVertex3fv(m_vertex[0]);
    glVertex3fv(m_vertex[5]);
    glVertex3fv(m_vertex[6]);

    glColor3ubv(color[face_color[top]]);
    glNormal3f(0, 1, 0);
    glVertex3fv(m_vertex[6]);
    glVertex3fv(m_vertex[1]);
    glVertex3fv(m_vertex[0]);

    // back face
    glColor3ubv(color[face_color[back]]);
    glNormal3f(0, 0, -1);
    glVertex3fv(m_vertex[5]);
    glVertex3fv(m_vertex[4]);
    glVertex3fv(m_vertex[7]);

    glColor3ubv(color[face_color[back]]);
    glNormal3f(0, 0, -1);
    glVertex3fv(m_vertex[6]);
    glVertex3fv(m_vertex[5]);
    glVertex3fv(m_vertex[7]);

    // left face
    glColor3ubv(color[face_color[left]]);
    glNormal3f(-1, 0, 0);
    glVertex3fv(m_vertex[1]);
    glVertex3fv(m_vertex[7]);
    glVertex3fv(m_vertex[2]);

    glNormal3f(-1, 0, 0);
    glColor3ubv(color[face_color[left]]);
    glVertex3fv(m_vertex[1]);
    glVertex3fv(m_vertex[1]);
    glVertex3fv(m_vertex[6]);
    glVertex3fv(m_vertex[7]);

    // bottom face
    glColor3ubv(color[face_color[bottom]]);
    glNormal3f(0, -1, 0);
    glVertex3fv(m_vertex[3]);
    glVertex3fv(m_vertex[2]);
    glVertex3fv(m_vertex[7]);

    glColor3ubv(color[face_color[bottom]]);
    glNormal3f(0, -1, 0);
    glVertex3fv(m_vertex[4]);
    glVertex3fv(m_vertex[3]);
    glVertex3fv(m_vertex[7]);

    glEnd();
}

void Cube::translate(float dx, float dy, float dz)
{
    for (int i = 0; i < 8; i++)
    {
        m_vertex[i][0] += dx;
        m_vertex[i][1] += dy;
        m_vertex[i][2] += dz;
    }
}
