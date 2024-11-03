//#include "../../includs/graphics_utils.h"



// Bresenham's line algorithm
void bresenham_line(int x1, int y1, int x2, int y2, int color = 15, int lw = 1) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int px = (dx > 0) ? 1 : -1;
    int py = (dy > 0) ? 1 : -1;
    int x = x1, y = y1;
    dx = abs(dx);
    dy = abs(dy);
    long s;

    if (dx > dy) {
        int i = 0;
        s = 2 * dy - dx;
        while (x != x2) {
            if (s > 0) {
                y += py;
                s += 2 * (dy - dx);
            } else {
                s += 2 * dy;
            }
            x += px;
            pixel(x, y, color, lw);
        }
    } else {
        s = 2 * dx - dy;
        int i = 0;
        while (y != y2) {
            if (s > 0) {
                x += px;
                s += 2 * (dx - dy);
            } else {
                s += 2 * dx;
            }
            y += py;
            pixel(x, y, color, lw);
        }
    }
}

// The main display function
void myline(int xd, int yd, int xf, int yf,int lw=1) {

    bresenham_line(xd, yd, xf, yf,lw); // Draw the line using Bresenham's algorithm
}

#ifdef TEST_BRESENHAM_LINE
int main()
{
    // Initialize the graphics system
    init_graph();

    int X_MAX = 640, Y_MAX = 480;

    repere(X_MAX / 2, Y_MAX / 2);
    int a;

    // Draw a line from (50, 50) to (200, 150)
    myline(50, 50, 200, 150);
    scanf("%d", &a);
    getch();
    closegraph();
    return 0;
}
#endif
