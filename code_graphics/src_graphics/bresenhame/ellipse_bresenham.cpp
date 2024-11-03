#include "../../includs/graphics_utils.h"
#include <graphics.h>
#include <iostream>
#include <cmath>

void ellipse_bresenham(int a, int b, int xc = 0, int yc = 0, int color = 15) {
    int x = 0, y = b;
    int s1 = 2*b * b - 2*a * a * b + a * a;  // Initial decision parameter for Region 1
    int s2;


    while (y > 0 && x < a) {
        if (a * a * (y ) > b * b * (x )) {// First Region
            std::cout << "// Region I" << std::endl;
            pixel(x + xc, y + yc, color);
            pixel(-x + xc, y + yc, color);
            pixel(x + xc, -y + yc, color);
            pixel(-x + xc, -y + yc, color);

            if (s1 > 0) {
                s1 += b * b * (4 * x + 6) +  a * a * (-4 * y + 4);
                x++;
                y--;

            } else {
                s1 += b * b * (4 * x + 6);
                x++;
            }
        } else {
            s2 = b * b * (x ) * (x ) + a * a * (y ) * (y ) - a * a * b * b;
            while (y >= 0) {
                std::cout << "// Region II" << std::endl;
                pixel(x + xc, y + yc, color);
                pixel(-x + xc, y + yc, color);
                pixel(x + xc, -y + yc, color);
                pixel(-x + xc, -y + yc, color);

                if (s2 < 0) {
                    s2 += 2 * b * b * x - 2 * a * a * y + a * a;
                    x++;
                    y--;
                } else {
                    s2 += a * a * (-2 * y + 3);
                    y--;
                }
            }
        }

    }
}

int main() {
    init_graph();
    int X_MAX = 640, Y_MAX = 480;
    setbkcolor(5);
    repere(X_MAX / 2, Y_MAX / 2);
    ellipse_bresenham(300, 200);  // xc and yc centered in window, color set to 15

    getch();
}












/*
#include "../../includs/graphics_utils.cpp"
#include <graphics.h>
#include <iostream>
#include <cmath>

void ellipse_bresenham(int a, int b, int xc=0, int yc=0, int color=15) {
    double s1 = 0, s2 = 0;

    int x = 0;
    int y = b;
    s1 = 2 * b * b - 2 * a * a * b - 2 * a * a;
    int i = 0, j;

    while (true) {
        if (a * a * (y - 1) > b * b * (x + 1)) {
            s2 = b * b * (x + 1) * (x + 1) + a * a * (y - 1) * (y - 1) - a * a * b * b;
            j = 1;
            while (true) {
                if (y > 0) {
                    if (s2 < 0) {
                        s2 += 2 * b * b * x + 3 + a * a * (-2 * y + 3);
                        y--;
                        x++;
                    } else {
                        s2 += a * a * (-2 * y + 3);
                        y--;
                    }
                    j++;
                } else {
                    x++;
                    y--;
                    break;
                }
            }
        } else {
            if (s1 > 0) {
                s1 += b * b * (4 * x + 6) + a * a * (-4 * y + 4);
                x++;
                y--;
            } else {
                s1 += b * b * (4 * x + 6);
                x++;
            }
            i++;
        }
        pixel(x + xc, y + yc, color);
        pixel(-x + xc, y + yc, color);
        pixel(x + xc, -y + yc, color);
        pixel(-x + xc, -y + yc, color);

        if (x >= a && y <= 0) {
            break;
        }
    }
}
int main() {
    init_graph();
    int X_MAX = 640, Y_MAX = 480;
    setbkcolor(5);
    repere(X_MAX / 2, Y_MAX / 2);
    ellipse_bresenham(80, 40);

    getch();
}*/
