#include "matrices.h"

#pragma region MATRIX22
void AddMatrix22(const Matrix22 *a, const Matrix22 *b, Matrix22 *result)
{
    result->m00 = a->m00 + b->m00;
    result->m01 = a->m01 + b->m01;
    result->m10 = a->m10 + b->m10;
    result->m11 = a->m11 + b->m11;
}
void SubMatrix22(const Matrix22 *a, const Matrix22 *b, Matrix22 *result)
{
    result->m00 = a->m00 - b->m00;
    result->m01 = a->m01 - b->m01;
    result->m10 = a->m10 - b->m10;
    result->m11 = a->m11 - b->m11;
}
void MultMatrix22(const Matrix22 *a, const Matrix22 *b, Matrix22 *result)
{
    result->m00 = a->m00 * b->m00 + a->m01 * b->m10;
    result->m01 = a->m00 * b->m01 + a->m01 * b->m11;

    result->m10 = a->m10 * b->m00 + a->m11 * b->m10;
    result->m11 = a->m10 * b->m01 + a->m11 * b->m11;
}
void TransformMatrix22(const Matrix22 *matrix, const Vec2 *vec2, Vec2 *result)
{
    result->x = matrix->m00 * vec2->x + matrix->m01 * vec2->y;
    result->y = matrix->m10 * vec2->x + matrix ->m11 * vec2->y;
}   

void SetIdentityMatrix22(Matrix22 *a)
{
    a->m00 = a->m11 = 1;
    a->m01 = a->m10 = 0;
}
void SetZeroMatrix22(Matrix22 *a)
{
    a->m00 = a->m11 = a->m01 = a->m10 = 0;
}
void TransposeMatrix22(Matrix22 *a)
{
    float temp = a->m10;
    a->m10 = a->m01;
    a->m01 = temp;
}
void InverseMatrix22(Matrix22 *a)
{
    float det = DetMatrix22(a);
    if(det)
    {
        float detInv = 1.0f / det;
        float temp = a->m00;
        a->m00 = a->m11 * detInv;
        a->m11 = temp * detInv;
        
        temp = a->m01 * detInv;
        a->m01 = -a->m10 * detInv;
        a->m10 = -temp * detInv;
    }
}
void NegateMatrix22(Matrix22 *a)
{
    a->m00 *= -1;
    a->m01 *= -1;
    a->m10 *= -1;
    a->m11 *= -1;
}

float DetMatrix22(const Matrix22 *a)
{
    return (a->m00 * a->m11) - (a->m01 * a->m10);
}
#pragma endregion

#pragma region MATRIX33
void AddMatrix33(const Matrix33 *a, const Matrix33 *b, Matrix33 *result)
{
    result->m00 = a->m00 + b->m00;
    result->m01 = a->m01 + b->m01;
    result->m02 = a->m02 + b->m02;

    result->m10 = a->m10 + b->m10;
    result->m11 = a->m11 + b->m11;
    result->m12 = a->m12 + b->m12;

    result->m20 = a->m20 + b->m20;
    result->m21 = a->m21 + b->m21;
    result->m22 = a->m22 + b->m22;
}
void SubMatrix33(const Matrix33 *a, const Matrix33 *b, Matrix33 *result)
{
    result->m00 = a->m00 - b->m00;
    result->m01 = a->m01 - b->m01;
    result->m02 = a->m02 - b->m02;

    result->m10 = a->m10 - b->m10;
    result->m11 = a->m11 - b->m11;
    result->m12 = a->m12 - b->m12;

    result->m20 = a->m20 - b->m20;
    result->m21 = a->m21 - b->m21;
    result->m22 = a->m22 - b->m22;
}

