#pragma once

namespace M::MMath
{
    struct Vector3
    {
        float x, y, z;

        constexpr Vector3() : Vector3(0.0f) {}
        explicit constexpr Vector3(float n) noexcept : Vector3(n, n, n) {}
        constexpr Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

        const static Vector3 Zero;
        const static Vector3 One;
        const static Vector3 XAxis;
        const static Vector3 YAxis;
        const static Vector3 ZAxis;

        constexpr Vector3 operator-() { return Vector3(-x, -y, -z); }

        constexpr Vector3 operator+(const Vector3& rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.y); }
        constexpr Vector3 operator-(const Vector3& rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
        constexpr Vector3 operator*(const Vector3& rhs) const { return Vector3(x * rhs.x, y * rhs.y, z * rhs.z); }
        constexpr Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
        constexpr Vector3 operator/(float s) const { return Vector3(x / s, y / s, z / s); }

        Vector3& operator +=(const Vector3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
        Vector3& operator -=(const Vector3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
        Vector3& operator *=(const Vector3& rhs) { x *= rhs.x; y *= rhs.y; z *= rhs.z; return *this; }
        Vector3& operator *=(float s) { x *= s; y *= s; z *= s; return *this; }
        Vector3& operator /=(float s) { x /= s; y /= s; z /= s; return *this; }
    };
}