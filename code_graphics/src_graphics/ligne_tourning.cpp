#include ".\..\..\includs\graphics_utils.h"
#include <graphics.h>
#include <iostream>
#include <cmath>

// Bresenham's line algorithm
void ligne_polynomial(int xd, int yd, int xf, int yf, int color)
{
    int dx = xf - xd;
    int dy = yf - yd;
    int px = (xf > xd) ? 1 : -1;
    int py = (yf > yd) ? 1 : -1;

    pixel(xd, yd, color);
    pixel(xf, yf, color);

    // Use float for accurate line drawing
    if (abs(dx) >= abs(dy))
    {
        float a = (float)dy / dx; // Slope
        float b = yd - xd * a;    // Intercept
        for (int x = xd + px; x != xf; x += px)
        {
            int y = a * x + b;
            pixel(x, y, color);
        }
    }
    else
    {
        float a = (float)dx / dy; // Slope for steep lines
        float b = xd - yd * a;    // Intercept
        for (int y = yd + py; y != yf; y += py)
        {
            int x = a * y + b;
            pixel(x, y, color);
        }
    }
}
/*

int main()
{
    // Initialize the graphics system
    init_graph();

    // tille de fenitre
    int X_MAX = 640, Y_MAX = 480;
    repere(X_MAX / 2, Y_MAX / 2);

    int a = 0;
    int rr = 200;
    int xx, yy;
    while (a < 999999)
    {
        xx = rr * sin((float)a * 0.02);
        yy = rr * cos((float)a * 0.02);

        ligne_polynomial(xx, yy, 0, 0, YELLOW);
        delay(5); // Used delay instead of Sleep to match graphics library
        // ligne_polynomial(0, 0, xx, yy, BLACK); // Clear the previous circle
        repere(X_MAX / 2, Y_MAX / 2);
        // printf("xx= %d , yy= %d ", xx, yy);
        a++;
    }

    getch();
    closegraph();
    return 0;
}
*/
