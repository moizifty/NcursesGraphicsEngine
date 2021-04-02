#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <ncurses.h>
#include "GraphicsMath/graphicsmath.h"
#include "rasterizer.h"

#include "thpool.h"

#define WinHeight (LINES)
#define WinWidth  (COLS)

float angle = 0;
int currentFrameBuffer = 0;
FrameBuffer *presentFrame;
FrameBuffer *renderFrame;
FrameBuffer **frameBuffers;

void *
RenderCallback(void *args)
{
    //always set transform matrix to identity, starrting off so i dont mess up transforms
    Matrix44 transform =
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
    };

    Vec3 scale = {5, 1, 1};
    Vec3 rotateAxis = {0, 1, 1};

    //ScaleMatrix44(&transform, &scale);
    RotateMatrix44(&transform, &rotateAxis, DegToRad(-angle));

    Vec4 v4a = {-0.5, 0.5, 0, 1};
    Vec4 v4b = {0.5, 0.5, 0, 1};
    Vec4 v4c = {0, -0.5, 0, 1};

    Vec4 v4ar, v4br, v4cr;
    MultMatrix44Vec4(&transform, &v4a, &v4ar);
    MultMatrix44Vec4(&transform, &v4b, &v4br);
    MultMatrix44Vec4(&transform, &v4c, &v4cr);

    ClearFrameBuffer(renderFrame, 0);
    RasterizeTriange(renderFrame, 
                    &(Vec2){v4ar.x, v4ar.y}, 
                    &(Vec2){v4br.x, v4br.y},
                    &(Vec2){v4cr.x, v4cr.y});
    
    angle += 0.05f;
}


int
main(void)
{
    initscr();
    raw();
    noecho();
    curs_set(0);
    start_color();
    cbreak();

    frameBuffers = RasterizerInit(WinWidth, WinHeight, RenderCallback);
    SwapBuffers(&presentFrame, &renderFrame, frameBuffers, &currentFrameBuffer);
   
    while (true)
    {
        PrintFrameBuffer(presentFrame);
        //ClearFrameBuffer(presentFrame, 0);
        SwapBuffers(&presentFrame, &renderFrame, frameBuffers, &currentFrameBuffer);
        refresh();
        erase();
    }

    RasterizerFree(&frameBuffers);
    endwin();

    return 0;
}