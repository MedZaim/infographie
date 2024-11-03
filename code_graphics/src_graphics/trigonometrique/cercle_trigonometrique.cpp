#include ".\..\..\includs\graphics_utils.h"
#include <cmath>
#include <iostream>



void cercle_polynomial(int xc, int yc, int r, int color) {
    int x;
    int y;
    for (double i = 0; i <  PI/4; i =i+ 0.002) {
        x = r * cos(i*PI);
        y = r * sin(i*PI);
        pixel(x + xc, y + yc, color);
        pixel(-x + xc, y + yc, color);
        pixel(x + xc, -y + yc, color);
        pixel(-x + xc, -y + yc, color);
        std::cout<<x<<" "<<y<<" "<<"r="<<r<<std::endl;
    }
}
/*

int main() {
    init_graph();
    int X_MAX = 640, Y_MAX = 480;
    cleardevice();
    setbkcolor(5);
    repere(X_MAX / 2, Y_MAX / 2);

    cercle_polynomial(10, 30, 200, 15);
    cercle_polynomial(0, 10, 70, 15);

    getch();
    }
*/
