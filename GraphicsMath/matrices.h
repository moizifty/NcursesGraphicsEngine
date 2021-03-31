#ifndef MATRICES_H
#define MATRICES_H
#include "vector.h"

#define DET33(m00, m01, m02, m10, m11, m12, m20, m21, m22) \
              (((m00) * ((m11) * (m22) - (m12) * (m21))) + \
              ((m01) * ((m12) * (m20) - (m10) * (m22))) + \
              ((m02) * ((m10) * (m21) - (m11) * (m20))))

typedef struct Matrix22
{
    float m00, m01,
          m10, m11;
}Matrix22;

typedef struct Matrix33
{
    float m00, m01, m02,
          m10, m11, m12,
          m20, m21, m22;
}Matrix33;

typedef struct Matrix44
{
    float m00, m01, m02, m03,
          m10, m11, m12, m13,
          m20, m21, m22, m23,
          m30, m31, m32, m33;
}Matrix44;

#pragma region MATRIX22
void AddMatrix22(const Matrix22 *a, const Matrix22 *b, Matrix22 *result);
void SubMatrix22(const Matrix22 *a, const Matrix22 *b, Matrix22 *result);
void MultMatrix22(const Matrix22 *a, const Matrix22 *b, Matrix22 *result);
void TransformMatrix22(const Matrix22 *matrix, const Vec2 *vec2, Vec2 *result);

void SetIdentityMatrix22(Matrix22 *a);
void SetZeroMatrix22(Matrix22 *a);
void TransposeMatrix22(Matrix22 *a);
void InverseMatrix22(Matrix22 *a);
void NegateMatrix22(Matrix22 *a);

float DetMatrix22(const Matrix22 *a);

#pragma endregion

#pragma region MATRIX33
void AddMatrix33(const Matrix33 *a, const Matrix33 *b, Matrix33 *result);
void SubMatrix33(const Matrix33 *a, const Matrix33 *b, Matrix33 *result);
void MultMatrix33(const Matrix33 *a, const Matrix33 *b, Matrix33 *result);
void TransformMatrix33(const Matrix33 *matrix, const Vec3 *vec3, Vec3 *result);

void SetIdentityMatrix33(Matrix33 *a);
void SetZeroMatrix33(Matrix33 *a);
void TransposeMatrix33(Matrix33 *a);
void InverseMatrix33(Matrix33 *a);
void NegateMatrix33(Matrix33 *a);

float DetMatrix33(const Matrix33 *a);

#pragma endregion

#pragma region MATRIX44
void AddMatrix44(const Matrix44 *a, const Matrix44 *b, Matrix44 *result);
void SubMatrix44(const Matrix44 *a, const Matrix44 *b, Matrix44 *result);
void MultMatrix44(const Matrix44 *a, const Matrix44 *b, Matrix44 *result);
void MultMatrix44Vec4(const Matrix44 *a, const Vec4 *b, Vec4 *result);
void TransformMatrix44(const Matrix44 *matrix, const Vec4 *vec4, Vec4 *result);

void SetIdentityMatrix44(Matrix44 *a);
void SetZeroMatrix44(Matrix44 *a);
void TransposeMatrix44(Matrix44 *a);
void InverseMatrix44(Matrix44 *a);
void NegateMatrix44(Matrix44 *a);

void ScaleMatrix44(Matrix44 *matrix, const Vec3 *scale);
void RotateMatrix44(Matrix44 *matrix, const Vec3 *eulerAxis, float angle);
void TranslateMatrix44(Matrix44 *matrix, const Vec4 *vec4);

float DetMatrix44(const Matrix44 *a);

#pragma endregion
#endif