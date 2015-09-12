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

RubikCube::RubikCube()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                SubCube[i][j][k] = new Cube();

}

void RubikCube::init()
{
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 3; y++)
            for (int z = 0; z < 3; z++)
                SubCube[x][y][z]->translate(x - 1.5f, y - 1.5f, z - 1.5f);

    int i, j;

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
        {
            SubCube[i][j][2]->setFaceColor(front, white);
            SubCube[i][j][0]->setFaceColor(back, green);
        }

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
        {
            SubCube[0][i][j]->setFaceColor(left, yellow);
            SubCube[2][i][j]->setFaceColor(right, orange);
        }

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
        {
            SubCube[i][0][j]->setFaceColor(bottom, blue);
            SubCube[i][2][j]->setFaceColor(top, red);
        }

    theta_x = 0;
    theta_y = 0;
    theta_z = 0;
}

void RubikCube::draw()
{
    int type = 0;
    switch (type) {
    case 0:
    case 1:
    case 2:
        glPushMatrix();
        glRotatef(theta_x, 1, 0, 0);
        for (int y = 0; y < 3; y++)
            for (int z = 0; z < 3; z++)
                SubCube[type][y][z]->draw();
        glPopMatrix();
        break;
    case 3:
    case 4:
    case 5:
        glPushMatrix();
        glRotatef(theta_y, 0, 1, 0);
        for (int x = 0; x < 3; x++)
            for (int z = 0; z < 3; z++)
                SubCube[x][type%3][z]->draw();
        glPopMatrix();
        break;
    case 6:
    case 7:
    case 8:
        glPushMatrix();
        glRotatef(theta_z, 0, 0, 1);
        for (int x = 0; x < 3; x++)
            for (int y = 0; y < 3; y++)
                SubCube[x][y][type%3]->draw();
        glPopMatrix();
        break;
    default:
        break;
    }

    for (int x = 0; x < 3; x++)
    {
        if (x == type)
            continue;
        for (int y = 0; y < 3; y++)
        {
            if (y + 3 == type)
                continue;
            for (int z = 0; z < 3; z++)
            {
                if (z + 6 == type)
                    continue;
                SubCube[x][y][z]->draw();
            }
        }
    }
}

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

    face_color[front]   = black; 
    face_color[back]    = black; 
    face_color[left]    = black; 
    face_color[right]   = black; 
    face_color[top]     = black; 
    face_color[bottom]  = black; 
}

void Cube::draw()
{
    glBegin(GL_LINE);
    glColor3ub(255, 0, 0);
    glLineWidth(3.0f);
    //glVertex3fv(m_vertex[0]);
    //glVertex3fv(m_vertex[1]);
    glVertex3f(2, 2, 2);
    glVertex3f(2, 0, 2);
    glEnd();


    glBegin(GL_QUADS);
    // front face
    glColor3ubv(color[face_color[front]]);
    //glNormal3f(0, 0, 1);
    glVertex3fv(m_vertex[0]);
    glVertex3fv(m_vertex[1]);
    glVertex3fv(m_vertex[2]);
    glVertex3fv(m_vertex[3]);

    // right face
    glColor3ubv(color[face_color[right]]);
    //glNormal3f(1, 0, 0);
    glVertex3fv(m_vertex[0]);
    glVertex3fv(m_vertex[3]);
    glVertex3fv(m_vertex[4]);
    glVertex3fv(m_vertex[5]);

    // top face
    glColor3ubv(color[face_color[top]]);
    //glNormal3f(0, 1, 0);
    glVertex3fv(m_vertex[0]);
    glVertex3fv(m_vertex[5]);
    glVertex3fv(m_vertex[6]);
    glVertex3fv(m_vertex[1]);

    // back face
    glColor3ubv(color[face_color[back]]);
    //glNormal3f(0, 0, -1);
    glVertex3fv(m_vertex[5]);
    glVertex3fv(m_vertex[4]);
    glVertex3fv(m_vertex[7]);
    glVertex3fv(m_vertex[6]);

    // left face
    glColor3ubv(color[face_color[left]]);
    //glNormal3f(-1, 0, 0);
    glVertex3fv(m_vertex[1]);
    glVertex3fv(m_vertex[6]);
    glVertex3fv(m_vertex[7]);
    glVertex3fv(m_vertex[2]);

    // bottom face
    glColor3ubv(color[face_color[bottom]]);
    //glNormal3f(0, -1, 0);
    glVertex3fv(m_vertex[3]);
    glVertex3fv(m_vertex[2]);
    glVertex3fv(m_vertex[7]);
    glVertex3fv(m_vertex[4]);

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

void Cube::setFaceColor(Color front_color,
                      Color back_color,
                      Color left_color,
                      Color right_color,
                      Color top_color,
                      Color bottom_color)
{
    face_color[front]  = front_color;
    face_color[back]   = back_color;
    face_color[left]   = left_color;
    face_color[right]  = right_color;
    face_color[top]    = top_color;
    face_color[bottom] = bottom_color;
}

void Cube::setFaceColor(Face face_name, Color color_name)
{
    face_color[face_name] = color_name;
}
