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

matrix_t get_matrix_reper(const matrix_t cube, double d) {
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

void display_BH_(matrix_t cube, int color = GREEN, int lw = 5) {
    line_bresenham(cube[1], cube[7], color, lw);
}

matrix_t display_cube(const matrix_t cube) {
    matrix_t cube1 = cube * Tcv;
    Tracer_cube(cube1);
    display_BH_(cube1);
    return cube1;
}

void rotate(matrix_t cube, matrix_t reper, matrix_t M) {
    while (true) {
        cube = (cube * M);
        cleardevice();
        Tracer_cube(cube * Tcv);
        display_BH_(cube * Tcv);

        display_reper(reper);
    }
}

int main() {
    initwindow(800, 600, "Controle");

    matrix_t cube1, cube = get_parallelogram(200, 100, 100, 1);
    Tracer_cube(cube * Tcv);
    display_BH_(cube * Tcv);
    matrix_t reper = get_matrix_reper(cube * Tcv, 300);
    display_reper(reper);
    getch();

    matrix_t Tras = M_trs({-200, 0, 0, 1});

    matrix_t Trs_inverse = M_trs({200, 0, 0, 1});

    //  aligner hb avec z
    matrix_t aliner = get_matrix_alin_v_with_Z(cube[7] - cube[0]);

    //matrice de tronsformation globale

    matrix_t M = Tras * aliner * M_rot_z(0.01) * (aliner ^'t') * Trs_inverse;

    rotate(cube, reper, M);
    getch();
}
