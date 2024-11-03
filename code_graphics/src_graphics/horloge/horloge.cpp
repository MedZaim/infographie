//
// Created by lenovo on 02/11/2024.

#include "./../../includs/graphics_utils.h"
#include "./../bresenhame/bresenham_cercle.cpp"
#include "./../bresenhame/bresenham_line.cpp"
#include <cmath>
#include <iostream>
#include <ctime>

//how to get the current time from the system
//https://www.tutorialspoint.com/c_standard_library/c_function_localtime.htm
//https://www.tutorialspoint.com/c_standard_library/c_function_time.htm



std::time_t printCurrentTime() {
    // Get the current time
    std::time_t now = std::time(nullptr);
    return now;
}


void clock_(int xc = 0, int yc = 0, int r = 200, int color = 15, int color_h_h = GREEN, int color_h_m = BLUE,
            int color_h_s = RED, int bk_color = 5) {
    int h = 0, m = 0, s = 0, xh = 0, yh = 0, xm = 0, ym = 0, xs = 0, ys = 0, xh_ = 0, yh_ = 0, xm_ = 0, ym_ = 0, xs_ = 0, ys_ = 0;
    bresenham_full_cercle(xc, yc, r + 12, r + 6, color);
    int rs = r - .2 * r;
    int rm = r - .3 * r;
    int rh = r - .5 * r;

    for (int i = 0; i < 60; i++) {
        int x1, y1;
        int x2 = r * sin((i / 60.0) * 2 * PI);
        int y2 = r * cos((i / 60.0) * 2 * PI);
        if (i % 5 == 0) {
            x1 = (r - 20) * sin((i / 60.0) * 2 * PI);
            y1 = (r - 20) * cos((i / 60.0) * 2 * PI);
            if (i % 15 == 0)
                bresenham_line(x1 + xc, y1 + yc, x2 + xc, y2 + yc, color, 13);
            else
                bresenham_line(x1 + xc, y1 + yc, x2 + xc, y2 + yc, color, 9);
        } else {
            x1 = (r - 10) * sin((i / 60.0) * 2 * PI);
            y1 = (r - 10) * cos((i / 60.0) * 2 * PI);
            bresenham_line(x1 + xc, y1 + yc, x2 + xc, y2 + yc, color, 1);
        }


    }
    while (true) {
        std::time_t now = printCurrentTime();
        std::tm *localTime = std::localtime(&now);
        h = localTime->tm_hour;
        m = localTime->tm_min;
        s = localTime->tm_sec;


        xh = rh * sin((h / 12.0) * 2 * PI);
        yh = rh * cos((h / 12.0) * 2 * PI);

        xm = rm * sin((m / 60.0) * 2 * PI);
        ym = rm * cos((m / 60.0) * 2 * PI);

        xs = rs * sin((s / 60.0) * 2 * PI);
        ys = rs * cos((s / 60.0) * 2 * PI);


        bresenham_line(xc, yc, xh_+xc, yh_+yc, bk_color, 13);
        bresenham_line(xc, yc, xh+xc, yh+yc, color_h_h, 13);

        bresenham_line(xc, yc, xm_+xc, ym_+yc, bk_color, 9);
        bresenham_line(xc, yc, xm+xc, ym+yc, color_h_m, 9);

        bresenham_line(xc, yc, xs_+xc, ys_+yc, bk_color, 5);
        bresenham_line(xc, yc, xs+xc, ys+yc, color_h_s, 5);

        xh_ = xh;
        yh_ = yh;
        xm_ = xm;
        ym_ = ym;
        xs_ = xs;
        ys_ = ys;

    }
}

int main() {
    init_graph_();
    int X_MAX = 640, Y_MAX = 480;
    setbkcolor(5);
    repere(X_MAX / 2, Y_MAX / 2);
    clock_(100, 100, 100, 15);
    printCurrentTime();
    getch();
}

