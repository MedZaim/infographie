#include ".\..\..\includs\graphics_utils.h"
#include <cmath>

// Bresenham's line algorithm with float correction
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

    // Define window size
    int X_MAX = 640, Y_MAX = 480;

    repere(X_MAX / 2, Y_MAX / 2);

    // Draw a line from (50, 50) to (80, 80)
    ligne_polynomial(50, 50, 80, 80, 4); // 4 represents RED

    getch();
    closegraph();
    return 0;
}
*/
