#include "../../includs/graphics_utils.h"


// The main display function
void bresenham_cercle(int xc, int yc, int r, int color,int wl=13) {
    int x = 0;
    int y = r;
    int s = 3 - 2 * r;


    for (int i = 1; x <= y; i++) {

        pixel(x + xc, y + yc, color,wl); // Draw pixel5 at (x, y)
        pixel(-x + xc, y + yc, color, wl);
        pixel(x + xc, -y + yc, color, wl);
        pixel(-x + xc, -y + yc, color, wl);

        pixel(y + xc, x + yc, color, wl); // Draw pixel5 at (x, y)
        pixel(-y + xc, x + yc, color, wl);
        pixel(y + xc, -x + yc, color, wl);
        pixel(-y + xc, -x + yc, color, wl);
        if (s > 0) {
            s += 4 * (x - y) + 10;
            x += 1;
            y -= 1;
        } else {
            s += 4 * x + 6;
            x += 1;
        }

    }
}

void bresenham_full_cercle(int xc, int yc, int r2, int r1 = 0, int color = 15,int lw=13) {
    for (int i = r1; i <= r2; i+=1) {
        bresenham_cercle(xc, yc, i, color,lw);

    }
}


//#ifdef TEST_BRESENHAM_CERCLE
int main()
{
    // Initialize the graphics system
    init_graph_();
    // tille de fenitre
    int X_MAX = 640, Y_MAX = 480;
    setbkcolor(5);
    bresenham_cercle(40, 40, 80, BLUE);
    repere(X_MAX / 2, Y_MAX / 2);
    int a = 0;
    int rr = 200;
    bresenham_full_cercle(200, 100, 80, 10, 15, 1);
    // Draw a line from (50, 50) to (200, 150)
    bresenham_cercle(200, 100, 80, 10);
    getch();

    while (true)
    {
        int xx = rr * sin(a * 0.01);
        int yy = rr * cos(a * 0.01);

        bresenham_cercle(xx, yy, 80, BLUE);
        Sleep(20);
        repere(X_MAX / 2, Y_MAX / 2);
        a++;
    }
}
//#endif