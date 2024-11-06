#include "graphics.h"
#include <cmath>
#include <iostream>

#define PI 3.14159265358979323846

class Point {
public:
    int x, y;

    Point() {}

    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }

    Point rotation( double teta=0,Point C={0,0}) {
        int x_ = (this->x-C.x ) * cos(teta) - ( this->y-C.y ) * sin(teta) + C.x;
        int y_ = (this->x-C.x) * sin(teta) + ( this->y-C.y )* cos(teta) + C.y ;
        return {x_, y_};
    }
};

Point rotation(Point p, double teta) {
    int x_ = p.x * cos(teta) - p.y * sin(teta);
    int y_ = p.x * sin(teta) + p.y * cos(teta);
    return {x_, y_};
}

void init_graph_() {
    int g = DETECT, m;
    initgraph(&g, &m, (char *) "");
}

void repere(int xc, int yc) {
    int xm = getmaxx() / 2;
    int ym = getmaxy() / 2;
    line(xc - xm, yc + 0, xc + xm, yc + 0);
    line(xc + 0, yc - ym, xc + 0, yc + ym);

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
