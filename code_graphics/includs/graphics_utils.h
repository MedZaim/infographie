#include "graphics.h"

#define PI 3.14159265358979323846
class Point{
public:
    int x,y;
    Point(int x,int y){
        this->x=x;
        this->y=y;
    }
};

void init_graph_() {
    int g = DETECT, m;
    initgraph(&g, &m, (char *) "");
}

void repere(int xc, int yc) {
    cleardevice();
    setbkcolor(5);
    line(xc - 320, yc + 0, xc + 320, yc + 0);
    line(xc + 0, yc - 240, xc + 0, yc + 240);
    setcolor(5);
}

void pixel5(int x, int y, int color) {
    x = x + 320;
    y = 240 - y;
    putpixel(x, y, color);


    putpixel(x + 1, y - 1, color);
    putpixel(x - 1, y + 1, color);


    putpixel(x + 1, y + 1, color);
    putpixel(x - 1, y - 1, color);
}

void pixel9(int x, int y, int color) {
    x = x + 320;
    y = 240 - y;
    putpixel(x, y, color);

    putpixel(x + 1, y, color);
    putpixel(x, y + 1, color);


    putpixel(x - 1, y, color);
    putpixel(x, y - 1, color);


    putpixel(x + 1, y - 1, color);
    putpixel(x - 1, y + 1, color);


    putpixel(x + 1, y + 1, color);
    putpixel(x - 1, y - 1, color);
}
void pixel13(int x, int y, int color) {
    x = x + 320;
    y = 240 - y;
    putpixel(x, y, color);

    putpixel(x + 1, y, color);
    putpixel(x, y + 1, color);
    putpixel(x + 1, y + 1, color);

    putpixel(x - 1, y, color);
    putpixel(x, y - 1, color);
    putpixel(x - 1, y - 1, color);

    putpixel(x + 1, y - 1, color);
    putpixel(x - 1, y + 1, color);

    putpixel(x + 2, y, color);
    putpixel(x, y + 2, color);
    putpixel(x + 2, y + 2, color);

    putpixel(x - 2, y, color);
    putpixel(x, y - 2, color);
    putpixel(x - 2, y - 2, color);

    putpixel(x + 2, y - 2, color);
    putpixel(x - 2, y + 2, color);
}
void pixel(int x, int y, int color, int lw = 1) {


    switch (lw) {
        case 5:
            pixel5(x, y, color);
            break;
        case 9:
            pixel9(x, y, color);
            break;
        case 13:
            pixel13(x, y, color);
            break;
        default:
            x = x + 320;
            y = 240 - y;
            putpixel(x, y, color);
            break;
    }
}
