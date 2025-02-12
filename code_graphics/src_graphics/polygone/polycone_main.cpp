//
// Created by lenovo on 10/11/2024.
//
#include "Polygon.h"


Polygon_ draw_polygon_by_mouse(int color = 15, int color_bk = 0, int lw = 9) {
    Polygon_ p = Polygon_();
    clearmouseclick(WM_LBUTTONDOWN);
    while (!ismouseclick(WM_LBUTTONDOWN)) {}
    Point p1 = {mousex() - getmaxx() / 2, getmaxy() / 2 - mousey()};
    p1.draw(color, lw);
    p.add_point(p1);
    int x, y;
    clearmouseclick(WM_RBUTTONDOWN);
    while (true) {
        while (true) {
            if (ismouseclick(WM_RBUTTONDOWN)) {
                goto barra;
            }

            int x = mousex() - getmaxx() / 2;
            int y = getmaxy() / 2 - mousey();

            line_bresenham(p.points[p.n - 1], {x, y}, color, lw);

            line_bresenham(p.points[p.n - 1], {x, y}, color_bk, lw);

            if (ismouseclick(WM_LBUTTONDOWN)) {
                p.add_point({x, y});
                clearmouseclick(WM_LBUTTONDOWN);
                break;
            }
        }
        line_bresenham(p.points[p.n - 2], p.points[p.n - 1], color, lw);
    }

    barra:
    p.draw(color, lw);
    clearmouseclick(WM_RBUTTONDOWN);
    clearmouseclick(WM_RBUTTONUP);
    clearmouseclick(WM_LBUTTONDOWN);
    clearmouseclick(WM_LBUTTONUP);
    return p;
}


double get_pent(Point p1, Point p2) {
    return (p2.y - p1.y) / (double) (p2.x - p1.x);
}

double get_distance(Point p1, Point p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

double get_produit_scalaire(Point p1, Point p2) {
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

double get_angle(Point A, Point O, Point B) {
    // Vectors OA and OC
    double OAx = A.x - O.x, OAy = A.y - O.y;
    double OCx = B.x - O.x, OCy = B.y - O.y;


    double scalaire_p = OAx * OCx + OAy * OCy;
    double vectoriel_p = OAx * OCy - OAy * OCx;

    return atan2_(vectoriel_p, scalaire_p);
}


void is_inside_polygon(Polygon_ p, Point point) {
    double angle = 0;
    for (int i = 0; i < p.n; i++) {
        angle = angle + get_angle(p.points[i], point, p.points[(i + 1) % p.n]);
    }
    if ((angle <= 1e-6 && angle >= -1e-6)) {
        outtextxy(getmaxx() / 2 + 10 + point.x, getmaxy() / 2 - (10 + point.y), "outside");

    } else {
        outtextxy(getmaxx() / 2 + 10 + point.x, getmaxy() / 2 - (10 + point.y), "inside");

    }
    printf("angle = %d\n", angle);
}

Point get_point_by_mouse() {
    Point p;
    clearmouseclick(WM_LBUTTONDOWN);
    while (!ismouseclick(WM_LBUTTONDOWN)) {}
    p.x = mousex() - getmaxx() / 2;
    p.y = getmaxy() / 2 - mousey();
    clearmouseclick(WM_LBUTTONDOWN);
    printf("point_by_mouse (%d, %d)\n", p.x, p.y);
    return p;
}

void draw_point(Point p, int color = 15, int lw = 1) {
    pixel(p.x, p.y, color, lw);
}

int main() {
    init_graph_();
    int X_MAX = 640, Y_MAX = 480;
    Polygon_ p = draw_polygon_by_mouse(14, 0, 1);
    while (true) {
        Point p1 = get_point_by_mouse();
        draw_point(p1, 13, 9);
        is_inside_polygon(p, p1);
    }

    printf("angle=%f\n", (180 / PI) * get_angle({100, 0}, {0, 0}, {-100, -100}));
    getch();
    closegraph();
    return 0;
}