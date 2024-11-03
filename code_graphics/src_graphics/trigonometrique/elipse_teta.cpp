
#include "../../includs/graphics_utils.h"
#include <cmath>

Point rotation(Point p, double teta) {
    return {static_cast<int>((p.x * cos(teta) - p.y * sin(teta))),static_cast<int>((p.x * sin(teta) + p.y * cos(teta)))};
}

void elipse_teta(int a, int b, int xc = 0, int yc = 0, double teta = 0, int color = 15) {
        int x;
        int y;
        Point p = rotation({x, y}, teta);
        for (double i = 0; i <  2*PI; i =i+ 0.03) {
            x = a * cos(i * PI);
            y = b * sin(i * PI);

            p = rotation({x, y}, teta);
            pixel9(p.x + xc, p.y + yc, color);
        }

}
void elipse_teta_full(int a, int b, int xc = 0, int yc = 0, double teta = 0, int color = 15) {
    for (int b_=b; b_>=0; b_-=3) {
        elipse_teta(a, b_, xc, yc, teta, color);
    }
}

/*
int main() {
    init_graph_();
    int X_MAX = 640, Y_MAX = 480;
    setbkcolor(5);
    repere(X_MAX / 2, Y_MAX / 2);

    elipse_teta(200, 100,50,60,PI/4);
    double teta= 0.5;
    while(true){
        elipse_teta_full(20, 10,50,60,teta);
        cleardevice();
        teta += 0.1;
    }
    // xc and yc centered in window, color set to 15
    getch();
}

*/

