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

#include "Matrix4.h"

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

typedef struct GridIndex
{
    int x1;
    int x2;
} GridIndex;

class Cube
{
public:
    Cube();
    void translate(float dx, float dy, float dz);
    void multiMatrix(Matrix3 &mat);
    void setFaceColor(Color front_color,
                      Color back_color,
                      Color left_color,
                      Color right_color,
                      Color top_color,
                      Color bottom_color);
    void setFaceColor(Face face_name, Color color_name);
    Color getFaceColor(Face face_name);

    void draw();

private:
    float m_vertex[8][3];
    Color face_color[6];
};

class RubikCube
{
public:
    RubikCube();
    void init();
    void draw();
    void transform(int axis);

private:
    void updateCubeIndex(int axis);

    Cube *SubCube[3][3][3];
};
