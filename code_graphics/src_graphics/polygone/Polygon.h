//
// Created by lenovo on 10/11/2024.
//
#include "../../includs/graphics_utils.h"



class Polygon_ {
public:
    Point *points;
    int n;

    Polygon_(Point *points, int n) {
        this->points = points;
        this->n = n;
    }

    Polygon_() {
        this->points = nullptr;
        this->n = 0;
    }

    void add_point(Point p) {
        Point *new_points = new Point[n + 1];
        for (int i = 0; i < n; i++) {
            new_points[i] = points[i];
        }
        new_points[n] = p;
        n++;
        delete[] points;
        points = new_points;
    }

    void draw(int color = 15, int lw = 1) {
        for (int i = 0; i < n - 1; i++) {
            line_bresenham(points[i], points[i + 1], color, lw);
        }
        line_bresenham(points[n - 1], points[0], color, lw);
    }

};



