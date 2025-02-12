

#include<iostream>
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


/*

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

void tracer_points_de_fuit(double resRot[8][4]){
    double vecteur01[2];
    findVector(resRot[0][0], resRot[0][1], resRot[3][0], resRot[3][1], vecteur01);
    double vecteur02[2];
    findVector(resRot[4][0], resRot[4][1], resRot[7][0], resRot[7][1], vecteur02);
    double resultat[2];

    findIntersection(vecteur01, vecteur02, resultat);



    line_bresenham(resRot[0][0], resRot[0][1], resultat[0], resultat[1], WHITE);

    line_bresenham(resRot[4][0], resRot[4][1], resultat[0], resultat[1], WHITE);
    line_bresenham(resRot[1][0], resRot[1][1], resultat[0], resultat[1], WHITE);
    line_bresenham(resRot[5][0], resRot[5][1], resultat[0], resultat[1], WHITE);


    double vecteur11[2];
    findVector(resRot[0][0], resRot[0][1], resRot[4][0], resRot[4][1], vecteur11);
    double vecteur12[2];
    findVector(resRot[3][0], resRot[3][1], resRot[7][0], resRot[7][1], vecteur12);
    double resultat1[2];
    findIntersection(vecteur11, vecteur12, resultat1);


    line_bresenham(resRot[0][0], resRot[0][1], resultat1[0], resultat1[1], WHITE);
    line_bresenham(resRot[3][0], resRot[3][1], resultat1[0], resultat1[1], WHITE);
    line_bresenham(resRot[1][0], resRot[1][1], resultat1[0], resultat1[1], WHITE);
    line_bresenham(resRot[5][0], resRot[5][1], resultat1[0], resultat1[1], WHITE);

    double vecteur21[2];
    findVector(resRot[0][0], resRot[0][1], resRot[1][0], resRot[1][1], vecteur21);
    double vecteur22[2];
    findVector(resRot[6][0], resRot[6][1], resRot[7][0], resRot[7][1], vecteur22);
    double resultat2[2];
    findIntersection(vecteur21, vecteur22, resultat2);


    line_bresenham(resRot[6][0], resRot[6][1], resultat2[0], resultat2[1], WHITE);
    line_bresenham(resRot[0][0], resRot[0][1], resultat2[0], resultat2[1], WHITE);
    line_bresenham(resRot[3][0], resRot[3][1], resultat2[0], resultat2[1], WHITE);
    line_bresenham(resRot[7][0], resRot[7][1], resultat2[0], resultat2[1], WHITE);

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


}
*/


int main() {
    // Initialize the graphics library and create a graphical window
    init_graph();
    initwindow(800, 500, "Graphics Window");

    // Define the vertices of a 3D cube in homogeneous coordinates (x, y, z, w)
    matrix_t cube1 = {
            {100, 100, 200, 100}, // Vertex A
            {200, 100, 200, 100}, // Vertex B
            {200, 200, 200, 100}, // Vertex C
            {100, 200, 200, 100}, // Vertex D
            {100, 100, 100, 100}, // Vertex E
            {200, 100, 100, 100}, // Vertex F
            {200, 200, 100, 100}, // Vertex G
            {100, 200, 100, 100}  // Vertex H
    };

    // Step 1: Initial translation to move the cube to the origin
    matrix_t T1 = {
            {1,    0,    0,    0},
            {0,    1,    0,    0},
            {0,    0,    1,    0},
            {-1.3, -1.3, -1.3, 1}
    };

    // Step 2: Rotation around the Y-axis by 45 degrees
    matrix_t T2 = {
            {0.7071, 0, -0.7071, 0},
            {0,      1, 0,       0},
            {0.7071, 0, 0.7071,  0},
            {0,      0, 0,       1}
    };

    // Step 3: Rotation around the X-axis
    matrix_t T3 = {
            {1, 0,    0,    0},
            {0, 0.86, 0.5,  0},
            {0, -0.5, 0.86, 0},
            {0, 0,    0,    1}
    };

    // Step 4: Final translation to move the cube to its target position
    matrix_t T4= {
            {1, 0, 0, 0.4},
            {0, 1, 0, 0.4},
            {0, 0, 1, 0.2},
            {0, 0, 0, 1}
    };


    // Step 5: Inverse of the initial translation to return to original space
    matrix_t inverse_T1 = {
            {1,   0,   0,   0},
            {0,   1,   0,   0},
            {0,   0,   1,   0},
            {1.3, 1.3, 1.3, 0.75}
    };

    // Perform matrix multiplications to combine transformations
    matrix_t M_T=T1* T2*T3*T4* inverse_T1;  // T1 * T2 * T3 * T4 *T1_inverse  Final transformation matrix
    // Apply the final transformation to the cube's vertices
    matrix_t res= cube1 * M_T;

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