void MultMatrix33(const Matrix33 *a, const Matrix33 *b, Matrix33 *result)
{
    result->m00 = a->m00 * b->m00 + a->m01 * b->m10 + a->m02 * b->m20;
    result->m01 = a->m00 * b->m01 + a->m01 * b->m11 + a->m02 * b->m21;
    result->m02 = a->m00 * b->m02 + a->m01 * b->m12 + a->m02 * b->m22;

    result->m10 = a->m10 * b->m00 + a->m11 * b->m10 + a->m12 * b->m20;
    result->m11 = a->m10 * b->m01 + a->m11 * b->m11 + a->m12 * b->m21;
    result->m12 = a->m10 * b->m02 + a->m11 * b->m12 + a->m12 * b->m22;

    result->m20 = a->m20 * b->m00 + a->m21 * b->m10 + a->m22 * b->m20;
    result->m21 = a->m20 * b->m01 + a->m21 * b->m11 + a->m22 * b->m21;
    result->m22 = a->m20 * b->m02 + a->m21 * b->m12 + a->m22 * b->m22;
}
void TransformMatrix33(const Matrix33 *matrix, const Vec3 *vec3, Vec3 *result)
{
    result->x = matrix->m00 * vec3->x + matrix->m01 * vec3->y + matrix->m02 * vec3->z;
    result->y = matrix->m10 * vec3->x + matrix->m11 * vec3->y + matrix->m12 * vec3->z;
    result->z = matrix->m20 * vec3->x + matrix->m21 * vec3->y + matrix->m22 * vec3->z;
}   
void SetIdentityMatrix33(Matrix33 *a)
{
    a->m00 = a->m11 = a->m22 = 1;
    a->m01 = a->m02 = a->m10 = a->m12 = a->m20 = a->m21 = 0;
}
void SetZeroMatrix33(Matrix33 *a)
{
    a->m00 = a->m11 = a->m22 = a->m01 = a->m02 = a->m10 = a->m12 = a->m20 = a->m21 = 0;
}
void TransposeMatrix33(Matrix33 *a)
{
    float temp = a->m10;
    a->m10 = a->m01;
    a->m01 = temp;

    temp = a->m20;
    a->m20 = a->m02;
    a->m02 = temp;

    temp = a->m12;
    a->m12 = a->m21;
    a->m21 = temp;
}
void InverseMatrix33(Matrix33 *a)
{
    float det = DetMatrix33(a);
    if(det)
    {
        float detInv = 1.0f / det;
        float m00 = a->m11 * a->m22 - a->m12 * a->m21;
        float m01 = a->m10 * a->m22 - a->m12 * a->m20;
        float m02 = a->m10 * a->m21 - a->m11 * a->m20;

        float m10 = a->m01 * a->m22 - a->m02 * a->m21;
        float m11 = a->m00 * a->m22 - a->m02 * a->m20;
        float m12 = a->m00 * a->m21 - a->m01 * a->m20;

        float m20 = a->m01 * a->m12 - a->m02 * a->m11;
        float m21 = a->m00 * a->m12 - a->m02 * a->m10;
        float m22 = a->m00 * a->m11 - a->m01 * a->m10;

        a->m00 = m00 * detInv;
        a->m01 = -m10 * detInv;
        a->m02 = m20 * detInv;

        a->m10 = -m01 * detInv;
        a->m11 = m11 * detInv;
        a->m12 = -m21 * detInv;

        a->m20 = m02 * detInv;
        a->m21 = -m12 * detInv;
        a->m22 = m22 * detInv;

    }
}
void NegateMatrix33(Matrix33 *a)
{
    a->m00 *= -1;
    a->m01 *= -1;
    a->m02 *= -1;

    a->m10 *= -1;
    a->m11 *= -1;
    a->m12 *= -1;

    a->m20 *= -1;
    a->m21 *= -1;
    a->m22 *= -1;

}
float DetMatrix33(const Matrix33 *a)
{
    return (a->m00 * (a->m11 * a->m22 - a->m12 * a->m21)) - (a->m01 * (a->m10 * a->m22 - a->m12 * a->m20)) 
            + (a->m02 * (a->m10 * a->m21 - a->m11 * a->m20));
}
#pragma endregion

#pragma region MATRIX44
void AddMatrix44(const Matrix44 *a, const Matrix44 *b, Matrix44 *result)
{
    result->m00 = a->m00 + b->m00;
    result->m01 = a->m01 + b->m01;
    result->m02 = a->m02 + b->m02;
    result->m03 = a->m03 + b->m03;

    result->m10 = a->m10 + b->m10;
    result->m11 = a->m11 + b->m11;
    result->m12 = a->m12 + b->m12;
    result->m13 = a->m13 + b->m13;

    result->m20 = a->m20 + b->m20;
    result->m21 = a->m21 + b->m21;
    result->m22 = a->m22 + b->m22;
    result->m23 = a->m23 + b->m23;

    result->m30 = a->m30 + b->m30;
    result->m31 = a->m31 + b->m31;
    result->m32 = a->m32 + b->m32;
    result->m33 = a->m33 + b->m33;
}
void SubMatrix44(const Matrix44 *a, const Matrix44 *b, Matrix44 *result)
{
    result->m00 = a->m00 - b->m00;
    result->m01 = a->m01 - b->m01;
    result->m02 = a->m02 - b->m02;
    result->m03 = a->m03 - b->m03;

    result->m10 = a->m10 - b->m10;
    result->m11 = a->m11 - b->m11;
    result->m12 = a->m12 - b->m12;
    result->m13 = a->m13 - b->m13;

    result->m20 = a->m20 - b->m20;
    result->m21 = a->m21 - b->m21;
    result->m22 = a->m22 - b->m22;
    result->m23 = a->m23 - b->m23;

    result->m30 = a->m30 - b->m30;
    result->m31 = a->m31 - b->m31;
    result->m32 = a->m32 - b->m32;
    result->m33 = a->m33 - b->m33;
}

