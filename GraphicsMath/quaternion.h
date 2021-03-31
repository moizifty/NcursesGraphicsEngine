#ifndef QUATERNION_H
#define QUATERNION_H
#include "vector.h"
#include "matrices.h"

#define MAX(a, b) (((a)>(b))? (a) : (b))
#define MIN(a, b) (((a)<(b))? (a) : (b))

typedef struct Quaternion
{
    int x;
    int y;
    int z;
    int w;
}Quaternion;

void SetIdentityQuaternion(Quaternion *quaternion);
float MagnititudeQuaternion(Quaternion *quaternion);
void NormalizeQuaternion(Quaternion *queternion);
void NegateQuaternion(Quaternion *quaternion);

void MultQuarternion(const Quaternion *a, const Quaternion *b, Quaternion *result);
void MultQuarternionVec3(const Quaternion *a, const Vec3 *b, Vec3 *result);
void MultQuarternionVec4(const Quaternion *a, const Vec4 *b, Vec4 *result); 

void ToMatrixQuarternion(const Quaternion *quaternion, Matrix44 *dest);
void SetToAxisAngleQuaternion(Quaternion *quaternion, const Vec3 *axis, float angle);
void SlerpQuaternion(const Quaternion *a, const Quaternion *b, float t, Quaternion *result);
void LookRotationQuaternion(Quaternion *quaternion, const Vec3 *forward, const Vec3 *up);
void SetMatrixQuaternion(Quaternion *quaternion, const Matrix44 *matrix);

#endif