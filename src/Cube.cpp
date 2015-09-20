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

// after COUNT_MAX_NUM rotations with rotation_step degree each time, update subcube indices
const int   rotation_step = 5;
const float DEG2RAD = 3.141592653f / 180;
const float DELTA_ANGLE = rotation_step * DEG2RAD;
const int   COUNT_MAX_NUM = 90 / rotation_step;

static int count = 0;

static GLubyte color[][3] =
{
    {243 , 0   , 0}   , // red
    {6   , 250 , 0}   , // green
    {102 , 105 , 255} , // blue
    {254 , 255 , 70}  , // yellow
    {253 , 98  , 0}   , // orange
    {255 , 255 , 255} , // white
    {50  , 50  , 50}  , // black
};

static GridIndex circleIndex[] =
{
    {0, 0},
    {0, 1},
    {0, 2},
    {1, 2},
    {2, 2},
    {2, 1},
    {2, 0},
    {1, 0},
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

}

void RubikCube::draw()
{
    int x, y, z;
    for (x = 0; x < 3; x++)
        for (y = 0; y < 3; y++)
            for (z = 0; z < 3; z++)
                SubCube[x][y][z]->draw();
}

void RubikCube::transform(int axis)
{
    count++;
    Matrix3 mat;
    int x, y, z;
    switch (axis) {
    case 0:
    case 1:
    case 2:
        for (y = 0; y < 3; y++)
            for (z = 0; z < 3; z++)
                SubCube[axis][y][z]->multiMatrix(mat.Rotate(DELTA_ANGLE, axis/3));
        if (count == COUNT_MAX_NUM)
        {
            count = 0;
            updateCubeIndex(axis);
        }
        break;
    case 3:
    case 4:
    case 5:
        for (x = 0; x < 3; x++)
            for (z = 0; z < 3; z++)
                SubCube[x][axis%3][z]->multiMatrix(mat.Rotate(DELTA_ANGLE, axis/3));
        if (count == COUNT_MAX_NUM)
        {
            count = 0;
            updateCubeIndex(axis);
        }
        break;
    case 6:
    case 7:
    case 8:
        for (x = 0; x < 3; x++)
            for (y = 0; y < 3; y++)
                SubCube[x][y][axis%3]->multiMatrix(mat.Rotate(DELTA_ANGLE, axis/3));
        if (count == COUNT_MAX_NUM)
        {
            count = 0;
            updateCubeIndex(axis);
        }
        break;
    default:
        break;
    }
}

void RubikCube::updateCubeIndex(int axis)
{
    int i;
    Cube *tmp[8] = {0};
    if (axis == 0 || axis == 1 || axis == 2)
    {
        for (i = 0; i < 8; i++)
            tmp[i] = SubCube[axis%3][circleIndex[i].x1][circleIndex[i].x2];
        for (i = 0; i < 8; i++)
            SubCube[axis%3][circleIndex[i].x1][circleIndex[i].x2] = tmp[(i+2)%8];
    }
    else if (axis == 3 || axis == 4 || axis == 5)
    {
        for (i = 0; i < 8; i++)
            tmp[i] = SubCube[circleIndex[i].x2][axis%3][circleIndex[i].x1];
        for (i = 0; i < 8; i++)
            SubCube[circleIndex[i].x2][axis%3][circleIndex[i].x1] = tmp[(i+2)%8];
    }
    else if (axis == 6 || axis == 7 || axis == 8)
    {
        for (i = 0; i < 8; i++)
            tmp[i] = SubCube[circleIndex[i].x1][circleIndex[i].x2][axis%3];
        for (i = 0; i < 8; i++)
            SubCube[circleIndex[i].x1][circleIndex[i].x2][axis%3] = tmp[(i+2)%8];
    }
    else
    {
        ;
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

    setFaceColor(black, black, black, black, black, black);
}

void Cube::draw()
{
    glColor3ub(50, 50, 50);
    glBegin(GL_LINE_LOOP);
    glVertex3fv(m_vertex[0]);
    glVertex3fv(m_vertex[1]);
    glVertex3fv(m_vertex[2]);
    glVertex3fv(m_vertex[3]);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3fv(m_vertex[4]);
    glVertex3fv(m_vertex[5]);
    glVertex3fv(m_vertex[6]);
    glVertex3fv(m_vertex[7]);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3fv(m_vertex[1]);
    glVertex3fv(m_vertex[6]);
    glVertex3fv(m_vertex[7]);
    glVertex3fv(m_vertex[2]);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3fv(m_vertex[0]);
    glVertex3fv(m_vertex[3]);
    glVertex3fv(m_vertex[4]);
    glVertex3fv(m_vertex[5]);
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

void Cube::multiMatrix(Matrix3 &mat)
{
    float tmp0, tmp1, tmp2;
    // row-major matrix
    for (int i = 0; i < 8; i++)
    {
        tmp0 = m_vertex[i][0];
        tmp1 = m_vertex[i][1];
        tmp2 = m_vertex[i][2];
        m_vertex[i][0] = tmp0 * mat[0] + tmp1 * mat[1] + tmp2 * mat[2];
        m_vertex[i][1] = tmp0 * mat[3] + tmp1 * mat[4] + tmp2 * mat[5];
        m_vertex[i][2] = tmp0 * mat[6] + tmp1 * mat[7] + tmp2 * mat[8];
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

Color Cube::getFaceColor(Face face_name)
{
    return face_color[face_name];
}
