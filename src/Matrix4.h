/*
 * =====================================================================================
 *
 *       Filename:  Matrix4.h
 *
 *    Description:  Matrix util for opengl
 *
 *        Version:  1.0
 *        Created:  2015年08月01日 14时01分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  etiennezhao
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef MATRIX4_H
#define MATRIX4_H

#include <iostream>

class Vector3
{
    friend class Matrix4;
public:
    Vector3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f);

    void        set(float x, float y, float z);
    float       length() const;
    void        normalize();
    Vector3     cross(const Vector3 &v) const;
    float       dot(const Vector3 &v) const;

    Vector3     operator+(const Vector3 &v) const;
    Vector3&    operator+=(const Vector3 &v);
    Vector3     operator-(const Vector3 &v) const;
    Vector3&    operator-=(const Vector3 &v);
    Vector3     operator*(const float scale) const;
    Vector3&    operator*=(const float scale);
    Vector3     operator*(const Vector3 &v) const;
    Vector3&    operator*=(const Vector3 &v);

    friend std::ostream& operator<<(std::ostream &os, const Vector3 &v);

private:
    float x, y, z;
};

class Vector4
{
    friend class Matrix4;
public:
    Vector4(float _x = 0.0, float _y = 0.0, float _z = 0.0, float w = 1.0);

private:
    float x, y, z, w;   
};

class Matrix4
{
public:
    Matrix4();
    Matrix4(const float src[16]);
    Matrix4(float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33);
    
    void        set(const float src[16]);
    void        set(float m00, float m01, float m02, float m03,
                    float m10, float m11, float m12, float m13,
                    float m20, float m21, float m22, float m23,
                    float m30, float m31, float m32, float m33);
    void        setRow(int index, const float row[4]);
    void        setRow(int index, const Vector4 &v);
    void        setRow(int index, const Vector3 &v);
    void        setColumn(int index, const float col[4]);
    void        setColumn(int index, const Vector4 &v);
    void        setColumn(int index, const Vector3 &v);

    const float* get() const;
    const float* getTranspose();
    float        getDeterminant();

    Matrix4&    identity();

    // transform matrix
    Matrix4&    translate(float x, float y, float z);
    Matrix4&    translate(const Vector3 &v);
    Matrix4&    rotate(float angle, const Vector3 &axis);
    Matrix4&    rotate(float angle, float x, float y, float z);
    Matrix4&    rotateX(float angle);
    Matrix4&    rotateY(float angle);
    Matrix4&    rotateZ(float angle);
    Matrix4&    scale(float s);
    Matrix4&    scale(float sx, float sy, float sz);

    Matrix4     operator+(const Matrix4 &mat) const;
    Matrix4&    operator+=(const Matrix4 &mat);
    Matrix4     operator-(const Matrix4 &mat) const;
    Matrix4&    operator-=(const Matrix4 &mat);
    Vector4     operator*(const Vector4 &vec) const;
    Vector3     operator*(const Vector3 &vec) const;
    Matrix4     operator*(const Matrix4 &mat) const;
    Matrix4&    operator*=(const Matrix4 &mat);
    float       operator[](int index) const;
    float&      operator[](int index);

private:
    float m[16];
    float tm[16];
};

class Matrix3
{
    friend std::ostream& operator<<(std::ostream &os, Matrix3 &mat);
public:
    Matrix3();
    Matrix3& Rotate(float angle, int axis);

    float   operator[](int index) const;

private:
    float m[9];
};
#endif
