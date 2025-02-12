//
// Created by lenovo on 24/12/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>
#include "../../includs/chapes.h"
void init_graph() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
}
void repere() {
    cleardevice();
    setbkcolor(9);
    setcolor(5);
    line(0, 240, 640, 240);
    line(320, 0, 320, 480);
}/*
void pixel(int x, int y, int color) {
    x = x + 320;
    y = 240 - y;
    putpixel(x, y, color);
}
void dessiner_ligne(int x1, int y1, int x2, int y2, int color) {
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        pixel(x1, y1, color);
        if (x1 == x2 && y1 == y2) break;
        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}*/
void dessiner_3d_graphe(){
    line_bresenham(0, 0, 0, 320, WHITE);
    line_bresenham(0, 0, 420, 0, WHITE);
    line_bresenham(0, 0, -160, -210, WHITE);
}
void T(int a, int b, int c, float t[4][4]){
    float A = sqrt((a * a) + (b * b) + (c * c));
    float B = sqrt((b * b) + (c * c));
    t[0][0] = B / A;          t[0][1] = 0;            t[0][2] = a / A;          t[0][3] = 0;
    t[1][0] = -(a * b) / (A * B); t[1][1] = c / B;     t[1][2] = b / A;          t[1][3] = 0;
    t[2][0] = -(c * a) / (A * B); t[2][1] = -b / B;    t[2][2] = c / A;          t[2][3] = 0;
    t[3][0] = 0;              t[3][1] = 0;            t[3][2] = 0;              t[3][3] = 1;
}
void T_inverse(int a, int b, int c, float t[4][4]) {
    float A = sqrt((a * a) + (b * b) + (c * c));
    float B = sqrt((b * b) + (c * c));

    t[0][0] = B / A;          t[0][1] = -(a * b) / (A * B); t[0][2] = -(c * a) / (A * B); t[0][3] = 0;
    t[1][0] = 0;              t[1][1] = c / B;             t[1][2] = -b / B;            t[1][3] = 0;
    t[2][0] = a / A;          t[2][1] = b / A;             t[2][2] = c / A;             t[2][3] = 0;
    t[3][0] = 0;              t[3][1] = 0;                t[3][2] = 0;                 t[3][3] = 1;
}
void multiply(float T[4][4], float T_inv[4][4], float result[4][4]) {
    int i, j, k;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            result[i][j] = 0;
            for (k = 0; k < 4; k++) {
                result[i][j] += T[i][k] * T_inv[k][j];
            }
        }
    }
}
void vect(float v[1][4], float result[4][4], float vect_res[1][4]) {
    int i, j, k;
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 4; j++) {
            vect_res[i][j] = 0;
            for (k = 0; k < 4; k++) {
                vect_res[i][j] += v[i][k] * result[k][j];
            }
        }
    }
}
int main()
{
    int v[3] = {-130, 350, 75};
    int n[3] = {100, 200, 20};

    float T_v[4][4], T_n[4][4], T_combined[4][4];
    float v_vect[1][4] = {{100, 200, 30, 1}};
    float n_vect[1][4] = {{-50, 150, 75, 1}};
    float v_result[1][4] = {0};

    T(v[0], v[1], v[2], T_v);
    T_inverse(n[0], n[1], n[2], T_n);
    multiply(T_v, T_n, T_combined);
    vect(v_vect, T_combined, v_result);
    init_graph();
    dessiner_3d_graphe();
    line_bresenham(0, 0, v[0], v[1], YELLOW, 5);
    line_bresenham(0, 0, n[0], n[1], GREEN , 5);
    delay(2000);
    cleardevice();
    setbkcolor(BLACK);
    dessiner_3d_graphe();
    line_bresenham(0, 0, (int)v_result[0][0], (int)v_result[0][1], YELLOW,5);
    line_bresenham(0, 0, n[0], n[1], GREEN,5);
    getch();
    closegraph();
    return 0;
}