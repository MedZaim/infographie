//
// Created by lenovo on 06/11/2024.
//
#include "./../bresenhame/line_bresenham.cpp"
//#include "../../includs/graphics_utils.h"
#include <iostream>

void ligne_click_mouse() {
    int x1, y1, x2, y2;
    while (true) {
        std::cout << "Click on the first point of the line." << std::endl;

        while (!ismouseclick(WM_LBUTTONDOWN)) {}
        x1 = mousex();
        y1 = mousey();
        clearmouseclick(WM_LBUTTONDOWN);
        std::cout << "First point: (" << x1 << ", " << y1 << ")" << std::endl;

        std::cout << "Click on the second point of the line." << std::endl;
        while (!ismouseclick(WM_LBUTTONDOWN)) {}

        x2 = mousex();
        y2 = mousey();
        clearmouseclick(WM_LBUTTONDOWN);
        std::cout << "Second point: (" << x2 << ", " << y2 << ")" << std::endl;
        x1 -= getmaxx() / 2;
        y1 = getmaxy() / 2 - y1;
        x2 -= getmaxx() / 2;
        y2 = getmaxy() / 2 - y2;
        bresenham_line(x1, y1, x2, y2, 15, 5);
        while (!ismouseclick(WM_LBUTTONDOWN)) {}
    }
}

int main() {
    init_graph_();
    int X_MAX = 640, Y_MAX = 480;
    setbkcolor(5);
    repere(X_MAX / 2, Y_MAX / 2);

    ligne_click_mouse();
/*
    std::cout << "Click anywhere on the window to get the coordinates." << std::endl;

    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int x = mousex();
            int y = mousey();
            std::cout << "Mouse clicked at: (" << x << ", " << y << ")" << std::endl;
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }*/
    getch();
    closegraph();
    return 0;
}