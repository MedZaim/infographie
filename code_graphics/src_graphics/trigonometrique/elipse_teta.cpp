#include "./../bresenhame/bresenham_line.cpp"
//#include "../../includs/graphics_utils.h"
#include <cmath>

Point rotation(Point p, double teta) {
    return {static_cast<int>((p.x * cos(teta) - p.y * sin(teta))),
            static_cast<int>((p.x * sin(teta) + p.y * cos(teta)))};
}

void elipse_teta(int a, int b, int xc = 0, int yc = 0, double teta = 0, int color = 15) {
    int x;
    int y;
    Point p = rotation({x, y}, teta);
    for (double i = 0; i < 2 * PI; i = i + 0.03) {
        x = a * cos(i * PI);
        y = b * sin(i * PI);

        p = rotation({x, y}, teta);
        pixel9(p.x + xc, p.y + yc, color);
    }

}

void elipse_teta_full(int a, int b, int xc = 0, int yc = 0, double teta = 0, int color = 15) {
    for (int b_ = b; b_ >= 0; b_ -= 3) {
        elipse_teta(a, b_, xc, yc, teta, color);
    }
}

void ellipse_full_by_ligne(int a, int b, int xc = 0, int yc = 0, double teta = 0, int color = 15, int lw = 1) {
    int y;
    int x1, y1,x2,y2;

    for (int x = -a; x <= a; x++) {
        y = (int) (b * sqrt(1 - (x * x / (float) (a * a))));

        Point p1 = rotation({x, y}, teta);
        Point p2 = rotation({x, -y}, teta);

        bresenham_line(p1.x + xc, p1.y + yc, p2.x + xc, p2.y + yc, color, lw);
    }

}


int main() {
    init_graph_();
    int X_MAX = 640, Y_MAX = 480;
    setbkcolor(5);
    repere(X_MAX / 2, Y_MAX / 2);
    //elipse_teta_full(200, 100,50,60,PI/4);
    ellipse_full_by_ligne(200, 100,100,100,5*PI/4,15,5);
    ellipse_full_by_ligne(100, 80,-60,-60,5*PI/4,15,5);

    getch();
}



