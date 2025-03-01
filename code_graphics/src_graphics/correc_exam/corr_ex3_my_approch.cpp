//
// Created by ZAIM Med on 2/11/2025.
// My approach

#include "graphics.h"
#include <cmath>
#include <vector>
#include <iomanip>
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

typedef vector<double> vector_t;
typedef vector<vector_t> matrix_t;

void affich(matrix_t mat, string label) {
    cout << label << ":[" << endl;
    for (int i = 0; i < mat.size(); i++) {
        cout << "     {";
        for (int j = 0; j < mat[i].size(); j++) {
            cout << setw(8) << std::round(mat[i][j] * 1000) / 1000 << " ";
        }
        cout << "}" << endl;
    }
    cout << "]" << endl;
}

matrix_t transpose(const matrix_t &mat) {
    int rows = mat.size();
    int cols = mat[0].size();

    matrix_t transposed(cols, vector_t(rows, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposed[j][i] = mat[i][j];
        }
    }
    return transposed;
}

// matrix_t multiplication function
matrix_t matrix_multiply(matrix_t mat1, matrix_t mat2) {
    int rows = mat1.size();
    int cols = mat2[0].size();
    int inner_dim = mat1[0].size();

    matrix_t res(rows, vector_t(cols, 0));

    if (mat1[0].size() != mat2.size()) {
        cout << "Invalid matrix_t multiplication" << endl;
        cout << mat1.size() + "!" + mat2[0].size() << endl;
        return res;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int k = 0; k < inner_dim; ++k) {
                res[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    return res;
}

matrix_t operator*(const matrix_t &a, const matrix_t &b) {
    return matrix_multiply(a, b);
}


void tracer_p(matrix_t cube, int color = GREEN) {
    setcolor(color);
    int x_ofset = getmaxx() / 2, y_ofset = getmaxy() / 2;
    line(cube[0][0] + x_ofset, -cube[0][1] + y_ofset, cube[1][0] + x_ofset, -cube[1][1] + y_ofset);
    // A--> B : plan de projection
    line(cube[0][0] + x_ofset, -cube[0][1] + y_ofset, cube[3][0] + x_ofset, -cube[3][1] + y_ofset); // A--> D
    line(cube[0][0] + x_ofset, -cube[0][1] + y_ofset, cube[4][0] + x_ofset, -cube[4][1] + y_ofset); // A--> E
    line(cube[1][0] + x_ofset, -cube[1][1] + y_ofset, cube[2][0] + x_ofset, -cube[2][1] + y_ofset); // B--> C
    line(cube[1][0] + x_ofset, -cube[1][1] + y_ofset, cube[5][0] + x_ofset, -cube[5][1] + y_ofset); // B--> G
    line(cube[2][0] + x_ofset, -cube[2][1] + y_ofset, cube[3][0] + x_ofset, -cube[3][1] + y_ofset); // C--> D

    line(cube[2][0] + x_ofset, -cube[2][1] + y_ofset, cube[6][0] + x_ofset, -cube[6][1] + y_ofset); // C--> H
    line(cube[3][0] + x_ofset, -cube[3][1] + y_ofset, cube[7][0] + x_ofset, -cube[7][1] + y_ofset); // D--> H
    line(cube[4][0] + x_ofset, -cube[4][1] + y_ofset, cube[5][0] + x_ofset, -cube[5][1] + y_ofset); // E--> F
    line(cube[4][0] + x_ofset, -cube[4][1] + y_ofset, cube[7][0] + x_ofset, -cube[7][1] + y_ofset); // E--> H :
    line(cube[5][0] + x_ofset, -cube[5][1] + y_ofset, cube[6][0] + x_ofset, -cube[6][1] + y_ofset); // F--> G
    line(cube[6][0] + x_ofset, -cube[6][1] + y_ofset, cube[7][0] + x_ofset, -cube[7][1] + y_ofset); // G--> H

    for (int i = 0; i < 8; i++) {
        int x = cube[i][0], y = cube[i][1], z = cube[i][2];
        char label[3] = {(char) ('A' + i), '\0'}; // Nommer les sommets A, B, C...
        outtextxy(x + x_ofset + 2, -y + y_ofset + 1, label);
    }
}

void reper() {
    line(getmaxx() / 2, getmaxy() / 2, getmaxx()/2+150, getmaxy() / 2 );
    line(getmaxx() / 2, getmaxy() / 2, getmaxx() / 2 , getmaxy()/2-150);

    outtextxy(getmaxx()/2+150, getmaxy()/ 2 , "X");
    outtextxy(getmaxx()/ 2   , getmaxy()/2-150, "Y");
}

// Question 1
//a) Une translation qui am`ene I `a A
matrix_t T_tr = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {-50, -25, -10, 1}
};
//translation inverse
matrix_t T_tr_inverse = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {50, 25, 10, 1}
};

