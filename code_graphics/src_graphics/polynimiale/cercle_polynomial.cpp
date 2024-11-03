#include ".\..\..\includs\graphics_utils.h"
#include <cmath>


void cercle_polynomial(int xc, int yc, int r, int color) {
    double x;
    double y;
    for (int i = 0; x <= r; x += 0.1) {
        y = sqrt(r * r - x * x);
        pixel(x + xc, y + yc, color);
        pixel(-x + xc, y + yc, color);
        pixel(x + xc, -y + yc, color);
        pixel(-x + xc, -y + yc, color);
    }
}

int main() {
    init_graph();
    int X_MAX = 640, Y_MAX = 480;
    cleardevice();
    setbkcolor(5);
    repere(X_MAX / 2, Y_MAX / 2);
    int a = 0;
    int rr = 200;



    cercle_polynomial(10, 30, 80, 15);


    cercle_polynomial(0, 10, 70, 15);
    delay(10);
    getch();
}
/*

int main()
{

    init_graph();
    // tille de fenitre
    int X_MAX = 640, Y_MAX = 480;
    repere(X_MAX / 2, Y_MAX / 2);

    cercle_polynomial(100, 50, 100, YELLOW);

    int a = 0;
    int rr = 200;
    int xx, yy;
    while (a < 999999)
    {
        xx = rr * sin((float)a * 0.2);
        yy = rr * cos((float)a * 0.2);

        ellipse_trigonometrique(xx, yy, 20, YELLOW);
        delay(700);
        repere(X_MAX / 2, Y_MAX / 2);
        a++;
    }

    getch();
    closegraph();
    return 0;
}
*/
