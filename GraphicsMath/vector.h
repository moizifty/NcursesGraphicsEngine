#ifndef VECTOR_H
#define VECTOR_H
#include <math.h>
#include "mathextentions.h"

typedef struct Vec2 
{
    float x;
    float y;
} Vec2;

typedef struct Vec3 
{
    float x;
    float y;
    float z;
} Vec3;

typedef struct Vec4 
{
    float x;
    float y;
    float z;
    float w;
} Vec4;


#pragma region VECTOR2
float MagnitudeVec2(const Vec2 *a);

void AddVec2(const Vec2 *a, const Vec2 *b, Vec2 *result);
void SubVec2(const Vec2 *a, const Vec2 *b, Vec2 *result);
void MultVec2(const Vec2 *a, const Vec2 *b, Vec2 *result);

void LerpVec2(const Vec2 *a, const Vec2 *b, float t,  Vec2 *result);
float DotVec2(const Vec2 *a, const Vec2 *b);
float AngleVec2(const Vec2 *a, const Vec2 *b);
float DistVec2(const Vec2 *a, const Vec2 *b);

void NormalizeVec2(Vec2 *a);
void GetNormalizedVec2(const Vec2 *a, Vec2 *result);
void ScaleVec2(Vec2 *a, float s);
#pragma endregion

#pragma region VECTOR3
float MagnitudeVec3(const Vec3 *Vec3);

void AddVec3(const Vec3 *a, const Vec3 *b, Vec3 *result);
void SubVec3(const Vec3 *a, const Vec3 *b, Vec3 *result);
void MultVec3(const Vec3 *a, const Vec3 *b, Vec3 *result);

void LerpVec3(const Vec3 *a, const Vec3 *b, float t, Vec3 *result);
float DotVec3(const Vec3 *a, const Vec3 *b);
void CrossVec3(const Vec3 *a, const Vec3 *b, Vec3 *result);
float AngleVec3(const Vec3 *a, const Vec3 *b);
float DistVec3(const Vec3 *a, const Vec3 *b);

void NormalizeVec3(Vec3 *a);
void GetNormalizedVec3(const Vec3 *a, Vec3 *result);
void ScaleVec3(Vec3 *a, float s);
#pragma endregion

#pragma region VECTOR4
float MagnitudeVec4(const Vec4 *Vec4);

void AddVec4(const Vec4 *a, const Vec4 *b, Vec4 *result);
void SubVec4(const Vec4 *a, const Vec4 *b, Vec4 *result);
void MultVec4(const Vec4 *a, const Vec4 *b, Vec4 *result);

void LerpVec4(const Vec4 *a, const Vec4 *b, float t, Vec4 *result);
float DotVec4(const Vec4 *a, const Vec4 *b);
float DistVec4(const Vec4 *a, const Vec4 *b);

void NormalizeVec4(Vec4 *a);
void GetNormalizedVec4(const Vec4 *a, Vec4 *result);
void ScaleVec4(Vec4 *a, float s);
#pragma endregion
#endif