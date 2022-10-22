#pragma once

namespace M::MMath
{
    struct Vector2
    {
        float x, y;

        constexpr Vector2() : Vector2(0.0f) {}
        explicit constexpr Vector2(float n) noexcept : Vector2(n, n) {}
        constexpr Vector2(float x, float y) : x(x), y(y){}

        const static Vector2 Zero;
        const static Vector2 One;
        const static Vector2 XAxis;
        const static Vector2 YAxis;

        constexpr Vector2 operator-() { return Vector2(-x, -y); }

        constexpr Vector2 operator+(const Vector2& rhs) const { return Vector2(x + rhs.x, y + rhs.y); }
        constexpr Vector2 operator-(const Vector2& rhs) const { return Vector2(x - rhs.x, y - rhs.y); }
        constexpr Vector2 operator*(const Vector2& rhs) const { return Vector2(x * rhs.x, y * rhs.y); }
        constexpr Vector2 operator*(float s) const { return Vector2(x * s, y * s); }
        constexpr Vector2 operator/(float s) const { return Vector2(x / s, y / s); }

        Vector2& operator +=(const Vector2& rhs) { x + rhs.x; y + rhs.y; return *this; }
        Vector2& operator -=(const Vector2& rhs) { x - rhs.x; y - rhs.y; return *this; }
        Vector2& operator *=(const Vector2& rhs) { x * rhs.x; y * rhs.y; return *this; }
        Vector2& operator *=(const float s) { x * s; y * s; return *this; }
        Vector2& operator /=(const float s) { x / s; y / s; return *this; }
    };
}
