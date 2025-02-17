//
// Created by lenovo on 06/11/2024.
//
#include "../../includs/graphics_utils.h"

#include <iostream>

void draw_mouse(int color = 15, int lw = 5) {
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

                pixel(x, y, color,lw);
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}

int main() {
 initwindow( 640 ,480, "Mouse draw");

    setbkcolor(5);
    draw_mouse(WHITE,9);

    getch();
    closegraph();
    return 0;
}