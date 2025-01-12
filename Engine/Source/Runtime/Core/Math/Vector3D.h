#pragma once
#include <cmath>

class Vector3D
{
public:
    double x;
    double y;
    double z;

    Vector3D() : x(0.0), y(0.0), z(0.0) {}
    Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

    // Addition operator
    Vector3D operator+(const Vector3D& other) const
    {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    // Subtraction operator
    Vector3D operator-(const Vector3D& other) const
    {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    // Scalar multiplication
    Vector3D operator*(double scalar) const
    {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    // Scalar division
    Vector3D operator/(double scalar) const
    {
        return Vector3D(x / scalar, y / scalar, z / scalar);
    }

    // Assignment operator for addition
    Vector3D& operator+=(const Vector3D& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    // Assignment operator for subtraction
    Vector3D& operator-=(const Vector3D& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    // Magnitude of the vector
    double magnitude() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Normalize the vector
    Vector3D normalize() const
    {
        double mag = magnitude();
        if (mag == 0)
            return Vector3D(0.0, 0.0, 0.0);
        return Vector3D(x / mag, y / mag, z / mag);
    }

    // Dot product
    double dotProduct(const Vector3D& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    // Cross product
    Vector3D crossProduct(const Vector3D& other) const
    {
        return Vector3D(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }
};