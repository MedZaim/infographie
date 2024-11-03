#include ".\..\..\includs\graphics_utils.h"
#include <cmath>




void ellipse_trigonometrique(int a, int b, int xc, int yc, int color) {
    int x;
    int y;
    for (double i = 0; i <  2*PI; i =i+ 0.002) {
        x = a * cos(i*PI);
        y = b * sin(i*PI);
        pixel(x + xc, y + yc, color);

    }
}

/*
int main() {
    init_graph();
    int X_MAX = 640, Y_MAX = 480;
    cleardevice();
    setbkcolor(5);
    repere(X_MAX / 2, Y_MAX / 2);

    ellipse_trigonometrique(30,50,10, 30, 15);
    ellipse_trigonometrique(200,60, -70, -40, 15);

    getch();
}*/
