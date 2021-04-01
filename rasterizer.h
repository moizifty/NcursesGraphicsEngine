#ifndef RASTERIZER_H
#define RASTERIZER_H
#include "thpool.h"
#include "GraphicsMath/graphicsmath.h"

//max depth of depth buffer
//0xff because its 8 byte int, and 0xff is max value for 8 byte int
#define MAX_DEPTH 0xff
//each pixel in array of pixels has depth and color
typedef uint8_t DepthBuffer;
//lower byte of color buffer is character at pixel, and upper byte is color
typedef uint16_t ColorBuffer;

typedef struct FrameBuffer
{
    int width;
    int height;

    DepthBuffer *depthBuffer;
    ColorBuffer *colorBuffer;
}FrameBuffer;


FrameBuffer **RasterizerInit(int fbWidth, int fbHeight);
void RecreateFrameBuffer(FrameBuffer *fb, int fbWidth, int fbHeight);
void ClearFrameBuffer(FrameBuffer *fb, int clearColor);
void SetPixelFrameBuffer(FrameBuffer *fb, int posX, int posY, ColorBuffer color, DepthBuffer depth);
ColorBuffer GetPixelColorFrameBuffer(FrameBuffer *fb, int posX, int posY);
DepthBuffer GetPixelDepthFrameBuffer(FrameBuffer *fb, int posX, int posY);
void PrintFrameBuffer(FrameBuffer *presentFrame, threadpool tpool, void *(*rcb)(void *));
void RasterizeTriange(FrameBuffer *fb, const Vec2 *v1, const Vec2 *v2, const Vec2 *v3);
void SwapBuffers(FrameBuffer **presentFrame, FrameBuffer **renderFrame, FrameBuffer **frameBuffers, int *currentBuffer);
void RasterizerFree(FrameBuffer ***fb);


#endif