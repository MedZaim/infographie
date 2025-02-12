#include <cmath>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <graphics.h>
#include <stdlib.h>
#include "../../includs/graphics_utils.h"


void init_graph() {
    int g = DETECT, m;
    initgraph(&g, &m, (char *) "C:\\TC\\BGI");
}

void repere() {
    setcolor(5);
    line(320, 240, 640, 240);
    line(320, 240, 320, 0);
    line(320, 240, 0, 560);
}

vector_t findIntersection(const vector_t &vecteur1, const vector_t &vecteur2) {
    vector_t result(2);
    result[0] = (vecteur2[1] - vecteur1[1]) / (vecteur1[0] - vecteur2[0]);
    result[1] = vecteur1[0] * result[0] + vecteur1[1];
    return result;
}

vector_t findIntersection(double x1, double y1, double x2, double y2) {
    vector_t vecteur(2);
    vecteur[0] = (y2 - y1) / (x2 - x1);
    vecteur[1] = y1 - vecteur[0] * x1;
    return vecteur;
}

void tracer_points_de_fuit(matrix_t resRot, int color = 15, int lw = 1) {
    vector_t vecteur01 = findIntersection(resRot[0][0], resRot[0][1], resRot[3][0], resRot[3][1]);
    vector_t vecteur02 = findIntersection(resRot[4][0], resRot[4][1], resRot[7][0], resRot[7][1]);
    vector_t resultat = findIntersection(vecteur01, vecteur02);

    line_bresenham(resRot[0][0], resRot[0][1], resultat[0], resultat[1], WHITE, lw);
    line_bresenham(resRot[4][0], resRot[4][1], resultat[0], resultat[1], WHITE, lw);
    line_bresenham(resRot[1][0], resRot[1][1], resultat[0], resultat[1], WHITE, lw);
    line_bresenham(resRot[5][0], resRot[5][1], resultat[0], resultat[1], WHITE, lw);

    vector_t vecteur11 = findIntersection(resRot[0][0], resRot[0][1], resRot[4][0], resRot[4][1]);
    vector_t vecteur12 = findIntersection(resRot[3][0], resRot[3][1], resRot[7][0], resRot[7][1]);
    vector_t resultat1 = findIntersection(vecteur11, vecteur12);

    line_bresenham(resRot[0][0], resRot[0][1], resultat1[0], resultat1[1], WHITE, lw);
    line_bresenham(resRot[3][0], resRot[3][1], resultat1[0], resultat1[1], WHITE, lw);
    line_bresenham(resRot[1][0], resRot[1][1], resultat1[0], resultat1[1], WHITE, lw);
    line_bresenham(resRot[5][0], resRot[5][1], resultat1[0], resultat1[1], WHITE, lw);

    vector_t vecteur21 = findIntersection(resRot[0][0], resRot[0][1], resRot[1][0], resRot[1][1]);
    vector_t vecteur22 = findIntersection(resRot[6][0], resRot[6][1], resRot[7][0], resRot[7][1]);
    vector_t resultat2 = findIntersection(vecteur21, vecteur22);

    line_bresenham(resRot[6][0], resRot[6][1], resultat2[0], resultat2[1], WHITE, lw);
    line_bresenham(resRot[0][0], resRot[0][1], resultat2[0], resultat2[1], WHITE, lw);
    line_bresenham(resRot[3][0], resRot[3][1], resultat2[0], resultat2[1], WHITE, lw);
    line_bresenham(resRot[7][0], resRot[7][1], resultat2[0], resultat2[1], WHITE, lw);
}


int main() {
    // Initialize the graphics library and create a graphical window
    init_graph();
    initwindow(800, 500, "Graphics Window");

    // Center de projection
    double a = 1, b = 1, c = 1;

    // Plan de projection
    double x0 = 1, y0 = 1, z0 = 1; // Poin de plan de projection
    double n1 = 1, n2 = 1, n3 = 100; // Vecteur normal

    double d0 = n1 * x0 + n2 * y0 + n3 * z0;
    double d = n1 * a + n2 * b + n3 * c;



    // Define the vertices of a 3D cube in homogeneous coordinates (x, y, z, w)
    matrix_t cube = {
            {0,   0,   0,   1}, // Vertex A
            {200, 0,   0,   1}, // Vertex B
            {200, 200, 0,   1}, // Vertex C
            {0,   200, 0,   1}, // Vertex D
            {0,   0,   200, 1}, // Vertex E
            {200, 0,   200, 1}, // Vertex F
            {200, 200, 200, 1}, // Vertex G
            {0,   200, 200, 1} // Vertex H
    };


   // cube = rotation_x(cube, PI/6);
    //cube = rotation_y(cube, PI/6);
    Tracer_cube(cube);
    getch();
    cube = rotation_x(cube, PI/6);
    cube = rotation_y(cube, PI/6);
    matrix_t cube_transformd = perspective(cube , a, b, c, x0, y0, z0, n1, n2, n3);

    //matrix_t cube_transformd = cube * get_perspective_calculated_matrix(a, b, c, x0, y0, z0, n1, n2, n3);
    cleardevice();
    cube_transformd = scaling(cube_transformd, 1, 1, 1);

    Tracer_cube(cube_transformd);
    affiche(cube_transformd);
    getch();
    return 0;
}

/*
    // Step 1: Initial translation to the origin
    matrix_t T_pv = {
            {1 + a * n1 / d, b * n1 / d,     c * n1 / d,     n1 / d},
            {a * n2 / d,     1 + b * n2 / d, c * n2 / d,     n2 / d},
            {a * n3 / d,     b * n3 / d,     1 + c * n1 / d, n1 / d},
            {a - a * d0 / d, b - b * d0 / d, c - c * d0 / d, 1}  // Corrected fourth row
    };
*/
/*

    // Step 1: Initial translation to the origin
    matrix_t T_trans_to_origin = {
            {1,  0,  0,  0},
            {0,  1,  0,  0},
            {0,  0,  1,  0},
            {-a, -b, -c, 1}
    };

    // Perspective projection matrix from origin
    matrix_t T_perspective_from_origin = {
            {1, 0, 0, n1 / d0},
            {0, 1, 0, n2 / d0},
            {0, 0, 1, n3 / d0},
            {0, 0, 0, 1}
    };

    // Step 5: Inverse of the initial translation to return to original space
    matrix_t T_trans_Inverse = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {a, b, c, 1}
    };
*/