//b) Une rotation autour de l’axe Z qui am`ene le segment (L) au plan XZ

//cos(teta1) = (AB/2) / √((AD/2)^2 + (AB/2)^2)= 25 / √(50^2 + 25^2)= 25 / √(2500 + 625)= 25 / √3125= 25 / 55.9= 0.45
double cos_theta1 = (25 / sqrt(2500 + 625));

//sin(teta1) =  (AD/2) / √((AD/2)^2 + (AB/2)^2)= 50 / √(50^2 + 25^2)= 50 / √(2500 + 625)= 50 / √3125= 50 / 55.9= 0.89
double sin_theta1 = (50 / sqrt(2500 + 625));

matrix_t T_RtZ = {
    {cos_theta1, sin_theta1, 0, 0},
    {-sin_theta1, cos_theta1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
};

//c) Une rotation autour de l’axe X pour aligner le segment (L) avec l’axe Z
// teta1 est negatif

//cos(teta2) = AC / √(AE^2 + AC^2)= 100 / √(100^2 + 20^2) = 100 / √(10000 + 400) = 100 / √10400 = 100 / 101.98 = 0.98
double cos_theta2 = (100 / sqrt(10000 + 400));

//sin(-teta2) = -sin(teta2) = - AE / √(AE^2 + AC^2) = -20 / √(10000 + 400) = -20 / √10400 = -20 / 101.98 = -0.2
double sin_theta2 = (-20 / sqrt(10000 + 400));

matrix_t T_RtX = {
    {1, 0, 0, 0},
    {0, cos_theta2, sin_theta2, 0},
    {0, -sin_theta2, cos_theta2, 0},
    {0, 0, 0, 1}
};

//d) Une rotation autour du segment (L) qui est d´ej`a align´e avec l’axe Z (rotation autour de Z) de 45°

matrix_t R_Z = {
    {sqrt(2) / 2, sqrt(2) / 2, 0, 0},
    {-sqrt(2) / 2, sqrt(2) / 2, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
};

//pour effectue un rotation continue autour du segment on doit determiner La Matrice de rotation
//en fonction de l'angle de rotation d_teta
matrix_t T__teta(double d_teta){
    matrix_t R_Z_d_teta = {
        {cos(d_teta), -sin(d_teta), 0, 0},
        {sin(d_teta), cos(d_teta), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    return T_tr * T_RtZ * T_RtX * R_Z_d_teta * transpose(T_RtX) * transpose(T_RtZ) * T_tr_inverse;
}

//La matrice de la transformation totale s’´ecrit alors :
matrix_t T = T_tr * T_RtZ * T_RtX * R_Z * transpose(T_RtX) * transpose(T_RtZ) * T_tr_inverse;

// Question 2
//La matrice de projection en perspective avec un centre de projection `a une distance d = 1000 est :
matrix_t T_per = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 0, -1.0 / 100},
    {0, 0, 0, 1}
};

matrix_t projection_perspective(const matrix_t parallelogramme) {
    matrix_t res = parallelogramme * T_per;
    // devision des coordonees Xh, Yh, et Zh par Wh
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            res[i][j] /= (double) res[i][3];
        }
    }
    return res;
}

void rotate(matrix_t figure, int color=YELLOW) {
    double d_teta = 0.01;
    // Rotation continue autour du segment
    for (;;) {
        clearmouseclick(WM_LBUTTONDOWN);
        cleardevice();
        setcolor(3);
        reper();
        figure = figure * T__teta(d_teta);
        tracer_p(figure, color);
        // Sleep for 10 milliseconds
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        if (kbhit()) {
            break;
        }
    }
}

int main() {
    initwindow(400, 300, "Rotation continue/(L).(my approach)");

    matrix_t parallelogramme = {
        {0, 0, 0, 1}, // A
        {100, 0, 0, 1}, // B
        {100, 50, 0, 1}, // C
        {0, 50, 0, 1}, // D
        {0, 0, 20, 1}, // E
        {100, 0, 20, 1}, // F
        {100, 50, 20, 1}, // G
        {0, 50, 20, 1} // H
    };
    setcolor(3);
    reper();
    tracer_p(parallelogramme, WHITE);
    getch();
    cleardevice();
    rotate(parallelogramme);
    getch();
    closegraph();
    /////////////////////////////////////////////////////////////////////////
    initwindow(400, 300, "projection perspective sur [XY] ");
    setcolor(3);
    matrix_t projected_p = projection_perspective(parallelogramme);
    reper();
    tracer_p(projected_p, 13);

    affich(parallelogramme, "parallelogramme");
    affich(projected_p, "projected_p");
    getch();
    closegraph();
    return 0;
}
