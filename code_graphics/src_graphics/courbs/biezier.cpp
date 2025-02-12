#include <graphics.h>
#include <iostream>
#include <cmath>

using namespace std;

// Fonction pour calculer les points d'une courbe de Bézier linéaire
void bezierLinear(int x0, int y0, int x1, int y1) {
    for (float t = 0; t <= 1; t += 0.001) {
        float x = (1 - t) * x0 + t * x1;
        float y = (1 - t) * y0 + t * y1;
        putpixel(x, y, WHITE);
    }
}

// Fonction pour calculer les points d'une courbe de Bézier quadratique
void bezierQuadratic(int x0, int y0, int x1, int y1, int x2, int y2) {
    for (float t = 0; t <= 1; t += 0.001) {
        float x = pow(1 - t, 2) * x0 + 2 * (1 - t) * t * x1 + pow(t, 2) * x2;
        float y = pow(1 - t, 2) * y0 + 2 * (1 - t) * t * y1 + pow(t, 2) * y2;
        putpixel(x, y, WHITE);
    }
}

// Fonction pour calculer les points d'une courbe de Bézier cubique
void bezierCubic(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3) {
    for (float t = 0; t <= 1; t += 0.001) {
        float x = pow(1 - t, 3) * x0 + 3 * pow(1 - t, 2) * t * x1 + 3 * (1 - t) * pow(t, 2) * x2 + pow(t, 3) * x3;
        float y = pow(1 - t, 3) * y0 + 3 * pow(1 - t, 2) * t * y1 + 3 * (1 - t) * pow(t, 2) * y2 + pow(t, 3) * y3;
        putpixel(x, y, WHITE);
    }
}

int main() {
    // Initialisation de la fenêtre graphique
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char *) "");

    // Points de contrôle pour la courbe de Bézier linéaire
    int x0_linear = 100, y0_linear = 100; // Point de départ
    int x1_linear = 400, y1_linear = 100; // Point d'arrivée

    // Points de contrôle pour la courbe de Bézier quadratique
    int x0_quad = 100, y0_quad = 200;
    int x1_quad = 200, y1_quad = 50;
    int x2_quad = 400, y2_quad = 200;

    // Points de contrôle pour la courbe de Bézier cubique
    int x0_cubic = 100, y0_cubic = 300;
    int x1_cubic = 200, y1_cubic = 150;
    int x2_cubic = 400, y2_cubic = 450;
    int x3_cubic = 500, y3_cubic = 300;

    int color_courb = 13;
    int color_ponit = YELLOW;

    setcolor(color_ponit);
    circle(x0_linear, y0_linear, 5);
    circle(x1_linear, y1_linear, 5);
    getch();

    setcolor(color_courb);
    // Dessiner les courbes de Bézier
    bezierLinear(x0_linear, y0_linear, x1_linear, y1_linear); // Linéaire
    getch();

    setcolor(color_ponit);
    // Points de contrôle pour la courbe quadratique
    circle(x0_quad, y0_quad, 5);
    circle(x1_quad, y1_quad, 5);
    circle(x2_quad, y2_quad, 5);
    getch();
    setcolor(color_courb);
    bezierQuadratic(x0_quad, y0_quad, x1_quad, y1_quad, x2_quad, y2_quad); // Quadratique

    getch();

    setcolor(color_ponit);
    // Points de contrôle pour la courbe cubique
    circle(x0_cubic, y0_cubic, 5);
    circle(x1_cubic, y1_cubic, 5);
    circle(x2_cubic, y2_cubic, 5);
    circle(x3_cubic, y3_cubic, 5);

    getch();
    setcolor(color_courb);
    bezierCubic(x0_cubic, y0_cubic, x1_cubic, y1_cubic, x2_cubic, y2_cubic, x3_cubic, y3_cubic); // Cubique


    getch();
    closegraph();
    return 0;
}
/*


 */