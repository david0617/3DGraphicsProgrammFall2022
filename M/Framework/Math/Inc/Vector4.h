#pragma once

namespace M::MMath
{
    struct Vector4
    {
        float x, y, z, w;

        constexpr Vector4() : Vector4(0.0f) {}
        explicit constexpr Vector4(float n) noexcept : Vector4(n, n, n, n) {}
        constexpr Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

        const static Vector4 Zero;
        const static Vector4 One;
        const static Vector4 XAxis;
        const static Vector4 YAxis;
        const static Vector4 ZAxis;
        const static Vector4 WAxis;

        constexpr Vector4 operator-() { return Vector4(-x, -y, -z, -w); }

        constexpr Vector4 operator+(const Vector4& rhs) const { return Vector4(x + rhs.x, y + rhs.y, z + rhs.y, w + rhs.w); }
        constexpr Vector4 operator-(const Vector4& rhs) const { return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w); }
        constexpr Vector4 operator*(const Vector4& rhs) const { return Vector4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w); }
        constexpr Vector4 operator*(float s) const { return Vector4(x * s, y * s, z * s, w * s); }
        constexpr Vector4 operator/(float s) const { return Vector4(x / s, y / s, z / s, w / s); }

        Vector4& operator +=(const Vector4& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w; return *this; }
        Vector4& operator -=(const Vector4& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w; return *this; }
        Vector4& operator *=(const Vector4& rhs) { x *= rhs.x; y *= rhs.y; z *= rhs.z; w *= rhs.w; return *this; }
        Vector4& operator *=(float s) { x *= s; y *= s; z *= s; w *= s; return *this; }
        Vector4& operator /=(float s) { x /= s; y /= s; z /= s; w /= s; return *this; }
    };
}
