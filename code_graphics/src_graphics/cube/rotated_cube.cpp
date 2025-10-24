#include <iostream>
#include <math.h>
#include <graphics.h>
#include "../includs/graphics_utils.h"

#define PI 3.141592653589793

void initialisation_graph() {
    // Show instruction in the window title
    initwindow(800, 700, "Dessin de cube en projection - Appuyez sur une touche pour continuer");
}

void tracer(int x, int y, int color) {
    x = x + getmaxx() / 2;
    y = getmaxy() / 2 - y;
    putpixel(x, y, color);
}

void polynomiale_ligne(int xd, int yd, int xf, int yf) {
    int dx = xf - xd;
    int dy = yf - yd;

    int steps = std::max(abs(dx), abs(dy));
    float x_inc = dx / (float) steps;
    float y_inc = dy / (float) steps;

    float x = xd;
    float y = yd;

    for (int i = 0; i <= steps; i++) {
        tracer(round(x), round(y), WHITE);
        x += x_inc;
        y += y_inc;
    }
}

void repere() {
    cleardevice();
    setcolor(YELLOW);

    // X-axis
    polynomiale_ligne(-400, 0, 400, 0);
    outtextxy(getmaxx() - 50, getmaxy() / 2, "X");

    // Y-axis
    polynomiale_ligne(0, -350, 0, 350);
    outtextxy(getmaxx() / 2, 10, "Y");

    // Z-axis
    polynomiale_ligne(0, 0, -300, -300);
    outtextxy(getmaxx() / 2 - 300, getmaxy() / 2 + 50, "Z");
}



void draw_cube(const matrix_t cube, double k, double h) {
    // Points labels
    const char *labels[8] = {"A", "B", "C", "D", "E", "F", "G", "H"};

    for (int i = 0; i < 8; i++) {
        outtextxy(cube[i][0] + k, h - cube[i][1], (char *) labels[i]);
    }

    // Draw edges
    int edges[12][2] = {
            {0, 1},
            {1, 2},
            {2, 3},
            {3, 0}, // Bottom face
            {4, 5},
            {5, 6},
            {6, 7},
            {7, 4}, // Top face
            {0, 5},
            {1, 6},
            {2, 7},
            {3, 4}  // Vertical edges
    };

    for (auto &edge: edges) {
        line(cube[edge[0]][0] + k, h - cube[edge[0]][1],
             cube[edge[1]][0] + k, h - cube[edge[1]][1]);
    }
}


void animate_cube_rotation( matrix_t cube, double k, double h) {
    double angle = 0.09;

    while (true) {
        cube = rotation_x(cube, angle);
        draw_cube(cube*Tcb, k, h);
        delay(50);
        cleardevice();
        repere();
    }
}

int main() {
    initialisation_graph();
    repere();

    double k = getmaxx() / 2.0;
    double h = getmaxy() / 2.0;

    matrix_t cube = {
            {0,   0,   0,    1},
            {150, 0,   0,    1},
            {150, 150, 0,    1},
            {0,   150, 0,    1},
            {0,   150, -150, 1},
            {0,   0,   -150, 1},
            {150, 0,   -150, 1},
            {150, 150, -150, 1}
    };

    animate_cube_rotation(cube, k, h);

    getch();
    closegraph();
    return 0;
}