void MultMatrix44(const Matrix44 *a, const Matrix44 *b, Matrix44 *result)
{
    result->m00 = a->m00 * b->m00 + a->m01 * b->m10 + a->m02 * b->m20 + a->m03 * b->m30;
    result->m01 = a->m00 * b->m01 + a->m01 * b->m11 + a->m02 * b->m21 + a->m03 * b->m31;
    result->m02 = a->m00 * b->m02 + a->m01 * b->m12 + a->m02 * b->m22 + a->m03 * b->m32;
    result->m03 = a->m00 * b->m03 + a->m01 * b->m13 + a->m02 * b->m23 + a->m03 * b->m33;

    result->m10 = a->m10 * b->m00 + a->m11 * b->m10 + a->m12 * b->m20 + a->m13 * b->m30;
    result->m11 = a->m10 * b->m01 + a->m11 * b->m11 + a->m12 * b->m21 + a->m13 * b->m31;
    result->m12 = a->m10 * b->m02 + a->m11 * b->m12 + a->m12 * b->m22 + a->m13 * b->m32;
    result->m13 = a->m10 * b->m03 + a->m11 * b->m13 + a->m12 * b->m23 + a->m13 * b->m33;

    result->m20 = a->m20 * b->m00 + a->m21 * b->m10 + a->m22 * b->m20 + a->m23 * b->m30;
    result->m21 = a->m20 * b->m01 + a->m21 * b->m11 + a->m22 * b->m21 + a->m23 * b->m31;
    result->m22 = a->m20 * b->m02 + a->m21 * b->m12 + a->m22 * b->m22 + a->m23 * b->m32;
    result->m23 = a->m20 * b->m03 + a->m21 * b->m13 + a->m22 * b->m23 + a->m23 * b->m33;

    result->m30 = a->m30 * b->m00 + a->m31 * b->m10 + a->m32 * b->m20 + a->m33 * b->m30;
    result->m31 = a->m30 * b->m01 + a->m31 * b->m11 + a->m32 * b->m21 + a->m33 * b->m31;
    result->m32 = a->m30 * b->m02 + a->m31 * b->m12 + a->m32 * b->m22 + a->m33 * b->m32;
    result->m33 = a->m30 * b->m03 + a->m31 * b->m13 + a->m32 * b->m23 + a->m33 * b->m33;
}

