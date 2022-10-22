#pragma once

#include "Common.h"

namespace M::MMath
{
    //Vector2
    inline float MagnitudeSqr(const Vector2& v);
    inline float Magnitude(const Vector2& v);

    inline float Distance(const Vector2& v1, Vector2& v2);
    inline float DistanceSqr(const Vector2& v1, Vector2& v2);

    inline float Dot(const Vector2& v1, Vector2& v2);
    inline Vector2 Cross(const Vector2& v1, Vector2& v2);

    //Vector3
    inline float MagnitudeSqr(const Vector3& v);
    inline float Magnitude(const Vector3& v);

    inline float Distance(const Vector3& v1, Vector3& v2);
    inline float DistanceSqr(const Vector3& v1, Vector3& v2);

    inline float Dot(const Vector3& v1, Vector3& v2);
    inline Vector3 Cross(const Vector3& v1, Vector3& v2);
    //Vector4
    inline float MagnitudeSqr(const Vector4& v);
    inline float Magnitude(const Vector4& v);

    inline float Distance(const Vector4& v1, Vector4& v2);
    inline float DistanceSqr(const Vector4& v1, Vector4& v2);

    inline float Dot(const Vector4& v1, Vector4& v2);
    inline Vector4 Cross(const Vector4& v1, Vector4& v2);
}
