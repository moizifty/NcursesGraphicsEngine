#include "vector.h"

#pragma region VECTOR2
float MagnitudeVec2(const Vec2 *a)
{
    return sqrt((a->x * a->x) + (a->y * a->y));
}

void AddVec2(const Vec2 *a, const Vec2 *b, Vec2 *result)
{
    result->x = a->x + b->x;
    result->y = a->y + b->y;
}
void SubVec2(const Vec2 *a, const Vec2 *b, Vec2 *result)
{
    result->x = a->x - b->x;
    result->y = a->y - b->y;
}
void MultVec2(const Vec2 *a, const Vec2 *b, Vec2 *result)
{
    result->x = a->x * b->x;
    result->y = a->y * b->y;
}

void LerpVec2(const Vec2 *a, const Vec2 *b, float t, Vec2 *result)
{
    result->x = a->x + ((b->x - a->x) * t);
    result->y = a->y + ((b->y - a->y) * t);
}
float DotVec2(const Vec2 *a, const Vec2 *b)
{
    return (a->x * b->x) + (a->y * b->y);
}
float AngleVec2(const Vec2 *a, const Vec2 *b)
{
    float dot = DotVec2(a, b);
    return acos(dot / (MagnitudeVec2(a) * MagnitudeVec2(b)));
}
float DistVec2(const Vec2 *a, const Vec2 *b)
{
    float xDiff = a->x - b->x;
    float yDiff = a->y - b->y; 

    return sqrt(xDiff * xDiff + yDiff * yDiff); 
}

void NormalizeVec2(Vec2 *a)
{
    float mag = MagnitudeVec2(a);
    a->x /= mag;
    a->y /= mag;
}
void GetNormalizedVec2(const Vec2 *a, Vec2 *result)
{
    result->x = a->x;
    result->y = a->y;

    NormalizeVec2(result);
}
void ScaleVec2(Vec2 *a, float s)
{
    a->x *= s;
    a->y *= s;
}
#pragma endregion

#pragma region VECTOR3
float MagnitudeVec3(const Vec3 *a)
{
    return sqrt((a->x * a->x) + (a->y * a->y) + (a->z * a->z));
}

void AddVec3(const Vec3 *a, const Vec3 *b, Vec3 *result)
{
    result->x = a->x + b->x;
    result->y = a->y + b->y;
    result->z = a->z + b->z;
}
void SubVec3(const Vec3 *a, const Vec3 *b, Vec3 *result)
{
    result->x = a->x - b->x;
    result->y = a->y - b->y;
    result->z = a->z - b->z;
}
void MultVec3(const Vec3 *a, const Vec3 *b, Vec3 *result)
{
    result->x = a->x * b->x;
    result->y = a->y * b->y;
    result->z = a->z * b->z;
}

void LerpVec3(const Vec3 *a, const Vec3 *b, float t, Vec3 *result)
{
    result->x = a->x + ((b->x - a->x) * t);
    result->y = a->y + ((b->y - a->y) * t);
    result->z = a->z + ((b->z - a->z) * t);
}
float DotVec3(const Vec3 *a, const Vec3 *b)
{
    return (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
}
void CrossVec3(const Vec3 *a, const Vec3 *b, Vec3 *result)
{
    result->x = a->y * b->z - a->z * b->y;
    result->y = a->z * b->x - a->x * b->z;
    result->z = a->x * b->y - a->y * b->x;
}
float AngleVec3(const Vec3 *a, const Vec3 *b)
{
    float dot = DotVec3(a, b);
    return acos(dot / (MagnitudeVec3(a) * MagnitudeVec3(b)));
}
float DistVec3(const Vec3 *a, const Vec3 *b)
{
    float xDiff = a->x - b->x;
    float yDiff = a->y - b->y;
    float zDiff = a->z - b->z; 

    return sqrt(xDiff * xDiff + yDiff * yDiff + zDiff * zDiff); 
}

void NormalizeVec3(Vec3 *a)
{
    float mag = MagnitudeVec3(a);
    a->x /= mag;
    a->y /= mag;
    a->z /= mag;
}
void GetNormalizedVec3(const Vec3 *a, Vec3 *result)
{
    result->x = a->x;
    result->y = a->y;
    result->z = a->z;

    NormalizeVec3(result);
}
void ScaleVec3(Vec3 *a, float s)
{
    a->x *= s;
    a->y *= s;
    a->z *= s;
}
#pragma endregion

#pragma region VECTOR4
float MagnitudeVec4(const Vec4 *a)
{
    return sqrt((a->x * a->x) + (a->y * a->y) + (a->z * a->z) + (a->w * a->w));
}

void AddVec4(const Vec4 *a, const Vec4 *b, Vec4 *result)
{
    result->x = a->x + b->x;
    result->y = a->y + b->y;
    result->z = a->z + b->z;
    result->w = a->w + b->w;
}
void SubVec4(const Vec4 *a, const Vec4 *b, Vec4 *result)
{
    result->x = a->x - b->x;
    result->y = a->y - b->y;
    result->z = a->z - b->z;
    result->w = a->z - b->w;
}
void MultVec4(const Vec4 *a, const Vec4 *b, Vec4 *result)
{
    result->x = a->x * b->x;
    result->y = a->y * b->y;
    result->z = a->z * b->z;
    result->w = a->w * b->w;
}

void LerpVec4(const Vec4 *a, const Vec4 *b, float t, Vec4 *result)
{
    result->x = a->x + ((b->x - a->x) * t);
    result->y = a->y + ((b->y - a->y) * t);
    result->z = a->z + ((b->z - a->z) * t);
    result->w = a->w + ((b->w - a->w) * t);
}
float DotVec4(const Vec4 *a, const Vec4 *b)
{
    return (a->x * b->x) + (a->y * b->y) + (a->z * b->z) + (a->w * b->w);
}
float DistVec4(const Vec4 *a, const Vec4 *b)
{
    float xDiff = a->x - b->x;
    float yDiff = a->y - b->y;
    float zDiff = a->z - b->z; 
    float wDiff = a->w - b->w; 

    return sqrt(xDiff * xDiff + yDiff * yDiff + zDiff * zDiff + wDiff * wDiff); 
}

void NormalizeVec4(Vec4 *a)
{
    float mag = MagnitudeVec4(a);
    a->x /= mag;
    a->y /= mag;
    a->z /= mag;
    a->w /= mag;
}
void GetNormalizedVec4(const Vec4 *a, Vec4 *result)
{
    result->x = a->x;
    result->y = a->y;
    result->z = a->z;
    result->w = a->w;

    NormalizeVec4(result);
}
void ScaleVec4(Vec4 *a, float s)
{
    a->x *= s;
    a->y *= s;
    a->z *= s;
    a->w *= s;
}
#pragma endregion