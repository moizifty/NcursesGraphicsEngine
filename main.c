#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <ncurses.h>
#include "GraphicsMath/graphicsmath.h"
#include "rasterizer.h"

#define WinHeight (LINES)
#define WinWidth  (COLS)

int
main(void)
{
    initscr();
    raw();
    noecho();
    curs_set(0);
    start_color();
    cbreak();

    FrameBuffer *fb = RasterizerInit(WinWidth / 2, WinHeight / 2);

    float angle = 0;

    while (angle < 1000.0f)
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
        Vec3 rotateAxis = {0, 0, 1};

        //ScaleMatrix44(&transform, &scale);
        RotateMatrix44(&transform, &rotateAxis, DegToRad(-angle));

        Vec4 v4a = {-1, 1, 1, 1};
        Vec4 v4b = {1, 1, 1, 1};
        Vec4 v4c = {0, -1, 1, 1};

        Vec4 v4ar, v4br, v4cr;
        MultMatrix44Vec4(&transform, &v4a, &v4ar);
        MultMatrix44Vec4(&transform, &v4b, &v4br);
        MultMatrix44Vec4(&transform, &v4c, &v4cr);

        ClearFrameBuffer(fb, 0);
        RasterizeTriange(fb, 
                        &(Vec2){v4ar.x, v4ar.y}, 
                        &(Vec2){v4br.x, v4br.y},
                        &(Vec2){v4cr.x, v4cr.y});

        PrintFrameBuffer(fb, 0, 0);
        refresh();
        erase();
        angle += 0.05f;
    }

    RasterizerFree(&fb);
    endwin();

    return 0;
}