void MultMatrix44Vec4(const Matrix44 *a, const Vec4 *b, Vec4 *result)
{
    TransformMatrix44(a, b, result);
}
void TransformMatrix44(const Matrix44 *matrix, const Vec4 *vec4, Vec4 *result)
{
    result->x = matrix->m00 * vec4->x + matrix->m01 * vec4->y + matrix->m02 * vec4->z + matrix->m03 * vec4->w;
    result->y = matrix->m10 * vec4->x + matrix->m11 * vec4->y + matrix->m12 * vec4->z + matrix->m13 * vec4->w;
    result->z = matrix->m20 * vec4->x + matrix->m21 * vec4->y + matrix->m22 * vec4->z + matrix->m23 * vec4->w;
    result->z = matrix->m30 * vec4->x + matrix->m31 * vec4->y + matrix->m32 * vec4->z + matrix->m33 * vec4->w;
}   
void SetIdentityMatrix44(Matrix44 *a)
{
    a->m00 = a->m11 = a->m22 = a->m33 = 1;
    a->m01 = a->m02 = a->m03 = a->m10 = a->m12 = a->m13 = a->m20 = a->m21 = a->m23 = a->m30 = a->m31 = a->m32 = 0;
}
void SetZeroMatrix44(Matrix44 *a)
{
    a->m00 = a->m11 = a->m22 = a->m33 = a->m01 = a->m02 = a->m03 = a->m10 = a->m12 = a->m13 = a->m20 = a->m21 = a->m23 = a->m30 = a->m31 = a->m32 = 0;
}
void TransposeMatrix44(Matrix44 *a)
{
    float temp = a->m10;
    a->m10 = a->m01;
    a->m01 = temp;

    temp = a->m20;
    a->m20 = a->m02;
    a->m02 = temp;

    temp = a->m30;
    a->m30 = a->m03;
    a->m03 = temp;

    temp = a->m12;
    a->m12 = a->m21;
    a->m21 = temp;

    temp = a->m13;
    a->m13 = a->m31;
    a->m31 = temp;

    temp = a->m23;
    a->m23 = a->m32;
    a->m32 = temp;
}
void InverseMatrix44(Matrix44 *a)
{
    float det = DetMatrix44(a);
    if (det) 
    {
        float detInv = (float)1/det;

        float t00 =  DET33(a->m11, a->m12, a->m13, a->m21, a->m22, a->m23, a->m31, a->m32, a->m33);
        float t01 = -DET33(a->m10, a->m12, a->m13, a->m20, a->m22, a->m23, a->m30, a->m32, a->m33);
        float t02 =  DET33(a->m10, a->m11, a->m13, a->m20, a->m21, a->m23, a->m30, a->m31, a->m33);
        float t03 = -DET33(a->m10, a->m11, a->m12, a->m20, a->m21, a->m22, a->m30, a->m31, a->m32);

        float t10 = -DET33(a->m01, a->m02, a->m03, a->m21, a->m22, a->m23, a->m31, a->m32, a->m33);
        float t11 =  DET33(a->m00, a->m02, a->m03, a->m20, a->m22, a->m23, a->m30, a->m32, a->m33);
        float t12 = -DET33(a->m00, a->m01, a->m03, a->m20, a->m21, a->m23, a->m30, a->m31, a->m33);
        float t13 =  DET33(a->m00, a->m01, a->m02, a->m20, a->m21, a->m22, a->m30, a->m31, a->m32);

        float t20 =  DET33(a->m01, a->m02, a->m03, a->m11, a->m12, a->m13, a->m31, a->m32, a->m33);
        float t21 = -DET33(a->m00, a->m02, a->m03, a->m10, a->m12, a->m13, a->m30, a->m32, a->m33);
        float t22 =  DET33(a->m00, a->m01, a->m03, a->m10, a->m11, a->m13, a->m30, a->m31, a->m33);
        float t23 = -DET33(a->m00, a->m01, a->m02, a->m10, a->m11, a->m12, a->m30, a->m31, a->m32);

        float t30 = -DET33(a->m01, a->m02, a->m03, a->m11, a->m12, a->m13, a->m21, a->m22, a->m23);
        float t31 =  DET33(a->m00, a->m02, a->m03, a->m10, a->m12, a->m13, a->m20, a->m22, a->m23);
        float t32 = -DET33(a->m00, a->m01, a->m03, a->m10, a->m11, a->m13, a->m20, a->m21, a->m23);
        float t33 =  DET33(a->m00, a->m01, a->m02, a->m10, a->m11, a->m12, a->m20, a->m21, a->m22);

        a->m00 = t00*detInv;
        a->m11 = t11*detInv;
        a->m22 = t22*detInv;
        a->m33 = t33*detInv;
        a->m01 = t10*detInv;
        a->m10 = t01*detInv;
        a->m20 = t02*detInv;
        a->m02 = t20*detInv;
        a->m12 = t21*detInv;
        a->m21 = t12*detInv;
        a->m03 = t30*detInv;
        a->m30 = t03*detInv;
        a->m13 = t31*detInv;
        a->m31 = t13*detInv;
        a->m32 = t23*detInv;
        a->m23 = t32*detInv;
    }
}
void NegateMatrix44(Matrix44 *a)
{
    a->m00 *= -1;
    a->m01 *= -1;
    a->m02 *= -1;
    a->m03 *= -1;

    a->m10 *= -1;
    a->m11 *= -1;
    a->m12 *= -1;
    a->m13 *= -1;

    a->m20 *= -1;
    a->m21 *= -1;
    a->m22 *= -1;
    a->m23 *= -1;

    a->m30 *= -1;
    a->m31 *= -1;
    a->m32 *= -1;
    a->m33 *= -1;
}

