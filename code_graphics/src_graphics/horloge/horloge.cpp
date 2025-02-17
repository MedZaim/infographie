//
// Created by lenovo on 02/11/2024.

#include "./../../includs/graphics_utils.h"




void Dessine_Cadran_Horloge(int radius, int xc, int yc) {
    for (int i = 0; i < 12; i++) {
        double angle = i * (PI / 6) - PI / 2;
        int x = (int) ((radius) * cos(angle));
        int y = (int) ((radius) * sin(angle));
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        char number[12];
        sprintf(number, "%d", (i == 0) ? 12 : i);
        outtextxy(x + xc + getmaxx() / 2, (y - yc + getmaxy() / 2), number);


    }
}

std::time_t getCurrentTime() {
    // Get the current time
    std::time_t now = std::time(nullptr);
    return now;
}


void clock_(int xc = 0, int yc = 0, int r = 200, int color = 15, int color_h_h = GREEN, int color_h_m = YELLOW,
            int color_h_s = RED, int bk_color = 0) {
    int h = 0, m = 0, s = 0, xh = 0, yh = 0, xm = 0, ym = 0, xs = 0, ys = 0, xh_ = 0, yh_ = 0, xm_ = 0, ym_ = 0, xs_ = 0, ys_ = 0;
    cercle_full_bresenham(xc, yc, r + 55, r + 40, color);
    cercle_full_bresenham(xc, yc, r + 36, r+5 , 14);
    int rs = r - .2 * r;
    int rm = r - .3 * r;
    int rh = r - .5 * r;
    // degrees
    for (int i = 0; i < 60; i++) {
        int x1, y1;
        int x2 = r * sin((i / 60.0) * 2 * PI);
        int y2 = r * cos((i / 60.0) * 2 * PI);
        if (i % 5 == 0) {
            x1 = (r - 20) * sin((i / 60.0) * 2 * PI);
            y1 = (r - 20) * cos((i / 60.0) * 2 * PI);
            if (i % 15 == 0)
                line_bresenham(x1 + xc, y1 + yc, x2 + xc, y2 + yc, color, 13);
            else
                line_bresenham(x1 + xc, y1 + yc, x2 + xc, y2 + yc, color, 9);
        } else {
            x1 = (r - 10) * sin((i / 60.0) * 2 * PI);
            y1 = (r - 10) * cos((i / 60.0) * 2 * PI);
            line_bresenham(x1 + xc, y1 + yc, x2 + xc, y2 + yc, color, 1);
        }


    }
    Dessine_Cadran_Horloge(r+23, xc-9, yc+7);
    while (true) {

        std::time_t now = getCurrentTime();
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


        line_bresenham(xc, yc, xh_ + xc, yh_ + yc, bk_color, 13);
        line_bresenham(xc, yc, xh + xc, yh + yc, color_h_h, 13);

        line_bresenham(xc, yc, xm_ + xc, ym_ + yc, bk_color, 9);
        line_bresenham(xc, yc, xm + xc, ym + yc, color_h_m, 9);

        line_bresenham(xc, yc, xs_ + xc, ys_ + yc, bk_color, 5);
        line_bresenham(xc, yc, xs + xc, ys + yc, color_h_s, 5);

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
    //setbkcolor(5);
    repere(X_MAX / 2, Y_MAX / 2);
    clock_(80, 50, 100, 15);
    //Dessine_Cadran_Horloge(100, 0, 0);
    getch();
}

