//
// Created by lenovo on 24/11/2024.
//
#include "./../../includs/math_trix.cpp"
#include <graphics.h>
#include "../../includs/chapes.h"
#include <conio.h>
#include <iostream>


// Fonction pour centrer les points 3D
void centre3D(int *X, int *Y, int *Z) {
    int centreX = getmaxx() / 2;
    int centreY = getmaxy() / 2;
    int length = 350;

    // Ajuster les coordonnées X et Y pour centrer le cube
    *X = *X + centreX;
    *Y = centreY - *Y;

    // Calculer la perspective en utilisant le Z
    double facteur = (double)length / (length + *Z); // Facteur de perspective
    *X = (int)(*X * facteur);
    *Y = (int)(*Y * facteur);
}

// Fonction pour afficher une matrice
void afficherMatrice(Matrix<double> matrice) {
    for (int i = 0; i < matrice.size(); i++) {

        char label[3] = {(char)('A' + i), '\0'};
        printf("%s-->",label);

        for (int j = 0; j < 4; j++) {
            printf("%8.2f ", matrice[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}



// Fonction pour tracer les arêtes du cube
void Tracer_polyedre(Matrix<double> points, Matrix<double> edges, int color) {

    for (int i = 0; i < edges.size(); i++) {
        int p1 = edges[i][0], p2 = edges[i][1];

        // Points 3D
        int x1 = points[p1][0], y1 = points[p1][1], z1 = points[p1][2];
        int x2 = points[p2][0], y2 = points[p2][1], z2 = points[p2][2];

        Point A={x1,y1};
        Point B={x2,y2};
        line_bresenham(A,B,color);

    }
    // Afficher les étiquettes des sommets
    for (int i = 0; i < points.size(); i++) {
        int x = points[i][0], y = points[i][1], z = points[i][2];
        centre3D(&x, &y,&z);
        char label[3] = {(char) ('A' + i), '\0'}; // Nommer les sommets A, B, C...
        outtextxy(x, y, label);
    }
}

int
main() {

    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)(""))  ;

    double x = 100, y = 100, z = 100;
    Matrix<double> points = {
            //  {X, Y, Z, H}
            {0, 0, 0, 1},   // A
            {x, 0, 0, 1},   // B
            {x, y, 0, 1},   // C
            {0, y, 0, 1},   // D
            {0, y, z, 1},   // E
            {0, 0, z, 1},   // F
            {x, 0, z, 1},   // G
            {x, y, z, 1} ,   // H
            //{x+50, y+30, z+20, 1}    // I
    };
    Matrix<double> edges= {
            {0, 1}, {1, 2}, {2, 3}, {3, 0},
            {4, 5}, {5, 6}, {6, 7}, {7, 4},
            {0, 5}, {1, 6}, {2, 7}, {3, 4},
           // {2,8},{3,8},{4,8},{7,8}
    };
            Matrix<double> M_Homogine = {
            //  {X, Y, Z, H}
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {sqrt(2)/2, sqrt(2)/2, 0, 0},
            {0,0,0, 1}
    };



    Matrix<double>   polyedre = matrix_multiply(points, M_Homogine);
    Tracer_polyedre(polyedre,edges, 14);
    // repere(getmaxx()/2,getmaxy()/2);
    afficherMatrice(polyedre);
    getch();
    closegraph();
    return 0;
}