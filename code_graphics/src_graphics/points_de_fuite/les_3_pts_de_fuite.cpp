#include<iostream>
#include "../../includs/graphics_utils.h"


vector_t findIntersection(const vector_t v1, const vector_t v2) {
    vector_t resultat(2);
    resultat[0] = (v2[1] - v1[1]) / (v1[0] - v2[0]);
    resultat[1] = v1[0] * resultat[0] + v1[1];
    return resultat;
}

vector_t findVector(double x1, double y1, double x2, double y2) {
    vector_t vecteur(2);
    vecteur[0] = (y2 - y1) / (x2 - x1);
    vecteur[1] = y1 - vecteur[0] * x1;
    return vecteur;
}

void tracer_points_de_fuit(matrix_t resRot) {
    vector_t vecteur01 = findVector(resRot[0][0], resRot[0][1], resRot[3][0], resRot[3][1]);
    vector_t vecteur02 = findVector(resRot[4][0], resRot[4][1], resRot[7][0], resRot[7][1]);
    vector_t resultat = findIntersection(vecteur01, vecteur02);


    line_bresenham(resRot[0][0], resRot[0][1], resultat[0], resultat[1], WHITE);
    line_bresenham(resRot[4][0], resRot[4][1], resultat[0], resultat[1], WHITE);
    line_bresenham(resRot[1][0], resRot[1][1], resultat[0], resultat[1], WHITE);
    line_bresenham(resRot[5][0], resRot[5][1], resultat[0], resultat[1], WHITE);


    vector_t vecteur11 = findVector(resRot[0][0], resRot[0][1], resRot[4][0], resRot[4][1]);
    vector_t vecteur12 = findVector(resRot[3][0], resRot[3][1], resRot[7][0], resRot[7][1]);
    vector_t resultat1 = findIntersection(vecteur11, vecteur12);


    line_bresenham(resRot[0][0], resRot[0][1], resultat1[0], resultat1[1], WHITE);
    line_bresenham(resRot[3][0], resRot[3][1], resultat1[0], resultat1[1], WHITE);
    line_bresenham(resRot[1][0], resRot[1][1], resultat1[0], resultat1[1], WHITE);
    line_bresenham(resRot[5][0], resRot[5][1], resultat1[0], resultat1[1], WHITE);

    vector_t vecteur21 = findVector(resRot[0][0], resRot[0][1], resRot[1][0], resRot[1][1]);
    vector_t vecteur22 = findVector(resRot[6][0], resRot[6][1], resRot[7][0], resRot[7][1]);
    vector_t resultat2 = findIntersection(vecteur21, vecteur22);


    line_bresenham(resRot[6][0], resRot[6][1], resultat2[0], resultat2[1], WHITE);
    line_bresenham(resRot[0][0], resRot[0][1], resultat2[0], resultat2[1], WHITE);
    line_bresenham(resRot[3][0], resRot[3][1], resultat2[0], resultat2[1], WHITE);
    line_bresenham(resRot[7][0], resRot[7][1], resultat2[0], resultat2[1], WHITE);
}

void Tracer_cube(double resRot[8][4]) {
    line_bresenham(resRot[0][0], resRot[0][1], resRot[1][0], resRot[1][1], WHITE, 5); // A--> B : plan de projection
    line_bresenham(resRot[0][0], resRot[0][1], resRot[3][0], resRot[3][1], WHITE, 5); // A--> D
    line_bresenham(resRot[0][0], resRot[0][1], resRot[4][0], resRot[4][1], WHITE, 5); // A--> E
    line_bresenham(resRot[1][0], resRot[1][1], resRot[2][0], resRot[2][1], WHITE, 5); // B--> C
    line_bresenham(resRot[1][0], resRot[1][1], resRot[5][0], resRot[5][1], WHITE, 5); // B--> G
    line_bresenham(resRot[2][0], resRot[2][1], resRot[3][0], resRot[3][1], WHITE, 5); // C--> D

    line_bresenham(resRot[2][0], resRot[2][1], resRot[6][0], resRot[6][1], WHITE, 5); // C--> H
    line_bresenham(resRot[3][0], resRot[3][1], resRot[7][0], resRot[7][1], WHITE, 5); // D--> H
    line_bresenham(resRot[4][0], resRot[4][1], resRot[5][0], resRot[5][1], WHITE, 5); // E--> F
    line_bresenham(resRot[4][0], resRot[4][1], resRot[7][0], resRot[7][1], WHITE, 5); // E--> H :
    line_bresenham(resRot[5][0], resRot[5][1], resRot[6][0], resRot[6][1], WHITE, 5); // F--> G
    line_bresenham(resRot[6][0], resRot[6][1], resRot[7][0], resRot[7][1], WHITE, 5); // G--> H
    setcolor(RED);
}


int main() {
    // Show instruction in the window title
    initwindow(800, 500, "Les 3 points de fuite - Appuyez sur une touche pour continuer");

    matrix_t cube1 = {
        {100, 100, 200, 100}, // Vertex A
        {200, 100, 200, 100}, // Vertex B
        {200, 200, 200, 100}, // Vertex C
        {100, 200, 200, 100}, // Vertex D
        {100, 100, 100, 100}, // Vertex E
        {200, 100, 100, 100}, // Vertex F
        {200, 200, 100, 100}, // Vertex G
        {100, 200, 100, 100} // Vertex H
    };

    matrix_t T_tr_o = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {-1.3, -1.3, -1.3, 1}
    };

    // Rotation around the Y-axis by 45 degrees
    matrix_t T_rot_Y = {
        {0.7071, 0, -0.7071, 0},
        {0, 1, 0, 0},
        {0.7071, 0, 0.7071, 0},
        {0, 0, 0, 1}
    };

    matrix_t T_rot_X = {
        {1, 0, 0, 0},
        {0, 0.86, 0.5, 0},
        {0, -0.5, 0.86, 0},
        {0, 0, 0, 1}
    };

    //  projection perspective matrix
    matrix_t T_pr = {
        {1, 0, 0, 0.4},
        {0, 1, 0, 0.4},
        {0, 0, 1, 0.2},
        {0, 0, 0, 1}
    };


    //  Inverse of the initial translation to return to original space
    matrix_t T_tr_inverse = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {1.3, 1.3, 1.3, 0.75}
    };

    matrix_t M_T = T_tr_o * T_rot_Y * T_rot_X * T_pr * T_tr_inverse;             //  Final transformation matrix

    // Apply the final transformation to the cube's vertices
    matrix_t res = cube1 * M_T;

    // Normalize the homogeneous coordinates and scale to fit the screen
    matrix_t resf(8, vector_t(4));
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 4; ++j) {
            resf[i][j] = (res[i][j] / res[i][3]) * 50;
        }
    }

    // Display the transformed vertices for debugging
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << resf[i][j] << "     ";
        }
        std::cout << std::endl;
    }

    Tracer_cube(resf);
    tracer_points_de_fuit(resf);
    getch();
    return 0;
}
