#pragma once
#include <cstdio>

#include "Vector3D.h"

class Matrix4x4
{
public:
    double m[4][4];

    // Constructor to initialize the matrix to the identity matrix
    Matrix4x4()
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                m[i][j] = (i == j) ? 1.0 : 0.0;
    }

    // Constructor to initialize the matrix with specific values
    Matrix4x4(double values[4][4])
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                m[i][j] = values[i][j];
    }

    // Addition operator
    Matrix4x4 operator+(const Matrix4x4& other) const
    {
        Matrix4x4 result;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                result.m[i][j] = m[i][j] + other.m[i][j];
        return result;
    }

    // Subtraction operator
    Matrix4x4 operator-(const Matrix4x4& other) const
    {
        Matrix4x4 result;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                result.m[i][j] = m[i][j] - other.m[i][j];
        return result;
    }

    // Multiplication operator
    Matrix4x4 operator*(const Matrix4x4& other) const
    {
        Matrix4x4 result;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
            {
                result.m[i][j] = 0.0;
                for (int k = 0; k < 4; ++k)
                    result.m[i][j] += m[i][k] * other.m[k][j];
            }
        return result;
    }

    // Transpose the matrix
    Matrix4x4 transpose() const
    {
        Matrix4x4 result;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                result.m[i][j] = m[j][i];
        return result;
    }

    // Multiply the matrix by a vector
    Vector3D operator*(const Vector3D& vec) const
    {
        double x = m[0][0] * vec.x + m[0][1] * vec.y + m[0][2] * vec.z + m[0][3];
        double y = m[1][0] * vec.x + m[1][1] * vec.y + m[1][2] * vec.z + m[1][3];
        double z = m[2][0] * vec.x + m[2][1] * vec.y + m[2][2] * vec.z + m[2][3];
        return Vector3D(x, y, z);
    }

    // Print matrix (for debugging)
    void print() const
    {
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                printf("%f ", m[i][j]);
            }
            printf("\n");
        }
    }
};