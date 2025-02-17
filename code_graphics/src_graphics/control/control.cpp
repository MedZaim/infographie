//
// Created by lenovo on 10/01/2025.

#include "../../includs/graphics_utils.h"


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
    return {
        get_point_of_seg_far(cube[0], cube[1], d),
        get_point_of_seg_far(cube[0], cube[3], d),
        get_point_of_seg_far(cube[0], cube[4], d),
        {1}
    };
}

void display_reper(matrix_t reper, point_2d_t center_rep = {0, 0}, int color = YELLOW, int lw = 1) {
    setcolor(color);
    char bufer[] = {'X', 'Y', 'Z', '\0'};
    int x0 = center_rep[0], y0 = center_rep[1];
    for (int i = 0; i < reper.size(); i++) {
        int x = reper[i][0], y = reper[i][1];
        line_bresenham(x0, y0, x + x0, y + y0, color, lw);
        //cercle
        circle_full_bresenham(x + x0, y + y0, 5, color);

        char label[3] = {bufer[i], '\0'}; // Nommer les sommets A, B, C...
        outtextxy((x + x0) + getmaxx() / 2 + 6, getmaxy() / 2 - (y + y0) + 3, label);
    }
}
void display_BH_(matrix_t cube) {
    line_bresenham(cube[1], cube[7], YELLOW);
}

int main() {
    initwindow(800, 500, "Graphics Window");

    matrix_t cube1, cube = get_parallelogram(-200, 100, 100, 1);
    cube = rotation_x(cube, -PI / 2);
    cube = rotation_y(cube,  -PI/ 2+0.3);
    cube1 = cube * Tcv;
    matrix_t reper = get_matrix_reper(cube1, 300);
    display_reper(reper);
    Tracer_cube(cube1);

getch();

/*while (true) {

    cleardevice();
    matrix_t cube_transformd = cavalier(cube);
    Tracer_cube(cube_transformd);

    display_reper(get_matrix_reper(cube1, 300));
    delay(20);
}*/


}
