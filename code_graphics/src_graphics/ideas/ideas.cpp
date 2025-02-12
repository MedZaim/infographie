//
// Created by lenovo on 06/11/2024.
//
//#include "./../../includs/graphics_utils.h"
#include "../../includs/chapes.h"
#include <conio.h>
#include <iostream>

// Initialize grid parameters
int gridSize = 20;    // Initial grid size
int zoomFactor = 2;   // Factor by which the grid scales with each zoom

// Function to draw a grid
void drawGrid(int size) {
    cleardevice();  // Clear the screen

    // Get screen dimensions
    int width = getmaxx();
    int height = getmaxy();

    // Draw vertical lines
    for (int x = 0; x <= width; x += size) {
        line(x, 0, x, height);
    }

    // Draw horizontal lines
    for (int y = 0; y <= height; y += size) {
        line(0, y, width, y);
    }
}

void zoomable_grid() {

    // Initial grid
    drawGrid(gridSize);

    // Event loop
    char key;
    while (true) {
        key = getch();

        if (key == 27) {  // Escape key to exit
            break;
        }

        // Zoom in
        if (key == '+') {
            gridSize += zoomFactor;
            drawGrid(gridSize);
        }

        // Zoom out, ensuring grid size stays above a minimum threshold
        if (key == '-') {
            if (gridSize - zoomFactor > 5) {
                gridSize -= zoomFactor;
                drawGrid(gridSize);
            }
        }
    }

}




int main() {
    // Initialize graphics mode
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    zoomable_grid();
    printf("random=%d\n", random(1, 10));


    getch();
    closegraph();
    return 0;
}
