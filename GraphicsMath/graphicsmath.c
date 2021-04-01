#include "graphicsmath.h"

float Clamp(float val, float min, float max)
{
    if(val >= max)
        val = max;
    else if(val <= min)
        val = min;
    
    return val;
}
float Interpolate(float a, float b, float t)
{
    return a + ((b - a) * t);
}

float DegToRad(float degrees)
{
    return (M_PI / 180.0f) * degrees;
}

float RadToDeg(float radians)
{
    return (180.0f / M_PI) * radians;
}