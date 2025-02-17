//
// Created by lenovo on 10/11/2024.
//
#include "../../includs/graphics_utils.h"


void draw_poygon(polygon_t p, int color = 15, int lw = 1) {
    for (int i = 0; i < p.size() - 1; i++) {
        line_bresenham(p[i], p[i + 1], color, lw);
    }
    line_bresenham(p[p.size() - 1], p[0], color, lw);
}

void draw_point(point_2d_t p, int color = 15, int lw = 1) {
    pixel(p[0], p[1], color, lw);
}

point_2d_t get_point_by_mouse() {
    point_2d_t p;
    p.push_back(mousex() - getmaxx() / 2);
    p.push_back(getmaxy() / 2 - mousey());
    return p;
}

point_2d_t get_point_by_mouse_click() {
    clearmouseclick(WM_LBUTTONDOWN);
    while (!ismouseclick(WM_LBUTTONDOWN));
    point_2d_t p = get_point_by_mouse();
    printf("point_by_mouse (%d, %d)\n", p[0], p[0]);
    return p;
}

polygon_t draw_polygon_by_mouse(int color = 15, int color_bk = 0, int lw = 9) {
    polygon_t po(0);
    cout << "po.size()=" << po.size() << endl;
    point_2d_t p1 = get_point_by_mouse_click();

    clearmouseclick(WM_RBUTTONDOWN);
    clearmouseclick(WM_LBUTTONDOWN);
    clearmouseclick(WM_RBUTTONUP);
    clearmouseclick(WM_LBUTTONUP);
    po.push_back(p1);
    point_2d_t p = get_point_by_mouse();
    while (true) {
        while (true) {
            p = get_point_by_mouse();
            line_bresenham(po[po.size() - 1][0], po[po.size() - 1][1], p[0], p[1], color, 1);
            line_bresenham(po[po.size() - 1][0], po[po.size() - 1][1], p[0], p[1], color_bk, 1);

            if (ismouseclick(WM_LBUTTONDOWN)) {
                po.push_back(p);
                line_bresenham(po[po.size() - 2][0], po[po.size() - 2][1], po[po.size() - 1][0], po[po.size() - 1][1],
                               color, lw);
                clearmouseclick(WM_LBUTTONDOWN);
                break;
            }
            if (ismouseclick(WM_RBUTTONDOWN)) {
                clearmouseclick(WM_RBUTTONDOWN);
                goto bara;
            }
        }
    }
bara:
    draw_poygon(po, color, lw);
    clearmouseclick(WM_RBUTTONDOWN);
    clearmouseclick(WM_RBUTTONUP);
    clearmouseclick(WM_LBUTTONDOWN);
    clearmouseclick(WM_LBUTTONUP);
    return po;
}


double get_pent(point_2d_t p1, point_2d_t p2) {
    return (p2.y - p1.y) / (double) (p2.x - p1.x);
}

double get_distance(point_2d_t p1, point_2d_t p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

double get_produit_scalaire(point_2d_t p1, point_2d_t p2) {
    return p1.x * p2.x + p1.y * p2.y;
}

double atan2_(double y, double x) {
    if (x > 0) {
        return atan(y / x); //  1 or 4
    } else if (x < 0 && y >= 0) {
        return atan(y / x) + M_PI; //  2
    } else if (x < 0 && y < 0) {
        return atan(y / x) - M_PI; //  3
    } else if (x == 0 && y != 0) {
        return (y > 0) ? M_PI / 2 : -M_PI / 2; // Positive or negative y-axis
    } else {
        return 0; // Undefined angle
    }
}

double get_angle(point_2d_t A, point_2d_t O, point_2d_t B) {
    // Vectors OA and OC
    double OAx = A[0] - O[0], OAy = A[1] - O[1];
    double OCx = B[0] - O[0], OCy = B[1] - O[1];


    double scalaire_p = OAx * OCx + OAy * OCy;
    double vectoriel_p = OAx * OCy - OAy * OCx;

    return atan2_(vectoriel_p, scalaire_p);
}


void is_inside_polygon(polygon_t p, point_2d_t point) {
    double angle = 0;
    for (int i = 0; i < p.size(); i++) {
        angle = angle + get_angle(p[i], point, p[(i + 1) % p.size()]);
    }
    if ((angle <= 1e-6 && angle >= -1e-6)) {
        outtextxy(getmaxx() / 2 + 10 + point[0], getmaxy() / 2 - (10 + point[1]), (char *) "outside");
    } else {
        outtextxy(getmaxx() / 2 + 10 + point[0], getmaxy() / 2 - (10 + point[1]), (char *) "inside");
    }
    printf("angle = %d\n", angle);
}


void draw_point(point_2d_t p, int color = 15, int lw = 1) {
    pixel(p.x, p.y, color, lw);
}


int main() {
    initwindow(800, 500, "Polygon");


    polygon_t po = draw_polygon_by_mouse(13, 0, 1);
    while (true) {
        point_2d_t p = get_point_by_mouse_click();
        draw_point(p,13,9);
        is_inside_polygon(po,p);
        if (ismouseclick(WM_RBUTTONDOWN)) break;
    }
    closegraph();
    return 0;
}
