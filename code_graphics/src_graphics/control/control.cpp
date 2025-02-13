//
// Created by lenovo on 10/01/2025.
//
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <graphics.h>
#include <stdlib.h>
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
//point of segment that defined by 2 points return a point of segment far from the first bay distence d

vector_t get_point_of_seg_far(double x1, double y1, double z1, double x2, double y2, double z2, double d = 200) {
    double x = x2 - x1;
    double y = y2 - y1;
    double z = z2 - z1;
    double norm = sqrt(x * x + y * y + z * z);
    x = x / norm;
    y = y / norm;
    z = z / norm;
    return {x * d + x1, y * d + y1, z * d + z1};
}


vector_t get_point_of_seg_far(vector_t p1, vector_t p2, double d) {
    return get_point_of_seg_far(p1[0], p1[1], p1[2], p2[0], p2[1], p2[2], d);
}

matrix_t get_matrix_reper(matrix_t cube, double d) {

    matrix_t reper = {
            get_point_of_seg_far(cube[0], cube[1], d),
            get_point_of_seg_far(cube[0], cube[3], d),
            get_point_of_seg_far(cube[0], cube[4], d),
            {1}
    };
    return reper;

}

void display_reper(matrix_t reper, int color = YELLOW) {
    setcolor(color);
    char bufer[] = {'X', 'Y', 'Z', '\0'};
    int x0 = 0, y0 = 0;
    for (int i = 0; i < reper.size(); i++) {
        int x = reper[i][0], y = reper[i][1];
        line(x0, y0, x, y);
        //cercle

        char label[3] = {bufer[i], '\0'}; // Nommer les sommets A, B, C...
        outtextxy(x, y, label);
        cercle_bresenham(x, y, 1, color);
    }

}


int main() {
    // Initialize the graphics library and create a graphical window
    init_graph();
    initwindow(800, 500, "Graphics Window");



    matrix_t cube = get_parallelepide(200, 100, 100, 1, 1);
    cube = cavalier(cube);
    Tracer_cube(cube);

    getch();
    cube = rotation_x(cube, -PI / 4);
    matrix_t cube1 = cube;
    while (true) {

        cleardevice();
        matrix_t cube_transformd = cavalier(cube);
        Tracer_cube(cube_transformd);

        display_reper(get_matrix_reper(cube1, 300));
        delay(20);
    }

}