void ScaleMatrix44(Matrix44 *matrix, const Vec3 *scale)
{
    matrix->m00 = matrix->m00 * scale->x;
    matrix->m01 = matrix->m01 * scale->x;
    matrix->m02 = matrix->m02 * scale->x;
    matrix->m03 = matrix->m03 * scale->x;

    matrix->m10 = matrix->m10 * scale->y;
    matrix->m11 = matrix->m11 * scale->y;
    matrix->m12 = matrix->m12 * scale->y;
    matrix->m13 = matrix->m13 * scale->y;

    matrix->m20 = matrix->m20 * scale->z;
    matrix->m21 = matrix->m21 * scale->z;
    matrix->m22 = matrix->m22 * scale->z;
    matrix->m23 = matrix->m23 * scale->z;
}
void RotateMatrix44(Matrix44 *matrix, const Vec3 *eulerAxis, float angle)
{
    float c = (float) cos(angle);
    float s = (float) sin(angle);
    float oneminusc = 1.0f - c;
    float xy = eulerAxis->x*eulerAxis->y;
    float yz = eulerAxis->y*eulerAxis->z;
    float xz = eulerAxis->x*eulerAxis->z;
    float xs = eulerAxis->x*s;
    float ys = eulerAxis->y*s;
    float zs = eulerAxis->z*s;

    float f00 = eulerAxis->x*eulerAxis->x*oneminusc+c;
    float f01 = xy*oneminusc+zs;
    float f02 = xz*oneminusc-ys;
    float f10 = xy*oneminusc-zs;
    float f11 = eulerAxis->y*eulerAxis->y*oneminusc+c;
    float f12 = yz*oneminusc+xs;
    float f20 = xz*oneminusc+ys;
    float f21 = yz*oneminusc-xs;
    float f22 = eulerAxis->z*eulerAxis->z*oneminusc+c;

    float t00 = matrix->m00 * f00 + matrix->m10 * f01 + matrix->m20 * f02;
    float t01 = matrix->m01 * f00 + matrix->m11 * f01 + matrix->m21 * f02;
    float t02 = matrix->m02 * f00 + matrix->m12 * f01 + matrix->m22 * f02;
    float t03 = matrix->m03 * f00 + matrix->m13 * f01 + matrix->m23 * f02;
    float t10 = matrix->m00 * f10 + matrix->m10 * f11 + matrix->m20 * f12;
    float t11 = matrix->m01 * f10 + matrix->m11 * f11 + matrix->m21 * f12;
    float t12 = matrix->m02 * f10 + matrix->m12 * f11 + matrix->m22 * f12;
    float t13 = matrix->m03 * f10 + matrix->m13 * f11 + matrix->m23 * f12;

    matrix->m20 = matrix->m00 * f20 + matrix->m10 * f21 + matrix->m20 * f22;
    matrix->m21 = matrix->m01 * f20 + matrix->m11 * f21 + matrix->m21 * f22;
    matrix->m22 = matrix->m02 * f20 + matrix->m12 * f21 + matrix->m22 * f22;
    matrix->m23 = matrix->m03 * f20 + matrix->m13 * f21 + matrix->m23 * f22;
    matrix->m00 = t00;
    matrix->m01 = t01;
    matrix->m02 = t02;
    matrix->m03 = t03;
    matrix->m10 = t10;
    matrix->m11 = t11;
    matrix->m12 = t12;
    matrix->m13 = t13;
}
void TranslateMatrix44(Matrix44 *matrix, const Vec4 *vec4)
{
    matrix->m30 += matrix->m00 * vec4->x + matrix->m10 * vec4->y + matrix->m20 * vec4->z;
    matrix->m31 += matrix->m01 * vec4->x + matrix->m11 * vec4->y + matrix->m21 * vec4->z;
    matrix->m32 += matrix->m02 * vec4->x + matrix->m12 * vec4->y + matrix->m22 * vec4->z;
    matrix->m33 += matrix->m03 * vec4->x + matrix->m13 * vec4->y + matrix->m23 * vec4->z;
}

float DetMatrix44(const Matrix44 *a)
{
    float f = a->m00 * ((a->m11 * a->m22 * a->m33 + a->m12 * a->m23 * a->m31 + a->m13 * a->m21 * a->m32)
            - a->m13 * a->m22 * a->m31
            - a->m11 * a->m23 * a->m32
            - a->m12 * a->m21 * a->m33);
    f -= a->m01 * ((a->m10 * a->m22 * a->m33 + a->m12 * a->m23 * a->m30 + a->m13 * a->m20 * a->m32)
            - a->m13 * a->m22 * a->m30
            - a->m10 * a->m23 * a->m32
            - a->m12 * a->m20 * a->m33);
    f += a->m02 * ((a->m10 * a->m21 * a->m33 + a->m11 * a->m23 * a->m30 + a->m13 * a->m20 * a->m31)
            - a->m13 * a->m21 * a->m30
            - a->m10 * a->m23 * a->m31
            - a->m11 * a->m20 * a->m33);
    f -= a->m03 * ((a->m10 * a->m21 * a->m32 + a->m11 * a->m22 * a->m30 + a->m12 * a->m20 * a->m31)
            - a->m12 * a->m21 * a->m30
            - a->m10 * a->m22 * a->m31
            - a->m11 * a->m20 * a->m32);
    return f;
}
#pragma endregion
