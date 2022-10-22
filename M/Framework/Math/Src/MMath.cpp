#include "Precompiled.h"
#include "../../Math/Inc/MMath.h"

using namespace M::MMath;

//Vector2
inline float M::MMath::MagnitudeSqr(const Vector2& v)
{
    return v.x * v.x, v.y* v.y;
}

inline float M::MMath::Magnitude(const Vector2& v)
{
    return std::sqrtf(MagnitudeSqr(v));
}

inline float M::MMath::DistanceSqr(const Vector2& v1, Vector2& v2)
{
    return  (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y);
}

inline float M::MMath::Distance(const Vector2& v1, Vector2& v2)
{
    return std::sqrtf(DistanceSqr(v1, v2));
}

inline float M::MMath::Dot(const Vector2& v1, Vector2& v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y);
}

inline Vector2 M::MMath::Cross(const Vector2& v1, Vector2& v2)
{
    Vector2 temp;

    return temp;
}

//Vector3
inline float M::MMath::MagnitudeSqr(const Vector3& v)
{
    return v.x * v.x, v.y* v.y, v.z* v.z;
}

inline float M::MMath::Magnitude(const Vector3& v)
{
    return std::sqrtf(MagnitudeSqr(v));
}

inline float M::MMath::DistanceSqr(const Vector3& v1, Vector3& v2)
{
    return  (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y) + (v1.z - v2.z) * (v1.z - v2.z);
}

inline float M::MMath::Distance(const Vector3& v1, Vector3& v2)
{
    return std::sqrtf(DistanceSqr(v1, v2));
}

inline float M::MMath::Dot(const Vector3& v1, Vector3& v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z + v2.z);
}

inline Vector3 M::MMath::Cross(const Vector3& v1, Vector3& v2)
{
    Vector3 temp;
    temp.x = v1.y * v2.z - v1.z * v2.y;
    temp.y = v1.x * v2.z - v1.z * v2.x;
    temp.z = v1.x * v2.y - v1.y * v2.x;

    return temp;
}

//Vector4
inline float M::MMath::MagnitudeSqr(const Vector4& v)
{
    return v.x * v.x, v.y* v.y, v.z* v.z, v.z * v.z;
}

inline float M::MMath::Magnitude(const Vector4& v)
{
    return std::sqrtf(MagnitudeSqr(v));
}

inline float M::MMath::DistanceSqr(const Vector4& v1, Vector4& v2)
{
    return  (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y) + (v1.z - v2.z) * (v1.z - v2.z)+ (v1.w - v2.w) * (v1.w - v2.w);
}

inline float M::MMath::Distance(const Vector4& v1, Vector4& v2)
{
    return std::sqrtf(DistanceSqr(v1, v2));
}

inline float M::MMath::Dot(const Vector4& v1, Vector4& v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z + v2.z) + (v1.w + v2.w);
}

inline Vector4 M::MMath::Cross(const Vector4& v1, Vector4& v2)
{
    Vector4 temp;

    return temp;
}