/*
 * =====================================================================================
 *
 *       Filename:  Cube.h
 *
 *    Description:  Cube header
 *
 *        Version:  1.0
 *        Created:  2015年09月10日 22时06分03秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhihui09@hotmail.com
 *
 * =====================================================================================
 */

enum Color
{
    red,
    green,
    blue,
    yellow,
    orange,
    white,
    black,
};

enum Face
{
    front,
    back,
    left,
    right,
    top,
    bottom,
};

class Cube
{
public:
    Cube();
    void translate(float dx, float dy, float dz);
    void draw();

private:
    float m_vertex[8][3];
    Color face_color[6];
};

class RubikCube
{
public:
    RubikCube();

private:
    Cube SubCube[3][3];
};
