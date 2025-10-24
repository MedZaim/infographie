# include "../../Graphics/graphics.h"
# include <cmath>

#ifndef PI
#define PI 3.14159265358979323846
#endif


using namespace std;

void ellipse_teta(int xc, int yc, int a, int b, double teta) {
    double x, y, x1, y1;
    for (double i = 0; i < 360; i += 0.009) {

        x = a * cos(i * PI);
        y = b * sin(i * PI);

        x1 = x * cos(teta) + y * -sin(teta);
        y1 = x * sin(teta) + y * cos(teta);
        putpixel((int) x1 + xc, (int) y1 + yc, WHITE);

    }
}

void fleur(int xc = 100, int yc = 180, int r = 50, int a = 100, int b = 50) {
    circle(xc, yc, r);
    // Dessiner les ellipses
    for (double angle = 0; angle < 2 * PI; angle += PI / 3) {

        int x = (r + a) * cos(angle);
        int y = (r + a) * sin(angle);
        ellipse_teta(x + xc, y + yc, a, b, angle);
    }
}

int main() {
    // Open a titled window instead of legacy initgraph
    initwindow(800, 600, "Fleur - Correction Ex2 (ellipses teta)");
    fleur(getmaxx() / 2, getmaxy() / 2,50, 100,50);
    getch();
    closegraph();
    return 0;
}