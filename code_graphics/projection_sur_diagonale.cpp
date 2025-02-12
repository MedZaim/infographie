#include <cmath>
#include "includs/graphics_utils.h"
using namespace std;


// Function to draw the edges of the cube
void drawCube(const matrix_t cube) {
    // Pairs of vertices that form the cube's edges
    int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Bottom face
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // Top face
        {0, 4}, {1, 5}, {2, 6}, {3, 7} // Vertical edges
    };

    // Draw each edge
    for (int i = 0; i < 12; ++i) {
        int start = edges[i][0];
        int end = edges[i][1];
        line_bresenham((int) cube[start][0], (int) cube[start][1], (int) cube[end][0], (int) cube[end][1]);
    }
}

matrix_t projection_pespective(matrix_t cube, double d) {
    matrix_t projectedCube = cube * get_perspective_matrix_Z_d(d);
    // devision des coordonees Xh, Yh, et Zh par Wh
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            projectedCube[i][j] /= (double) projectedCube[i][3];
        }
    }
    return projectedCube;
}


int main() {
    // Initialize the graphics window
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char *) "");

    double x = 300, y = 300, z = 300;
    // Define the cube vertices in homogeneous coordinates
    matrix_t cube = get_parallelogram(x, y, z, 1);

    //plane of projection
    double n1 = 0, n2 = y, n3 = z ;
    //centre de projecton
    double a = 0, b = 0, c = 1000;

    // R0(x0,y0,z0) point sur le plan de projection
    double x0 = 0, y0 = y, z0 = 0;

    //distance orthogonale between the plan and the center of projection
    double d0 = -(n1*x0+n2*y0+n3*z0);

    // Translation matrix to move the cube to the origin
    matrix_t mat_translation_To_Origin = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {-a, -b, -c, 1}
    };
    // Translation matrix to move the cube to it's original position
    matrix_t mat_translation_inverse = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {a, b, c, 1}
    };
    //  Perspective Projection matrix for viewpoint at (a,b,c)
    //  on plan of normal(n1,n2,n3) and distance d from the viewpoint
    matrix_t T_per = {
        {1, 0, 0, n1 / d0},
        {0, 1, 0, n2 / d0},
        {0, 0, 1, n3 / d0},
        {0, 0, 0, 1}
    };

    // matrice of transformation global (translation + projection)
    matrix_t T = mat_translation_To_Origin * T_per * mat_translation_inverse;



    // Apply the perspective projection
    matrix_t projectedCube = cube * T;

    // devision des coordonees Xh, Yh, et Zh par Wh
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            projectedCube[i][j] /= (double) projectedCube[i][3];
        }
    }

    affich(cube, "cube");
    affich(T, "T");
    affich(projectedCube, "projectedCube");

    cleardevice();
    drawCube(projectedCube);

    getch();
    closegraph();
    return 0;
}
