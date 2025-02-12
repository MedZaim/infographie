//
// Created by lenovo on 27/12/2024.
//
#include <iostream>
#include <vector>
#include "../../includs/chapes.h"


using namespace std;


void cube(double points[8][4], int color = WHITE, int lw = 1) {
    // Base (face inf�rieure)
    line_bresenham(points[0][0], points[0][1], points[1][0], points[1][1], color, lw);
    line_bresenham(points[1][0], points[1][1], points[2][0], points[2][1], color, lw);
    line_bresenham(points[2][0], points[2][1], points[3][0], points[3][1], color, lw);
    line_bresenham(points[3][0], points[3][1], points[0][0], points[0][1], color, lw);

    // Haut (face sup�rieure)
    line_bresenham(points[4][0], points[4][1], points[5][0], points[5][1], color, lw);
    line_bresenham(points[5][0], points[5][1], points[6][0], points[6][1], color, lw);
    line_bresenham(points[6][0], points[6][1], points[7][0], points[7][1], color, lw);
    line_bresenham(points[7][0], points[7][1], points[4][0], points[4][1], color, lw);

    // Ar�tes verticales (connectant base et haut)
    line_bresenham(points[0][0], points[0][1], points[4][0], points[4][1], color, lw);
    line_bresenham(points[1][0], points[1][1], points[5][0], points[5][1], color, lw);
    line_bresenham(points[2][0], points[2][1], points[6][0], points[6][1], color, lw);
    line_bresenham(points[3][0], points[3][1], points[7][0], points[7][1], color, lw);

    // affiche les somes du cube
    for(int i=0; i<8; i++){
        char label[3] = {(char) ('A' + i), '\0'}; // Nommer les sommets A, B, C...
        outtextxy(points[i][1]+getmaxx()/2, -points[i][2]+getmaxy()/2, label);
    }
}

// Function to perform matrix multiplication for dynamic dimensions
vector<vector<double>> matrixMultiply(const vector<vector<double>> &mat1, const vector<vector<double>> &mat2) {
    int rows1 = mat1.size();
    int cols1 = mat1[0].size();
    int cols2 = mat2[0].size();

    // Initialize the result matrix with zeros
    vector<vector<double>> result(rows1, vector<double>(cols2, 0.0f));

    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            for (int k = 0; k < cols1; ++k) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    return result;
}

// Function for perspective projection using matrix transformations
void perspectiveProjectionGeneral(double x, double y, double z,
                                  double xc, double yc, double zc, // Centre de projection
                                  double x0, double y0, double z0, // Plan de projection
                                  double n1, double n2, double n3, // Vecteur normal
                                  double &x_proj, double &y_proj, double &z_proj) {

    double A = n1;
    double B = n2;
    double C = n3;
    double D = -(A * x0 + B * y0 + C * z0);

    // Create the perspective transformation matrix
    vector<vector<double>> perspectiveMatrix = {
            {1,      0,      0,      0},
            {0,      1,      0,      0},
            {0,      0,      1,      0},
            {-A / D, -B / D, -C / D, 1}
    };

    // Create the point vector for the input coordinates
    vector<vector<double>> pointVector = {
            {x - xc},
            {y - yc},
            {z - zc},
            {1}
    };

    // Perform the matrix multiplication
    vector<vector<double>> result = matrixMultiply(perspectiveMatrix, pointVector);

    // Extract the projected coordinates
    double w = result[3][0]; // Homogeneous coordinate
    x_proj = result[0][0] / w + xc;
    y_proj = result[1][0] / w + yc;
    z_proj = result[2][0] / w + zc;
}

void tracer_cube_perpective(double points[8][4],
                            double a, double b, double c, // Centre de projection
                            double x0, double y0, double z0, // Plan de projection
                            double n1, double n2, double n3 // Vecteur normal
) {
    double projected_points[8][4];
    for (int i = 0; i < 8; ++i) {
        perspectiveProjectionGeneral(points[i][0], points[i][1], points[i][2],
                                     a, b, c,
                                     x0, y0, z0,
                                     n1, n2, n3, projected_points[i][0],
                                     projected_points[i][1],
                                     projected_points[i][2]
        );

    }
    cube(projected_points, WHITE, 5);
    for (int i = 0; i < 8; ++i) {
        cout << "Point[" << i << "]: (" << projected_points[i][0] << ", " << projected_points[i][1] << ", "
             << projected_points[i][2] << ")" << endl;

    }

}

int main() {
    init_graph_();
    double x = 10, y = 20, z = 40;
    double xc = 10, yc = 20, zc = 100;
    double x0 = 1, y0 = 1, z0 = 1;
    double n1 = 0.0, n2 = 0.0, n3 = 1;
    double x_proj, y_proj, z_proj;

    perspectiveProjectionGeneral(x, y, z, xc, yc, zc, x0, y0, z0, n1, n2, n3, x_proj, y_proj, z_proj);

    cout << "Projected Coordinates: (" << x_proj << ", " << y_proj << ", " << z_proj << ")" << endl;

    double points[8][4] = {
            {0,   0,   0,    100},
            {100, 0,   0,    100},
            {100, 100, 0,    100},
            {0,   100, 0,    100},
            {0,   0,   -100, 100},
            {100, 0,   -100, 100},
            {100, 100, -100, 100},
            {0,   100, -100, 100}
    };


    tracer_cube_perpective(points,
                           10, 20, 100,
                           1, 1, 1,
                           0.0, 0.0, 1);
    getch();
    return 0;
}

