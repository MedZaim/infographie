
#include <cmath>
#include "../includs/graphics_utils.h"
using namespace std;

// Function to multiply a matrix by a cube's vertices
void multiplyMatricesCube(const double cube[8][4], const double matrix[4][4], double result[8][4]) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 4; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                result[i][j] += cube[i][k] * matrix[k][j];
            }
        }
    }
}

// Function to normalize homogeneous coordinates
void normalizeHomogeneous(double cube[8][4]) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 3; ++j) {
            cube[i][j] /= cube[i][3]; // Divide by the w-coordinate
        }
    }
}

// Function to draw the edges of the cube
void drawCube(const double cube[8][4]) {
    // Pairs of vertices that form the cube's edges
    int edges[12][2] = {
            {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Bottom face
            {4, 5}, {5, 6}, {6, 7}, {7, 4}, // Top face
            {0, 4}, {1, 5}, {2, 6}, {3, 7}  // Vertical edges
    };

    // Draw each edge
    for (int i = 0; i < 12; ++i) {
        int start = edges[i][0];
        int end = edges[i][1];
        line_bresenham((int)cube[start][0], (int)cube[start][1], (int)cube[end][0], (int)cube[end][1]);
    }
}


int main() {
    // Initialize the graphics window
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    double a=100, b=100, c=100;

    // Define the cube vertices in homogeneous coordinates
    double cube[8][4] = {
            {100, 100, 100, 1},
            {200, 100, 100, 1},
            {200, 200, 100, 1},
            {100, 200, 100, 1}, // Bottom face

            {100, 100, 200, 1},
            {200, 100, 200, 1},
            {200, 200, 200, 1},
            {100, 200, 200, 1}  // Top face
    };

    // Translation matrix to move the cube to the origin
    matrix_t mat_translation_To_Origin = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {-a, -b, -c, 1}
    };



    // Apply translation to the cube
    matrix_t transformedCube = multiplyMatricesCube(cube, translationToOrigin);

    // Debug: Print transformed cube after translation
    cout << "Cube after translation:" << endl;
    print_matrix(transformedCube);

    // Apply the perspective projection
    double projectedCube[8][4];
    multiplyMatricesCube(transformedCube, perspectiveMatrix, projectedCube);

    // Debug: Print transformed cube after perspective projection
    cout << "Cube after perspective projection:" << endl;
    printMatrix(projectedCube);

    // Normalize the homogeneous coordinates
    normalizeHomogeneous(projectedCube);

    // Debug: Print normalized cube coordinates
    cout << "Normalized cube coordinates:" << endl;
    printMatrix(projectedCube);

    // Clear the screen and draw the projected cube
    cleardevice();
    drawCube(projectedCube);
    /*normalizeHomogeneous(projectedCube);
    drawCube(projectedCube);*/

    // Wait for user input and close the graphics window
    getch();
    closegraph();
    return 0;
}
