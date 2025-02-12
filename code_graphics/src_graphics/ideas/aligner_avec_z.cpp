//
// Created by lenovo on 24/12/2024.
//

#include <cmath>
#include<iostream>
#include <stdio.h>
#include <math.h>
#include <graphics.h>
#include <stdlib.h>
#include "../../includs/chapes.h"

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


const double cosin = std::sqrt(2) / 2;

void multiplyMatrices(const double mat1[4][4], const double mat2[4][4], double result[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

void multiplyMatricesCube(const double mat1[8][4], const double mat2[4][4], double result[8][4]) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 4; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

void findIntersection(const double vecteur1[2], const double vecteur2[2], double resultat[2]) {
    resultat[0] = (vecteur2[1] - vecteur1[1]) / (vecteur1[0] - vecteur2[0]);
    resultat[1] = vecteur1[0] * resultat[0] + vecteur1[1];


}

void findVector(double x1, double y1, double x2, double y2, double vecteur[2]) {

    vecteur[0] = (y2 - y1) / (x2 - x1);
    vecteur[1] = y1 - vecteur[0] * x1;
}

void Tracer_cube(double resRot[8][4]) {
    line_bresenham(resRot[0][0], resRot[0][1], resRot[1][0], resRot[1][1], WHITE,5); // A--> B : plan de projection
    line_bresenham(resRot[0][0], resRot[0][1], resRot[3][0], resRot[3][1], WHITE,5); // A--> D
    line_bresenham(resRot[0][0], resRot[0][1], resRot[4][0], resRot[4][1], WHITE,5); // A--> E
    line_bresenham(resRot[1][0], resRot[1][1], resRot[2][0], resRot[2][1], WHITE,5); // B--> C
    line_bresenham(resRot[1][0], resRot[1][1], resRot[5][0], resRot[5][1], WHITE,5); // B--> G
    line_bresenham(resRot[2][0], resRot[2][1], resRot[3][0], resRot[3][1], WHITE,5); // C--> D

    line_bresenham(resRot[2][0], resRot[2][1], resRot[6][0], resRot[6][1], WHITE,5); // C--> H
    line_bresenham(resRot[3][0], resRot[3][1], resRot[7][0], resRot[7][1], WHITE,5); // D--> H
    line_bresenham(resRot[4][0], resRot[4][1], resRot[5][0], resRot[5][1], WHITE,5); // E--> F
    line_bresenham(resRot[4][0], resRot[4][1], resRot[7][0], resRot[7][1], WHITE,5); // E--> H :
    line_bresenham(resRot[5][0], resRot[5][1], resRot[6][0], resRot[6][1], WHITE,5); // F--> G
    line_bresenham(resRot[6][0], resRot[6][1], resRot[7][0], resRot[7][1], WHITE,5); // G--> H
    setcolor(RED);


    double vecteur01[2];
    findVector(resRot[0][0], resRot[0][1], resRot[3][0], resRot[3][1], vecteur01);
    double vecteur02[2];
    findVector(resRot[4][0], resRot[4][1], resRot[7][0], resRot[7][1], vecteur02);
    double resultat[2];

    findIntersection(vecteur01, vecteur02, resultat);

//	for (int i = 0; i < 2; i++){
//		printf("%lf ", resultat[i]) ;
//	}
    line_bresenham(resRot[0][0], resRot[0][1], resultat[0], resultat[1], WHITE);
    line_bresenham(resRot[4][0], resRot[4][1], resultat[0], resultat[1], WHITE);
    line_bresenham(resRot[1][0], resRot[1][1], resultat[0], resultat[1], WHITE);

    double vecteur11[2];
    findVector(resRot[0][0], resRot[0][1], resRot[4][0], resRot[4][1], vecteur11);
    double vecteur12[2];
    findVector(resRot[3][0], resRot[3][1], resRot[7][0], resRot[7][1], vecteur12);
    double resultat1[2];
    findIntersection(vecteur11, vecteur12, resultat1);
//	for (int i = 0; i < 2; i++){
//		printf("%lf ", resultat1[i]) ;
//	}
    line_bresenham(resRot[0][0], resRot[0][1], resultat1[0], resultat1[1], WHITE);
    line_bresenham(resRot[3][0], resRot[3][1], resultat1[0], resultat1[1], WHITE);
    line_bresenham(resRot[1][0], resRot[1][1], resultat1[0], resultat1[1], WHITE);

    double vecteur21[2];
    findVector(resRot[0][0], resRot[0][1], resRot[1][0], resRot[1][1], vecteur21);
    double vecteur22[2];
    findVector(resRot[6][0], resRot[6][1], resRot[7][0], resRot[7][1], vecteur22);
    double resultat2[2];
    findIntersection(vecteur21, vecteur22, resultat2);
//	for (int i = 0; i < 2; i++){
//		printf("%lf ", resultat2[i]) ;
//	}
    line_bresenham(resRot[6][0], resRot[6][1], resultat2[0], resultat2[1], WHITE);
    line_bresenham(resRot[0][0], resRot[0][1], resultat2[0], resultat2[1], WHITE);
    line_bresenham(resRot[3][0], resRot[3][1], resultat2[0], resultat2[1], WHITE);
    line_bresenham(resRot[1][0], resRot[1][1], resultat2[0], resultat2[1], WHITE);

}



int main() {
    // Initialize the graphics library and create a graphical window
    init_graph();
    initwindow(800, 500, "Graphics Window");


    double vector_n[1][4] = {
            {100, 100, 200, 1},
    };


    double tetax = PI/4;
    // Step 2: Rotation around the Y-axis by  angle teta
    double R_x_teta[4][4] = {
            {costetax,0, -sintetax, 0},
            {0, 1, 0, 0},
            {sintetax, 0, costetax,  0},
            {0, 0, 0, 1}
    };



    double phyy = PI/4;
    // Step 2: Rotation around the Y-axis by  angle teta
    double R_y_phyy[4][4] = {
            {1, 0, 0, 0},
            {0, cos(phyy), sin(phyy), 0},
            {0, -sin(phyy), cos(phyy),  0},
            {0, 0, 0, 1}
    };

    // Step 4: Final translation to move the cube to its target position
    double T4[4][4] = {
            {1, 0, 0, 0.4},
            {0, 1, 0, 0.4},
            {0, 0, 0, 0.2},
            {0, 0, 0, 1}
    };

void aligner(double v[1][4] , double n[1][4]) {
    double vecteur01[2];
    findVector(v[0][0], v[0][1], n[0][0], n[0][1], vecteur01);
    double vecteur02[2];
    findVector(v[0][2], v[0][1], n[0][2], n[0][1], vecteur02);
    double resultat[2];

    findIntersection(vecteur01, vecteur02, resultat);

    line_bresenham(v[0][0], v[0][1], resultat[0], resultat[1], WHITE);
    line_bresenham(v[0][2], v[0][1], resultat[0], resultat[1], WHITE);
    line_bresenham(v[0][1], v[0][1], resultat[0], resultat[1], WHITE);

    double vecteur11[2];
    findVector(v[0][0], v[0][1], v[0][2], v[0][1], vecteur11);
    double vecteur12[2];
    findVector(n[0][0], n[0][1], n[0][2], n[0][1], vecteur12);
    double resultat1[2];
    findIntersection(vecteur11, vecteur12, resultat1);

    line_bresenham(v[0][0], v[0][1], resultat1[0], resultat1[1], WHITE);
    line_bresenham(v[0][2], v[0][1], resultat1[0], resultat1[1], WHITE);
    line_bresenham(v[0][1], v[0][1], resultat1[0], resultat1[1], WHITE);

    double vecteur21[2];
    findVector(v[0][0], v[0][1], v[0][2], v[0][1], vecteur21);
    double vecteur22[2];
    findVector(n[0][0], n[0][1], n[0][2], n[0][1], vecteur22);
    double resultat2[2];
    findIntersection(vecteur21, vecteur22, resultat2);

    line_bresenham(n[0][0], n[0][1], resultat2

}



    // Perform matrix multiplications to combine transformations
    double T_t[4][4];
    multiplyMatrices(R_x_teta, R_y_phyy, T_t);  // T1 * T2

    double res2[4][4];
    multiplyMatrices(res1, T3, res2); // (T1 * T2) * T3

    double res3[4][4];
    multiplyMatrices(res2, T4, res3); // ((T1 * T2) * T3) * T4

    double res4[4][4];
    multiplyMatrices(res3, inverse_T1, res4); // Final transformation matrix


    /*   // Apply translation to each vertex
       double cube1[8][4];
       multiplyMatricesCube(cube0, translateDown, cube1);*/



    // Apply the final transformation to the cube's vertices
    double res5[8][4];
    multiplyMatricesCube(cube1, res4, res5);

    // Normalize the homogeneous coordinates and scale to fit the screen
    double res6[8][4];
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 4; ++j) {
            res6[i][j] = (res5[i][j] / res5[i][3]) * 50;
        }
    }

    // Display the transformed vertices for debugging
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << res6[i][j] << "     ";
        }
        std::cout << std::endl;
    }

    // Clear the graphics screen and draw the transformed cube
    cleardevice();

    Tracer_cube(res6);

    getch();
    return 0;
}
