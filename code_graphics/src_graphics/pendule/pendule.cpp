#include "../../includs/graphics_utils.h"
#include <conio.h>
#include <chrono>
#include <iostream>
#include <cmath>

using namespace std;

void pendule(point_t C, int r = 100, double f = 1.0 / 4.0, double a = 1.0 / 10.0, double teta_m = PI / 3, double angular_velocity = PI / 180) {
    double x, y;
    long long t0 = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();

    double angle = 0;

    while (true) {
        // Calculate elapsed time
        long long t1 = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();
        double t = (double)(t1 - t0) / 1000.0;

        angle += angular_velocity;

        double xp = r * cos(angle);
        double yp =  r * sin(angle);

        double Cx = C[0] +xp;
        double Cy = C[1] +yp;

        double teta = (teta_m * exp(-a * t)) * cos(2 * PI * f * t) - PI / 2;

        x = Cx + r * cos(teta);
        y = Cy + r * sin(teta);


        line_bresenham({Cx, Cy},{x, y}, 15, 1);
        line_bresenham({Cx - 15, Cy}, {Cx + 15, Cy}, 9,5);
        delay(10);
        line_bresenham({Cx, Cy},{x, y}, 0, 1);
        line_bresenham({Cx - 15, Cy}, {Cx + 15, Cy}, 0, 5);

        if (kbhit()) {
            break;
        }
    }
}

int main() {

    // This animation listens for a key to stop; indicate that in the title
    initwindow(640, 480, "Pendule - Appuyez sur une touche pour arrêter");

    pendule({0, 0}, 150);

    closegraph();

    return 0;
}