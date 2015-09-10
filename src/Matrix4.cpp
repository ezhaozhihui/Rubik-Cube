/*
 * =====================================================================================
 *
 *       Filename:  Matrix4.cpp
 *
 *    Description:  Matrix4 util for opengl
 *
 *        Version:  1.0
 *        Created:  2015年08月01日 14时04分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  etiennezhao
 *   Organization:  
 *
 * =====================================================================================
 */
#include "Matrix4.h"
#include <cmath>
#include <algorithm>

const float DEG2RAD = 3.141593f / 180;

Vector3::Vector3(float _x, float _y, float _z)
    : x(_x), y(_y), z(_z)
{

}

void Vector3::set(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
}

float Vector3::length() const
{
    return (float)sqrt(x * x + y * y + z * z);
}

void Vector3::normalize()
{
    float len = length();
    if (len > 1e-7)
    {
        x /= len;
        y /= len;
        z /= len;
    }
}

Vector3 Vector3::cross(const Vector3 &v) const
{
    return Vector3(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
}

float Vector3::dot(const Vector3 &v) const
{
    return x*v.x + y*v.y + z*v.z;
}

Vector3 Vector3::operator-(const Vector3 &v) const
{
    return Vector3(x-v.x, y-v.y, z-v.z);
}

Vector3& Vector3::operator-=(const Vector3 &v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vector3 Vector3::operator+(const Vector3 &v) const
{
    return Vector3(x+v.x, y+v.y, z+v.z);
}

Vector3& Vector3::operator+=(const Vector3 &v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector3 Vector3::operator*(const float scale) const
{
    return Vector3(x * scale, y * scale, z * scale);
}

Vector3& Vector3::operator*=(const float scale)
{
    x *= scale;
    y *= scale;
    z *= scale;
    return *this;
}

Vector3 Vector3::operator*(const Vector3 &v) const
{
    return Vector3(x * v.x, y * v.y, z * v.z);
}

Vector3& Vector3::operator*=(const Vector3 &v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

std::ostream& operator<<(std::ostream &os, const Vector3 &v)
{
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

Vector4::Vector4(float _x, float _y, float _z, float _w)
    : x(_x), y(_y), z(_z), w(_w)
{

}

Matrix4::Matrix4()
{
    identity();
}

Matrix4::Matrix4(const float src[16])
{
    set(src);
}

Matrix4::Matrix4(float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33)
{
    set(m00, m01, m02, m03,
        m10, m11, m12, m13,
        m20, m21, m22, m23,
        m30, m31, m32, m33);
}

void Matrix4::set(const float src[16])
{
    m[0]  = src[0];  m[1]  = src[1];  m[2]  = src[2];  m[3]  = src[3];
    m[4]  = src[4];  m[5]  = src[5];  m[6]  = src[6];  m[7]  = src[7];
    m[8]  = src[8];  m[9]  = src[9];  m[10] = src[10]; m[11] = src[11];
    m[12] = src[12]; m[13] = src[13]; m[14] = src[14]; m[15] = src[15];
}

void Matrix4::set(float m00, float m01, float m02, float m03,
                  float m10, float m11, float m12, float m13,
                  float m20, float m21, float m22, float m23,
                  float m30, float m31, float m32, float m33)
{
    m[0]  = m00; m[1]  = m01; m[2]  = m02; m[3]  = m03;
    m[4]  = m10; m[5]  = m11; m[6]  = m12; m[7]  = m13;
    m[8]  = m20; m[9]  = m21; m[10] = m22; m[11] = m23;
    m[12] = m30; m[13] = m31; m[14] = m32; m[15] = m33;
}

Matrix4& Matrix4::identity()
{
    m[0] = m[5] = m[10] = m[15] = 1.0f;
    m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.0f;
    return *this;
}

// M = T * M
// | 1  0  0  x | | m0  m1  m2  m3 |
// | 0  1  0  y | | m4  m5  m6  m7 |
// | 0  0  1  z | | m8  m9  m10 m11|
// | 0  0  0  1 | | m12 m13 m14 m15|
Matrix4& Matrix4::translate(float x, float y, float z)
{
    m[0]  += m[12] * x; m[1] += m[13] * x; m[2] += m[14] * x; m[3] += m[15] * x;
    m[4]  += m[12] * y; m[5] += m[13] * y; m[6] += m[14] * y; m[7] += m[15] * y;
    m[8]  += m[12] * z; m[9] += m[13] * z; m[10]+= m[14] * z; m[11]+= m[15] * z;
    return *this;
}

Matrix4& Matrix4::translate(const Vector3 &v)
{
    return translate(v.x, v.y, v.z);
}

Matrix4& Matrix4::rotate(float angle, const Vector3 &axis)
{
    return rotate(angle, axis.x, axis.y, axis.z);
}

Matrix4& Matrix4::rotate(float angle, float x, float y, float z)
{
    float c = cosf(angle * DEG2RAD);
    float s = sinf(angle * DEG2RAD);
    float xx = x * x;
    float xy = x * y;
    float xz = x * z;
    float yy = y * y;
    float yz = y * z;
    float zz = z * z;

    Matrix4 mat;
    mat[0]  = xx * (1 - c) + c;
    mat[1]  = xy * (1 - c) - z * s;
    mat[2]  = xz * (1 - c) + y * s;
    mat[3]  = 0;
    mat[4]  = xy * (1 - c) + z * s;
    mat[5]  = yy * (1 - c) + c;
    mat[6]  = yz * (1 - c) - x * s;
    mat[7]  = 0;
    mat[8]  = xz * (1 - c) - y * s;
    mat[9]  = yz * (1 - c) + x * s;
    mat[10] = zz * (1 - c) + c;
    mat[11] = 0;
    mat[12] = 0;
    mat[13] = 0;
    mat[14] = 0;
    mat[15] = 1;

    *this = mat * (*this);

    return *this;
}

Matrix4& Matrix4::rotateX(float angle)
{
    float c = cosf(angle * DEG2RAD);
    float s = sinf(angle * DEG2RAD);
    float m4 = m[4], m5 = m[5], m6 = m[6], m7 = m[7],
          m8 = m[8], m9 = m[9], m10 = m[10], m11 = m[11];

    m[4]  = m4 * c + m8  * -s;
    m[5]  = m5 * c + m9  * -s;
    m[6]  = m6 * c + m10 * -s;
    m[7]  = m7 * c + m11 * -s;
    m[8]  = m4 * s + m8  * c;
    m[9]  = m5 * s + m9  * c;
    m[10] = m6 * s + m10 * c;
    m[11] = m7 * s + m11 * c;

    return *this;
}

Matrix4& Matrix4::rotateY(float angle)
{
    float c = cosf(angle * DEG2RAD);
    float s = sinf(angle * DEG2RAD);
    float m0 = m[0], m1 = m[1], m2 = m[2],  m3 = m[3],
          m8 = m[8], m9 = m[9], m10= m[10], m11= m[11];

    m[0] = m0 * c + m8 * s;
    m[1] = m1 * c + m9 * s;
    m[2] = m2 * c + m10* s;
    m[3] = m3 * c + m11* s;
    m[8] = m0 *-s + m8 * c;
    m[9] = m1 *-s + m9 * c;
    m[10]= m2 *-s + m10* c;
    m[11]= m3 *-s + m11* c;

    return *this;
}

Matrix4& Matrix4::rotateZ(float angle)
{
    float c = cosf(angle * DEG2RAD);
    float s = sinf(angle * DEG2RAD);
    float m0 = m[0], m1 = m[1], m2 = m[2],  m3 = m[3],
          m4 = m[4], m5 = m[5], m6 = m[6],  m7 = m[7];

    m[0] = m0 * c + m4 *-s;
    m[1] = m1 * c + m5 *-s;
    m[2] = m2 * c + m6 *-s;
    m[3] = m3 * c + m7 *-s;
    m[4] = m0 * s + m4 * c;
    m[5] = m1 * s + m5 * c;
    m[6] = m2 * s + m6 * c;
    m[7] = m3 * s + m7 * c;

    return *this;
}

Matrix4& Matrix4::scale(float s)
{
    return scale(s, s, s);
}

Matrix4& Matrix4::scale(float sx, float sy, float sz)
{
    m[0] = m[0]*sx;   m[1] = m[1]*sx;   m[2] = m[2]*sx;   m[3] = m[3]*sx;
    m[4] = m[4]*sy;   m[5] = m[5]*sy;   m[6] = m[6]*sy;   m[7] = m[7]*sy;
    m[8] = m[8]*sz;   m[9] = m[9]*sz;   m[10]= m[10]*sz;  m[11]= m[11]*sz;

    return *this;
}

Matrix4 Matrix4::operator+(const Matrix4 &mat) const
{
    return Matrix4(m[0]   + mat[0], m[1]   + mat[1], m[2]   + mat[2], m[3]   + mat[3],
                    m[4]  + mat[4], m[5]   + mat[5], m[6]   + mat[6], m[7]   + mat[7],
                    m[8]  + mat[8], m[9]   + mat[9], m[10]  + mat[10], m[11] + mat[11],
                    m[12] + mat[12], m[13] + mat[13], m[14] + mat[14], m[15] + mat[15]);
}

Matrix4& Matrix4::operator+=(const Matrix4 &mat)
{
    m[0] += mat[0];
    m[1] += mat[1];
    m[2] += mat[2];
    m[3] += mat[3];
    m[4] += mat[4];
    m[5] += mat[5];
    m[6] += mat[6];
    m[7] += mat[7];
    m[8] += mat[8];
    m[9] += mat[9];
    m[10] += mat[10];
    m[11] += mat[11];
    m[12] += mat[12];
    m[13] += mat[13];
    m[14] += mat[14];
    m[15] += mat[15];

    return *this;
}

Vector4 Matrix4::operator*(const Vector4 &vec) const
{
    return Vector4(m[0]*vec.x + m[1]*vec.y + m[2]*vec.z + m[3]*vec.w,
                    m[4]*vec.x + m[5]*vec.y + m[6]*vec.z + m[7]*vec.w,
                    m[8]*vec.x + m[9]*vec.y + m[10]*vec.z + m[11]*vec.w,
                    m[12]*vec.x + m[13]*vec.y + m[14]*vec.z + m[15]*vec.w);
}

Vector3 Matrix4::operator*(const Vector3 &vec) const
{
    return Vector3(m[0]*vec.x + m[1]*vec.y + m[2]*vec.z,
                    m[4]*vec.x + m[5]*vec.y + m[6]*vec.z,
                    m[8]*vec.x + m[9]*vec.y + m[10]*vec.z);
}

Matrix4 Matrix4::operator*(const Matrix4 &mat) const
{
    return Matrix4(m[0]*mat[0] + m[1]*mat[4]  + m[2]*mat[8]   + m[3]*mat[12],
                  m[0]*mat[1]  + m[1]*mat[5]  + m[2]*mat[9]   + m[3]*mat[13],
                  m[0]*mat[2]  + m[1]*mat[6]  + m[2]*mat[10]  + m[3]*mat[14],
                  m[0]*mat[3]  + m[1]*mat[7]  + m[2]*mat[11]  + m[3]*mat[15],
                  m[4]*mat[0]  + m[5]*mat[4]  + m[6]*mat[8]   + m[7]*mat[12],
                  m[4]*mat[1]  + m[5]*mat[5]  + m[6]*mat[9]   + m[7]*mat[13],
                  m[4]*mat[2]  + m[5]*mat[6]  + m[6]*mat[10]  + m[7]*mat[14],
                  m[4]*mat[3]  + m[5]*mat[7]  + m[6]*mat[11]  + m[7]*mat[15],
                  m[8]*mat[0]  + m[9]*mat[4]  + m[10]*mat[8]  + m[11]*mat[12],
                  m[8]*mat[1]  + m[9]*mat[5]  + m[10]*mat[9]  + m[11]*mat[13],
                  m[8]*mat[2]  + m[9]*mat[6]  + m[10]*mat[10] + m[11]*mat[14],
                  m[8]*mat[3]  + m[9]*mat[7]  + m[10]*mat[11] + m[11]*mat[15],
                  m[12]*mat[0] + m[13]*mat[4] + m[14]*mat[8]  + m[15]*mat[12],
                  m[12]*mat[1] + m[13]*mat[5] + m[14]*mat[9]  + m[15]*mat[13],
                  m[12]*mat[2] + m[13]*mat[6] + m[14]*mat[10] + m[15]*mat[14],
                  m[12]*mat[3] + m[13]*mat[7] + m[14]*mat[11] + m[15]*mat[15]);
}

Matrix4& Matrix4::operator*=(const Matrix4 &mat)
{
    *this = *this * mat;
    return *this;
}

float Matrix4::operator[](int index) const
{
    return m[index];
}

float& Matrix4::operator[](int index)
{
    return m[index];
}
