//
// Created by lenovo on 24/11/2024.
//
#include "./../../includs/graphics_utils.h"
#include <conio.h>


// Fonction pour afficher une matrice
void affich_points(matrix_t matrice) {
    for (int i = 0; i < matrice.size(); i++) {
        char label[3] = {(char) ('A' + i), '\0'};
        printf("%s-->", label);

        for (int j = 0; j < 4; j++) {
            printf("%8.2f ", matrice[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


// Fonction pour tracer les arêtes du cube
void Tracer_polyedre(matrix_t points, matrix_t edges, int color) {
    for (int i = 0; i < edges.size(); i++) {
        int p1 = edges[i][0], p2 = edges[i][1];

        // Points 3D
        double x1 = points[p1][0], y1 = points[p1][1], z1 = points[p1][2];
        double x2 = points[p2][0], y2 = points[p2][1], z2 = points[p2][2];

        point_2d_t A = {x1, y1};
        point_2d_t B = {x2, y2};
        line_bresenham(A, B, color);
    }
    // Afficher les étiquettes des sommets
    for (int i = 0; i < points.size(); i++) {
        int x = points[i][0], y = points[i][1], z = points[i][2];

        char label[3] = {(char) ('A' + i), '\0'}; // Nommer les sommets A, B, C...
        outtextxy(x+getmaxx() / 2 ,getmaxy() / 2 - y, label);
    }
}

int
main() {
    initwindow(800, 500, "Polyedre");

    double x = 100, y = 100, z = 100;
    matrix_t points = {
        //  {X, Y, Z, H}
        {0, 0, 0, 1}, // A
        {x, 0, 0, 1}, // B
        {x, y, 0, 1}, // C
        {0, y, 0, 1}, // D
        {0, y, z, 1}, // E
        {0, 0, z, 1}, // F
        {x, 0, z, 1}, // G
        {x, y, z, 1}, // H
        {x/2, y+100, z/2, 1}    // I
    };
    matrix_t edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 5}, {1, 6}, {2, 7}, {3, 4},
         {2,8},{3,8},{4,8},{7,8}
    };

    matrix_t polyedre = points * Tcv;
    Tracer_polyedre(polyedre, edges, 14);

    affich_points(polyedre);
    getch();
    closegraph();
    return 0;
}
