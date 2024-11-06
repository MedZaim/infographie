//
// Created by lenovo on 06/11/2024.
//
#include "./../bresenhame/line_bresenham.cpp"
//#include "../../includs/graphics_utils.h"

#include <iostream>

void draw_mouse() {
    int x, y;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            while (true) {
                if (ismouseclick(WM_LBUTTONUP)) {
                    clearmouseclick(WM_LBUTTONUP);
                    break;
                }
                x = mousex();
                y = mousey();

                x -= getmaxx() / 2;
                y = getmaxy() / 2 - y;

                pixel9(x, y, 15);
                pixel9(x+3, y, 15);
                pixel9(x, y+3, 15);
                pixel9(x+3, y+3, 15);
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int X_MAX = 640, Y_MAX = 480;
    setbkcolor(5);
    repere(X_MAX / 2, Y_MAX / 2);

    draw_mouse();

    getch();
    closegraph();
    return 0;
}