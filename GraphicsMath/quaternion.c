#include "quaternion.h"

void SetIdentityQuaternion(Quaternion *quaternion)
{
    quaternion->x = 0;
    quaternion->y = 0;
    quaternion->z = 0;
    quaternion->w = 1;

}
float MagnititudeQuaternion(Quaternion *quaternion)
{   
    return sqrt(quaternion->x * quaternion->x + quaternion->y * quaternion->y + quaternion->z * quaternion->z + quaternion->w * quaternion->w);
}
void NormalizeQuaternion(Quaternion *quaternion)
{
    float mag = MagnititudeQuaternion(quaternion);

    if(mag == 0) 
        return;

    quaternion->x /= mag;
    quaternion->y /= mag;
    quaternion->z /= mag;
    quaternion->w /= mag;
}
void NegateQuaternion(Quaternion *quaternion)
{
    quaternion->x *= -1;
    quaternion->y *= -1;
    quaternion->z *= -1;
    quaternion->w *= -1;
}

void MultQuarternion(const Quaternion *a, const Quaternion *b, Quaternion *result)
{
    result->x = a->x * b->w + a->w * b->x + a->y * b->z - a->z * b->y;
    result->y = a->y * b->w + a->w * b->y + a->z * b->x - a->x * b->z;
    result->z = a->z * b->w + a->w * b->z + a->x * b->y - a->y * b->x;
    result->w = a->w * b->w - a->x * b->x - a->y * b->y - a->z * b->z;
}
void MultQuarternionVec3(const Quaternion *a, const Vec3 *b, Vec3 *result)
{
    Matrix44 trans;
    ToMatrixQuarternion(a, &trans);
    Vec4 v = {.x = b->x, .y = b->y, .z = b->z, .w = 0};
    Vec4 mod;
    MultMatrix44Vec4(&trans, &v, &mod);
    result->x = mod.x;
    result->y = mod.y;
    result->z = mod.z;
}
void MultQuarternionVec4(const Quaternion *a, const Vec4 *b, Vec4 *result)
{
    Matrix44 trans;
    ToMatrixQuarternion(a, &trans);
    MultMatrix44Vec4(&trans, b, result);
}

void ToMatrixQuarternion(const Quaternion *quaternion, Matrix44 *dest)
{
    float xy = quaternion->x * quaternion->y;
    float xz = quaternion->x * quaternion->z;
    float xw = quaternion->x * quaternion->w;
    float yz = quaternion->y * quaternion->z;
    float yw = quaternion->y * quaternion->w;
    float zw = quaternion->z * quaternion->w;
    float xSquared = quaternion->x * quaternion->x;
    float ySquared = quaternion->y * quaternion->y;
    float zSquared = quaternion->z * quaternion->z;

    dest->m00 = 1 - 2 * (ySquared + zSquared);
    dest->m01 = 2 * (xy - zw);
    dest->m02 = 2 * (xz + yw);
    dest->m03 = 0;
    dest->m10 = 2 * (xy + zw);
    dest->m11 = 1 - 2 * (xSquared + zSquared);
    dest->m12 = 2 * (yz - xw);
    dest->m13 = 0;
    dest->m20 = 2 * (xz - yw);
    dest->m21 = 2 * (yz + xw);
    dest->m22 = 1 - 2 * (xSquared + ySquared);
    dest->m23 = 0;
    dest->m30 = 0;
    dest->m31 = 0;
    dest->m32 = 0;
    dest->m33 = 1;
}
void SetToAxisAngleQuaternion(Quaternion *quaternion, const Vec3 *axis, float angle)
{
    Matrix44 rot;
    RotateMatrix44(&rot, axis, angle);

    SetMatrixQuaternion(quaternion, &rot);
    NormalizeQuaternion(quaternion);
}
void SlerpQuaternion(const Quaternion *a, const Quaternion *b, float t, Quaternion *result)
{
    float dot = a->w * b->w + a->x * b->x + a->y * b->y + a->z * b->z;
    float blendI = 1.0f - t;

    if (dot < 0)
    {
        result->w = blendI * a->w + t * -b->w;
        result->x = blendI * a->x + t * -b->x;
        result->y = blendI * a->y + t * -b->y;
        result->z = blendI * a->z + t * -b->z;
    }
    else
    {
        result->w = blendI * a->w + t * b->w;
        result->x = blendI * a->x + t * b->x;
        result->y = blendI * a->y + t * b->y;
        result->z = blendI * a->z + t * b->z;
    }

    NormalizeQuaternion(result);
}
void LookRotationQuaternion(Quaternion *quaternion, const Vec3 *forward, const Vec3 *up)
{
    Vec3 f = *forward;
    Vec3 u = *up;

    NormalizeVec3(&f);
    NormalizeVec3(&u);
    Vec3 right;
    CrossVec3(&f, &u, &right);

    Matrix44 rot;
    rot.m00 = right.x;
    rot.m10 = right.y;
    rot.m20 = right.z;

    rot.m01 = up->x;
    rot.m11 = up->y;
    rot.m21 = up->z;

    rot.m02 = forward->x;
    rot.m12 = forward->y;
    rot.m22 = forward->z;

    SetMatrixQuaternion(quaternion, &rot);
    NormalizeQuaternion(quaternion);
}
void SetMatrixQuaternion(Quaternion *quaternion, const Matrix44 *matrix)
{
    float m00, m01, m02;
    float m10, m11, m12;
    float m20, m21, m22;

    m00 = matrix->m00;
    m01 = matrix->m01;
    m02 = matrix->m02;

    m10 = matrix->m10;
    m11 = matrix->m11;
    m12 = matrix->m12;

    m20 = matrix->m20;
    m21 = matrix->m21;
    m22 = matrix->m22;

    float s;
    float tr = m00 + m11 + m22;
    if (tr >= 0.0) {
        s = (float) sqrt(tr + 1.0);
        quaternion->w = s * 0.5f;
        s = 0.5f / s;
        quaternion->x = (m21 - m12) * s;
        quaternion->y = (m02 - m20) * s;
        quaternion->z = (m10 - m01) * s;
    } else {
        float max = MAX(MAX(m00, m11), m22);
        if (max == m00) {
            s = (float) sqrt(m00 - (m11 + m22) + 1.0);
            quaternion->x = s * 0.5f;
            s = 0.5f / s;
            quaternion->y = (m01 + m10) * s;
            quaternion->z = (m20 + m02) * s;
            quaternion->w = (m21 - m12) * s;
        } else if (max == m11) {
            s = (float) sqrt(m11 - (m22 + m00) + 1.0);
            quaternion->y = s * 0.5f;
            s = 0.5f / s;
            quaternion->z = (m12 + m21) * s;
            quaternion->x = (m01 + m10) * s;
            quaternion->w = (m02 - m20) * s;
        } else {
            s = (float) sqrt(m22 - (m00 + m11) + 1.0);
            quaternion->z = s * 0.5f;
            s = 0.5f / s;
            quaternion->x = (m20 + m02) * s;
            quaternion->y = (m12 + m21) * s;
            quaternion->w = (m10 - m01) * s;
        }
    }
}