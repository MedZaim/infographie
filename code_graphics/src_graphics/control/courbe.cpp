//
// Created by lenovo on 10/01/2025.
//
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

vector_t get_point_of_seg_far(double x1, double y1, double z1, double x2, double y2, double z2, double d=200){
    double x = x2 - x1;
    double y = y2 - y1;
    double z = z2 - z1;
    double norm = sqrt(x * x + y * y + z * z);
    x = x / norm;
    y = y / norm;
    z = z / norm;
    return {x * d + x1, y * d + y1, z * d + z1};
}


vector_t get_point_of_seg_far(vector_t p1, vector_t p2, double d){
    return get_point_of_seg_far(p1[0], p1[1], p1[2], p2[0], p2[1], p2[2], d);
}

matrix_t get_matrix_reper(matrix_t cube , double d) {

    matrix_t reper = {
            get_point_of_seg_far(cube[0], cube[1], d),
            get_point_of_seg_far(cube[0], cube[3], d),
            get_point_of_seg_far(cube[0], cube[4], d),
            {1}
    };
    return reper;

}

void  display_reper(matrix_t reper,int color=YELLOW) {
    setcolor(color);
    char bufer[] = {'X', 'Y', 'Z', '\0'};
    int x0=0,y0=0;
    cout<<"reper size:"<<reper.size()<<endl;
    cout<<"reper:["<<endl;
    for (int i = 0; i < reper.size(); i++) {
        int x = reper[i][0], y = reper[i][1];

        line(x0, y0, x, y);
        //cercle

        char label[3] = {bufer[i], '\0'}; // Nommer les sommets A, B, C...
        outtextxy(x, y, label);

        cercle_bresenham(x, y, 1, color);
        cout<<"[x="<<x<<", y="<<y<<"]"<<endl;

    }
    cout<<"]"<<endl;

}
int main() {
    // Initialize the graphics library and create a graphical window
    init_graph();
    initwindow(800, 500, "Graphics Window");

    // Center de projection
    double a = 50, b = 50, c = 50;



    // Define the vertices of a 3D cube in homogeneous coordinates (x, y, z, w)
    matrix_t cube = get_parallelogram(200, 100, 100,  1);

    cercle_bresenham(cube[3][0], cube[3][1],5,1);


    matrix_t  reper =cavalier( get_matrix_reper(cube, 300));


    while (true) {
        // cube = rotation_z(cube, PI / 20);
        cleardevice();
        matrix_t cube1 = cavalier(cube);
        Tracer_cube(cube1);

        bezierCubic(cube[1][0], cube[1][1], cube[5][0], cube[5][1], cube[7][0], cube[7][1],cube[3][0], cube[3][1]);
        display_reper(reper);
        cercle_bresenham(cube[3][0], cube[3][1],5,1);
        Tracer_cube(cube1);
        delay(20);
    }

    return 0;
}
