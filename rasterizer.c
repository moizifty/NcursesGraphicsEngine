#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <ncurses.h>
#include <memory.h>

#include "rasterizer.h"

static 

bool PointInTriangle(int x, int y, const Vec2 *v1, const Vec2 *v2, const Vec2 *v3)
{
    //from lectures
    float wv1 = ((v2->y - v3->y) * (x - v3->x) +
                 (v3->x - v2->x) * (y - v3->y)) /
                 ((v2->y - v3->y) * (v1->x - v3->x) +
                  (v3->x - v2->x) * (v1->y - v3->y)); 

    float wv2 = ((v3->y - v1->y) * (x - v3->x) +
                 (v1->x - v3->x) * (y - v3->y)) /
                 ((v2->y - v3->y) * (v1->x - v3->x) +
                  (v3->x - v2->x) * (v1->y - v3->y));
    
    float wv3 = 1.0f - wv1 - wv2;

    return (wv1 <= 1.0f) && (wv1 >= 0.001f) && (wv2 <= 1.0f) && (wv2 >= 0.001f) &&
           (wv3 <= 1.0f) && (wv3 >= 0.001f);

}
FrameBuffer **RasterizerInit(int fbWidth, int fbHeight)
{
    FrameBuffer **fbMalloc;
    if(fbMalloc = malloc(sizeof(FrameBuffer *) * 2))
    {
        if(fbMalloc[0] = malloc(sizeof(FrameBuffer)))
            RecreateFrameBuffer(fbMalloc[0], fbWidth, fbHeight);
        else
        {
            fprintf(stderr, "Could not malloc framebuffer\n");
            exit(EXIT_FAILURE);
        }

        if(fbMalloc[1] = malloc(sizeof(FrameBuffer)))
            RecreateFrameBuffer(fbMalloc[1], fbWidth, fbHeight);
        else
        {
            fprintf(stderr, "Could not malloc framebuffer\n");
            exit(EXIT_FAILURE);
        }

        return fbMalloc;
    }
    else
    {
        fprintf(stderr, "Could not malloc framebuffer\n");
        exit(EXIT_FAILURE);
    }
}
void RecreateFrameBuffer(FrameBuffer *fb, int fbWidth, int fbHeight)
{
    fb->width = fbWidth;
    fb->height = fbHeight;

    if((fb->colorBuffer = malloc(sizeof(ColorBuffer) * fbWidth * fbHeight)) == NULL)
    {
        fprintf(stderr, "Could not allocate memory for colorbuffer\n");
        exit(EXIT_FAILURE);
    }
    if((fb->depthBuffer = malloc(sizeof(DepthBuffer) * fbWidth * fbHeight)) == NULL)
    {
        fprintf(stderr, "Could not allocate memory for depthbuffer\n");
        exit(EXIT_FAILURE);
    }

    ClearFrameBuffer(fb, 0);
}
void ClearFrameBuffer(FrameBuffer *fb, int clearColor)
{
    memset(fb->colorBuffer, clearColor, sizeof(ColorBuffer) * fb->width * fb->height);
    memset(fb->depthBuffer, MAX_DEPTH, sizeof(DepthBuffer) * fb->width * fb->height);
}
void RasterizerFree(FrameBuffer ***fb)
{
    free((*fb)[0]->colorBuffer);
    free((*fb)[0]->depthBuffer);

    free((*fb)[1]->colorBuffer);
    free((*fb)[1]->depthBuffer);

    free((*fb)[0]);
    free((*fb)[1]);
    free(*fb);
}
void SetPixelFrameBuffer(FrameBuffer *fb, int posX, int posY, ColorBuffer color, DepthBuffer depth)
{
    //index of pixel in frame buffer
    //posY * fb.width gets skips the apropriate number of rows, adding posX gives 'indent' into the row
    int index = (posY * fb->width) + posX;

    //only draw pixel if it should be infront of the pixel already at that position
    //if the pixels depth is less then the pixel already at tht position
    if(depth < fb->depthBuffer[index])
    {
        fb->colorBuffer[index] = color;
        fb->depthBuffer[index] = depth;
    }
}
ColorBuffer GetPixelColorFrameBuffer(FrameBuffer *fb, int posX, int posY)
{
    int index = (posY * fb->width) + posX;
    return fb->colorBuffer[index];
}
DepthBuffer GetPixelDepthFrameBuffer(FrameBuffer *fb, int posX, int posY)
{
    int index = (posY * fb->width) + posX;
    return fb->depthBuffer[index];
}
void PrintFrameBuffer(FrameBuffer *presentFrame, threadpool tpool, void *(*rcb)(void *))
{
    thpool_add_work(tpool, rcb, NULL);
    
    for(int y = 0; y < presentFrame->height; y++)
    {
        for(int x = 0; x < presentFrame->width; x++)
        {
            ColorBuffer cb = GetPixelColorFrameBuffer(presentFrame, x, y);
            if(!cb)
                continue;

            int color = cb >> 8;
            mvprintw(y, x, "%c", (char)cb); 
        }
    }
    thpool_wait(tpool);
}
void SwapBuffers(FrameBuffer **presentFrame, FrameBuffer **renderFrame, FrameBuffer **frameBuffers, int *currentBuffer)
{
    *currentBuffer ^= 1;
    *presentFrame = frameBuffers[*currentBuffer];
    *renderFrame = frameBuffers[*currentBuffer ^ 1];
}
void RasterizeTriange(FrameBuffer *fb, const Vec2 *vv1, const Vec2 *vv2, const Vec2 *vv3)
{
    int minX, maxX,
        minY, maxY;

    int halfWidth = fb->width / 2, halfHeight = fb->height / 2;
    Vec2 v1 = {.x = vv1->x * halfWidth + halfWidth, .y = -vv1->y * halfHeight + halfHeight};
    Vec2 v2 = {.x = vv2->x * halfWidth + halfWidth, .y = -vv2->y * halfHeight + halfHeight};
    Vec2 v3 = {.x = vv3->x * halfWidth + halfWidth, .y = -vv3->y * halfHeight + halfHeight};

    //max because u dont want to go below 0
    minX = MAX(0, MIN(v1.x, MIN(v2.x, v3.x)));   
    minY = MAX(0, MIN(v1.y, MIN(v2.y, v3.y)));

    //clamp to rect bounds
    maxX = MIN(fb->width, ceil( MAX(v1.x, MAX(v2.x, v3.x)) +1));
    maxY = MIN(fb->height, ceil( MAX(v1.y, MAX(v2.y, v3.y)) + 1));

    for(int y = minY; y < maxY; y++)
    {
        for(int x = minX; x < maxX; x++)
        {
            if(PointInTriangle(x, y, &v1, &v2, &v3))
            {
                SetPixelFrameBuffer(fb, x, y, '#', 0);
            }
#ifdef DEBUG
            else
                SetPixelFrameBuffer(fb, x, y, '.', 0);
#endif
        }
    }
}