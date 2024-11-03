#include "../../includs/graphics_utils.h"


/*
// Draw a circle using Bresenham’s algorithm with a specific color
void bresenham_cercle(int xc, int yc, int r, int color)
{
    int x = 0, y = r, s = 3 - 2 * r;
    while (x <= y)
    {
        pixel(x + xc, y + yc, color);
        pixel(-x + xc, y + yc, color);
        pixel(x + xc, -y + yc, color);
        pixel(-x + xc, -y + yc, color);
        pixel(y + xc, x + yc, color);
        pixel(-y + xc, x + yc, color);
        pixel(y + xc, -x + yc, color);
        pixel(-y + xc, -x + yc, color);

        if (s > 0)
        {
            s += 4 * (x - y) + 10;
            y -= 1;
        }
        else
        {
            s += 4 * x + 6;
        }
        x++;
    }
}*/
#ifdef TEST_CERCLE_TOURNANTE
int main()
{
    init_graph();
    int X_MAX = 640, Y_MAX = 480;
    int a = 0, rr = 200;
    int colorPalette[] = {RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA}; // Color palette
    int colorCount = sizeof(colorPalette) / sizeof(colorPalette[0]);

    // Draw the coordinate axes
    repere(X_MAX / 2, Y_MAX / 2);

    while (a < 999999999999)
    {
        int xx = rr * sin((float)a * 0.05);
        int yy = rr * cos((float)a * 0.05);

        int colorIndex = a % colorCount; // Cycle through colors
        int color = colorPalette[colorIndex];

        bresenham_cercle(xx, yy, 40, YELLOW);
        delay(10);                           // Used delay instead of Sleep to match graphics library
        bresenham_cercle(xx, yy, 40, BLACK); // Clear the previous circle
        repere(X_MAX / 2, Y_MAX / 2);
        // printf("xx= %d , yy= %d ", xx, yy);
        a++;
    }

    getch();
    closegraph();
}
#endif