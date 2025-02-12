#include ".\..\..\includs\graphics_utils.h"


// Function to draw a vector from origin
void drawVector(vector_t v, int color,int lw=1) {
    line_bresenham(0, 0,  v[0],  v[1], color, lw); // Draw the arrow shaft
    setcolor(color);
    circle( v[0],  v[1], 5); // Draw the arrow tip
}


// Function to create a rotation matrix around the X-axis
void createRotationMatrixX(double angle, double matrix[4][4]) {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            matrix[i][j] = (i == j) ? 1 : 0; // Identity matrix

    matrix[1][1] = cos(angle);
    matrix[1][2] = -sin(angle);
    matrix[2][1] = sin(angle);
    matrix[2][2] = cos(angle);
}


int main() {
    // Initialize graphics mode
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    if (graphresult() != grOk) {
        std::cerr << "Graphics initialization failed" << std::endl;
        return 1;
    }

    // Set up the screen center
    setbkcolor(BLACK);
    cleardevice();
    repere(getmaxx() / 2, getmaxy() / 2);

    // Original vector V(a, b, c)
    vector_t vector = {100, 150, 200, 1}; // Homogeneous coordinates


    // Draw the original vector in red
    drawVector(screenX, screenY, RED, 5);

    // Step 1: Rotate around X-axis to align V with the XZ plane
    double angle1 = atan2(vector[1], vector[2]); // Calculate angle for X-axis rotation
    double rotationX[4][4];
    createRotationMatrixX(-angle1, rotationX);
    applyTransformation(vector, rotationX);

    // Step 2: Rotate around Y-axis to align V with the Z-axis
    double angle2 = atan2(vector[0], vector[2]); // Calculate angle for Y-axis rotation
    double rotationY[4][4];
    createRotationMatrixY(-angle2, rotationY);
    applyTransformation(vector, rotationY);

    // Project transformed vector to 2D screen
    double alignedX = vector[0];
    double alignedY = vector[1]; // After transformation, Y should be close to 0

    // Draw the aligned vector in green
    drawVector(alignedX, alignedY, GREEN, 5);

    // Display result
    setcolor(RED);
    outtextxy(10, 10, (char*)"Red: Original Vector");
    setcolor(GREEN);
    outtextxy(10, 30, (char*)"Green: Aligned Vector");

    // Wait for user to close the window
    getch();
    closegraph();

    return 0;
}










/*

int main() {
    // testing main function:

    init_graph_();
    int X_MAX = 640, Y_MAX = 480;
    // line_bresenham(0, 0, 100, 100);
    repere(X_MAX / 2, Y_MAX / 2);

    //ellipse_p_p_by_mouse();
    //rectangle_by_mouse_click();
    //rectangle_teta({0, 0}, {100, 150}, 0);
    //rectangle_teta({0, 0}, {100, 150}, PI/4);
    //ellipse_p_p_by_mouse();
    rectangle_by_mouse_click_rotate();
    getch();
    closegraph();
    return 0;
}*/
