#include ".\..\..\includs\graphics_utils.h"
#include <graphics.h>
#include <iostream>

#include <cmath>



void ellipse_polynomial(int a, int b, int xc, int yc, int color)
{
    double x = 0;
    double y = b;
    for (int i = 0; x <= a; x += 0.1)
    {
        y = sqrt(b * b * (1 - (x * x) / (float)(a * a)));
        pixel(x + xc, y + yc, color);
        pixel(-x + xc, y + yc, color);
        pixel(x + xc, -y + yc, color);
        pixel(-x + xc, -y + yc, color);
    }
}
/*

int main()
{

    init_graph();
    // tille de fenitre
    int X_MAX = 640, Y_MAX = 480;
    repere(X_MAX / 2, Y_MAX / 2);

    ellipse_polynomial(100, 50, 100, 100, YELLOW);

    int a = 0;
    int rr = 200;
    int xx, yy;
    while (a < 999999)
    {
        xx = rr * sin((float)a * 0.2);
        yy = rr * cos((float)a * 0.2);

        ellipse_polynomial(20, 30, xx, yy, YELLOW);
        delay(700);
        repere(X_MAX / 2, Y_MAX / 2);
        a++;
    }

    getch();
    closegraph();
    return 0;
}
*/
