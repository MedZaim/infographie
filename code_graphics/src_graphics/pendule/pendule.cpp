//
// Created by lenovo on 11/11/2024.
//
#include "../../includs/graphics_utils.h"
#include <conio.h>
#include <chrono>


void pendule(int t0, point_t C, int r = 100, double f = 1.0 / 4.0, double a = 1 / 10, double teta_m = PI / 3) {
    line_bresenham({C[0] - 15, C[1]}, {C[0] + 15, C[1]}, 15, 9);
    double x, y, x_, y_;
    double teta;
    long long t;
    while (true) {
        long long t1 = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();

        t = (double)(t1 - t0) / 1000.0;
        cout << "t0=" << t0 << "     "<< "t1=" << t1 << "     " << "t=" << t << endl;
        teta = (teta_m * exp(-a * t)) * cos(2 * PI * f * t) - PI / 2;

        x = r * cos(teta);
        y = r * sin(teta);


        x_ = x;
        y_ = y;
        line_bresenham({x + C[0], y + C[1]}, C, 15, 1);
        delay(10);
        break;
        line_bresenham({x_ + C[0], y_ + C[1]}, C, 0, 1);
    }
}

int main() {
    initwindow(640, 480, "Pendule");
    int X_MAX = 640, Y_MAX = 480;
    long long t0  = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();
    point_t C = {100, 100};
    double x, y;
    double angle = PI / 2;
    int r = 100;
    while (true) {
        x = r * cos(angle);
        y = r * sin(angle);
        pendule(t0, {x, y}, 80);
        angle += PI / 180;
        cleardevice();
    }
    pendule(t0, C, 80);
    getch();

    return 0;
}
