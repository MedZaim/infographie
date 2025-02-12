# include "graphics.h"
# include <cmath>


using namespace std;

void ellipse_teta(int xc, int yc, int a, int b, double teta) {
    double x, y, x1, y1;
    for (double i = 0; i < 360; i += 0.003) {

        x = a * cos(i * M_PI);
        y = b * sin(i * M_PI);

        x1 = x * cos(teta) + y * -sin(teta);
        y1 = x * sin(teta) + y * cos(teta);
        putpixel((int) x1 + xc, (int) y1 + yc, WHITE);

    }
}

void fleur(int xc = 100, int yc = 180, int r = 50, int a = 100, int b = 50) {
    circle(xc, yc, r);
    // Dessiner les ellipses
    for (double angle = 0; angle < 2 * M_PI; angle += M_PI / 3) {

        int x = (r + a) * cos(angle);
        int y = (r + a) * sin(angle);
        ellipse_teta(x + xc, y + yc, a, b, angle);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char *) " ");
    fleur(getmaxx() / 2, getmaxy() / 2,50, 100,50);
    getch();
    closegraph();
    return 0;
}