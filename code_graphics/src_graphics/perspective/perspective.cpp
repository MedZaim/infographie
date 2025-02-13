
#include "../../includs/graphics_utils.h"


matrix_t get_perspective_matrix_o_r0_n(double x0, double y0,double z0, double n1, double n2, double n3) {
    double d0 = -(n1*x0+n2*y0+n3*z0);
    matrix_t T_perspective = {
        {1, 0, 0, n1 / d0},
        {0, 1, 0, n2 / d0},
        {0, 0, 1, n3 / d0},
        {0, 0, 0, 1}
    };
    return T_perspective;
}

matrix_t get_perspective_matrix_o_r0_n(vector_t r0, vector_t n) {
    return get_perspective_matrix_o_r0_n(r0[0], r0[1], r0[2], n[0], n[1], n[2]);
}

matrix_t get_perspective_matrix_cp_r0_n(double a, double b, double c, double x0, double y0, double z0, double n1, double n2, double n3) {
    matrix_t T_translation = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {-a, -b, -c, 1}
    };
    matrix_t T_perspective = get_perspective_matrix_o_r0_n(x0, y0, z0, n1, n2, n3);
    matrix_t T_translation_invers = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {a, b, c, 1}
    };
    return T_translation * T_perspective * T_translation_invers;
}

matrix_t get_perspective_matrix_cp_r0_n(vector_t center_proj, vector_t r0, vector_t n) {
    return get_perspective_matrix_cp_r0_n(center_proj[0], center_proj[1], center_proj[2], r0[0], r0[1], r0[2], n[0], n[1], n[2]);
}
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

vector_t findIntersection(const vector_t &vecteur1, const vector_t &vecteur2) {
    vector_t result(2);
    result[0] = (vecteur2[1] - vecteur1[1]) / (vecteur1[0] - vecteur2[0]);
    result[1] = vecteur1[0] * result[0] + vecteur1[1];
    return result;
}

vector_t findIntersection(double x1, double y1, double x2, double y2) {
    vector_t vecteur(2);
    vecteur[0] = (y2 - y1) / (x2 - x1);
    vecteur[1] = y1 - vecteur[0] * x1;
    return vecteur;
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
void tracer_points_de_fuit(matrix_t resRot, int color = 15, int lw = 1) {
    vector_t vecteur01 = findIntersection(resRot[0][0], resRot[0][1], resRot[3][0], resRot[3][1]);
    vector_t vecteur02 = findIntersection(resRot[4][0], resRot[4][1], resRot[7][0], resRot[7][1]);
    vector_t resultat = findIntersection(vecteur01, vecteur02);

    line_bresenham(resRot[0][0], resRot[0][1], resultat[0], resultat[1], WHITE, lw);
    line_bresenham(resRot[4][0], resRot[4][1], resultat[0], resultat[1], WHITE, lw);
    line_bresenham(resRot[1][0], resRot[1][1], resultat[0], resultat[1], WHITE, lw);
    line_bresenham(resRot[5][0], resRot[5][1], resultat[0], resultat[1], WHITE, lw);

    vector_t vecteur11 = findIntersection(resRot[0][0], resRot[0][1], resRot[4][0], resRot[4][1]);
    vector_t vecteur12 = findIntersection(resRot[3][0], resRot[3][1], resRot[7][0], resRot[7][1]);
    vector_t resultat1 = findIntersection(vecteur11, vecteur12);

    line_bresenham(resRot[0][0], resRot[0][1], resultat1[0], resultat1[1], WHITE, lw);
    line_bresenham(resRot[3][0], resRot[3][1], resultat1[0], resultat1[1], WHITE, lw);
    line_bresenham(resRot[1][0], resRot[1][1], resultat1[0], resultat1[1], WHITE, lw);
    line_bresenham(resRot[5][0], resRot[5][1], resultat1[0], resultat1[1], WHITE, lw);

    vector_t vecteur21 = findIntersection(resRot[0][0], resRot[0][1], resRot[1][0], resRot[1][1]);
    vector_t vecteur22 = findIntersection(resRot[6][0], resRot[6][1], resRot[7][0], resRot[7][1]);
    vector_t resultat2 = findIntersection(vecteur21, vecteur22);

    line_bresenham(resRot[6][0], resRot[6][1], resultat2[0], resultat2[1], WHITE, lw);
    line_bresenham(resRot[0][0], resRot[0][1], resultat2[0], resultat2[1], WHITE, lw);
    line_bresenham(resRot[3][0], resRot[3][1], resultat2[0], resultat2[1], WHITE, lw);
    line_bresenham(resRot[7][0], resRot[7][1], resultat2[0], resultat2[1], WHITE, lw);
}


int main() {

    initwindow(800, 500, "Graphics Window");

    matrix_t cube = get_parallelogram(200,200,200,1);

    vector_t center_proj = {0, 0, 400};
    vector_t r0 = {0, 0, 200};
    vector_t n = {0, 0, 200};


    matrix_t T_tr = get_perspective_matrix_cp_r0_n(center_proj, r0, n);

    matrix_t cube_transformd = divid_on_w(cube * T_tr);
   // tracer_points_de_fuit(cube_transformd);
    cleardevice();

    tracer_p(cube_transformd);

    affich(cube, "cube");
    affich(T_tr, "T_tr");
    affich(cube_transformd, "cube_transformd");
    getch();
    return 0;
}

