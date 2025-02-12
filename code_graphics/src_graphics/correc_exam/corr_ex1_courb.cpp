//
// Created by lenovo on 29/01/2025.
//
#include <graphics.h>
#include <iostream>
#include <cmath>

using namespace std;

// Fonction pour calculer les coefficients binomiaux
int binomialCoefficient(int n, int k) {
    if (k == 0 || k == n)
        return 1;
    return binomialCoefficient(n - 1, k - 1) + binomialCoefficient(n - 1, k);
}

// Fonction pour calculer les points de la courbe de Bézier
void bezierCurve(int x[], int y[], int n) {
    double t;
    for (t = 0.0; t <= 1.0; t += 0.0005) {
        double xt = 0.0, yt = 0.0;
        for (int i = 0; i < n; i++) {
            double blend = binomialCoefficient(n - 1, i) * pow(t, i) * pow(1 - t, n - 1 - i);
            xt += x[i] * blend;
            yt += y[i] * blend;
        }
        putpixel(xt, yt, WHITE);
    }
}

int main() {
    int gd = DETECT, gm;
    initwindow(640, 200, "Bezier Curve");

    // Points de contrôle de la courbe de Bézier
    int x[] = {0, 200, 300, 350, 450, 600};
    int y[] = {0, 100, 0, 75, 120, 0};
    int n = sizeof(x) / sizeof(x[0]);

    setcolor(YELLOW);
    //tracer les points
    for(int i=0;i<=5;i++){
        circle(x[i], y[i], 5);
        //label B_0 B_1 B_2 B_3 B_4
        char label[3];
        sprintf(label, "B_%d", i);
        outtextxy(x[i], y[i]+4, label);
    }
    setcolor(WHITE);
    // Tracer la courbe de Bézier
    bezierCurve(x, y, n);

    getch();
    closegraph();
    return 0;
}