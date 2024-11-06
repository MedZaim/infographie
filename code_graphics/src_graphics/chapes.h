#include "./../includs/graphics_utils.h"

//  BRESENHAM ALGORITHMS


// Bresenham's line algorithm
void line_bresenham(int x1, int y1, int x2, int y2, int color = 15, int lw = 1) {
    printf("__> line_bresenhame called with ::x1=%d y1=%d x2=%d y2=%d color=%d lw=%d \n", x1, y1, x2, y2, color, lw);
    int dx = x2 - x1;
    int dy = y2 - y1;
    int px = (dx > 0) ? 1 : -1;
    int py = (dy > 0) ? 1 : -1;
    int x = x1, y = y1;
    dx = abs(dx);
    dy = abs(dy);
    long s;


    if (dx > dy) {
        int i = 0;
        s = 2 * dy - dx;
        while (x != x2) {
            if (s > 0) {
                y += py;
                s += 2 * (dy - dx);
            } else {
                s += 2 * dy;
            }
            x += px;
            pixel(x, y, color, lw);
        }
    } else {
        s = 2 * dx - dy;
        int i = 0;
        while (y != y2) {
            if (s > 0) {
                x += px;
                s += 2 * (dx - dy);
            } else {
                s += 2 * dx;
            }
            y += py;
            pixel(x, y, color, lw);
        }
    }
}

void line_bresenham(Point p1, Point p2, int color = 15, int lw = 1) {
    line_bresenham(p1.x, p1.y, p2.x, p2.y, color, lw);
}
// Bresenham's circle algorithm


void cercle_bresenham(int xc, int yc, int r, int color, int wl = 13) {
    int x = 0;
    int y = r;
    int s = 3 - 2 * r;


    for (int i = 1; x <= y; i++) {

        pixel(x + xc, y + yc, color, wl); // Draw pixel5 at (x, y)
        pixel(-x + xc, y + yc, color, wl);
        pixel(x + xc, -y + yc, color, wl);
        pixel(-x + xc, -y + yc, color, wl);

        pixel(y + xc, x + yc, color, wl); // Draw pixel5 at (x, y)
        pixel(-y + xc, x + yc, color, wl);
        pixel(y + xc, -x + yc, color, wl);
        pixel(-y + xc, -x + yc, color, wl);
        if (s > 0) {
            s += 4 * (x - y) + 10;
            x += 1;
            y -= 1;
        } else {
            s += 4 * x + 6;
            x += 1;
        }

    }
}


void bresenham_full_cercle(int xc, int yc, int r2, int r1 = 0, int color = 15, int lw = 13) {
    for (int i = r1; i <= r2; i += 1) {
        cercle_bresenham(xc, yc, i, color, lw);

    }
}

// Bresenham's ellipse algorithm


void ellipse_bresenham(int a, int b, int xc = 0, int yc = 0, int color = 15) {
    int x = 0, y = b;
    int s1 = 2 * b * b - 2 * a * a * b + a * a;  // Initial decision parameter for Region 1
    int s2;


    while (y > 0 && x < a) {
        if (a * a * (y) > b * b * (x)) {// First Region
            std::cout << "// Region I" << std::endl;
            pixel(x + xc, y + yc, color);
            pixel(-x + xc, y + yc, color);
            pixel(x + xc, -y + yc, color);
            pixel(-x + xc, -y + yc, color);

            if (s1 > 0) {
                s1 += b * b * (4 * x + 6) + a * a * (-4 * y + 4);
                x++;
                y--;

            } else {
                s1 += b * b * (4 * x + 6);
                x++;
            }
        } else {
            s2 = b * b * (x) * (x) + a * a * (y) * (y) - a * a * b * b;
            while (y >= 0) {
                std::cout << "// Region II" << std::endl;
                pixel(x + xc, y + yc, color);
                pixel(-x + xc, y + yc, color);
                pixel(x + xc, -y + yc, color);
                pixel(-x + xc, -y + yc, color);

                if (s2 < 0) {
                    s2 += 2 * b * b * x - 2 * a * a * y + a * a;
                    x++;
                    y--;
                } else {
                    s2 += a * a * (-2 * y + 3);
                    y--;
                }
            }
        }

    }
}

//POLYNOMIAL ALGORITHMS
//polynomial line algorithm

void line_polynomial(int xd, int yd, int xf, int yf, int color) {
    int dx = xf - xd;
    int dy = yf - yd;
    int px = (xf > xd) ? 1 : -1;
    int py = (yf > yd) ? 1 : -1;

    pixel(xd, yd, color);
    pixel(xf, yf, color);

    // Use float for accurate line drawing
    if (abs(dx) >= abs(dy)) {
        float a = (float) dy / dx; // Slope
        float b = yd - xd * a;    // Intercept
        for (int x = xd + px; x != xf; x += px) {
            int y = a * x + b;
            pixel(x, y, color);
        }
    } else {
        float a = (float) dx / dy; // Slope for steep lines
        float b = xd - yd * a;    // Intercept
        for (int y = yd + py; y != yf; y += py) {
            int x = a * y + b;
            pixel(x, y, color);
        }
    }
}

//polynomial circle algorithm


void cercle_polynomial(int xc, int yc, int r, int color) {
    double x;
    double y;
    for (int i = 0; x <= r; x += 0.1) {
        y = sqrt(r * r - x * x);
        pixel(x + xc, y + yc, color);
        pixel(-x + xc, y + yc, color);
        pixel(x + xc, -y + yc, color);
        pixel(-x + xc, -y + yc, color);
    }
}

//polynomial ellipse algorithm



void ellipse_polynomial(int a, int b, int xc, int yc, int color) {
    double x = 0;
    double y = b;
    for (int i = 0; x <= a; x += 0.1) {
        y = sqrt(b * b * (1 - (x * x) / (float) (a * a)));
        pixel(x + xc, y + yc, color);
        pixel(-x + xc, y + yc, color);
        pixel(x + xc, -y + yc, color);
        pixel(-x + xc, -y + yc, color);
    }
}

//TRIGONOMETRIC ALGORITHMS
//trigonometric circle algorithm
void circle_trigonometric(int xc, int yc, int r, int color) {
    int x;
    int y;
    for (float i = 0; i < 2 * PI; i = i + 0.002) {
        x = r * cos(i * PI);
        y = r * sin(i * PI);
        pixel(x + xc, y + yc, color);
    }
}


// trigonometric ellipse algorithm
void ellipse_trigonometrique(int a, int b, int xc, int yc, int color) {
    int x;
    int y;
    for (double i = 0; i < 2 * PI; i = i + 0.002) {
        x = a * cos(i * PI);
        y = b * sin(i * PI);
        pixel(x + xc, y + yc, color);

    }
}

//COMPLEX CHAPES
//polynomial rectangle algorithm

void rectangle_(int x1, int y1, int x2, int y2, int color = 15, int lw = 1) {
    printf(" __>rectangle called with ::x1=%d y1=%d x2=%d y2=%d\n", x1, y1, x2, y2);
    line_bresenham(x1, y1, x2, y1, color, lw);
    line_bresenham(x1, y1, x1, y2, color, lw);
    line_bresenham(x2, y1, x2, y2, color, lw);
    line_bresenham(x1, y2, x2, y2, color, lw);
}

void rectangle_(Point p1, Point p2, int color = 15, int lw = 1) {
    rectangle_(p1.x, p1.y, p2.x, p2.y, color, lw);
}

void rectangle_teta(Point p1, Point p2, double teta = 0, int color = 15, int lw = 1) {

    Point center = {(p1.x + p2.x) / 2, (p1.y + p2.y) / 2};

    Point p11 = {p1.x, p2.y};
    Point p22 = {p2.x, p1.y};

    Point p1_ = p1.rotation(teta, center);
    Point p2_ = p2.rotation(teta, center);
    Point p11_ = p11.rotation(teta, center);
    Point p22_ = p22.rotation(teta, center);
    line_bresenham(p1_, p22_, color, lw);
    line_bresenham(p1_, p11_, color, lw);
    line_bresenham(p2_, p11_, color, lw);
    line_bresenham(p2_, p22_, color, lw);
}


void rectangle_by_mouse_click(int color = 15, int color_bk = 0, int lw = 1) {
    int x1, y1, x2, y2;
    clearmouseclick(WM_LBUTTONDOWN);
    while (!ismouseclick(WM_LBUTTONDOWN)) {}
    x1 = mousex() - getmaxx() / 2;
    y1 = getmaxy() / 2 - mousey();


    while (true) {
        rectangle_(x1, y1, x2, y2, color_bk, lw);
        x2 = mousex() - getmaxx() / 2;
        y2 = getmaxy() / 2 - mousey();

        rectangle_(x1, y1, x2, y2, color, lw);
        if (ismouseclick(WM_LBUTTONUP)) {
            break;
        }
    }
}

void rectangle_by_mouse_click_rotate(int color = 15, int color_bk = 0, int lw = 1) {

    Point p1, p2, p3, center;

    double teta = 0;
    clearmouseclick(WM_LBUTTONDOWN);
    while (!ismouseclick(WM_LBUTTONDOWN)) {}
    p1.x = mousex() - getmaxx() / 2;
    p1.y = getmaxy() / 2 - mousey();


    while (true) {
        rectangle_(p1.x, p1.y, p2.x, p2.y, color_bk, lw);
        p2.x = mousex() - getmaxx() / 2;
        p2.y = getmaxy() / 2 - mousey();

        rectangle_(p1.x, p1.y, p2.x, p2.y, color, lw);
        if (ismouseclick(WM_LBUTTONUP)) {
            break;
        }
    }
    center = {(p1.x + p2.x) / 2, (p1.y + p2.y) / 2};
    clearmouseclick(WM_LBUTTONDOWN);
    clearmouseclick(WM_LBUTTONUP);
    while (true) {

        rectangle_teta(p1, p2, teta, color_bk, lw);
        p3.y = getmaxy() / 2 - mousey();
        teta = (double) 2 * PI * ((p3.y - (float) p2.y) / (float) getmaxy());

        rectangle_teta(p1, p2, teta, color, lw);

        if (ismouseclick(WM_LBUTTONDOWN)) {
            break;
        }

    }
}

void ellipse_teta(int a, int b, int xc = 0, int yc = 0, double teta = 0, int color = 15) {
    int x;
    int y;
    Point p;
    for (double i = 0; i < 2 * PI; i = i + 0.03) {
        x = a * cos(i * PI);
        y = b * sin(i * PI);

        p = rotation({x, y}, teta);
        pixel9(p.x + xc, p.y + yc, color);
    }

}

void elipse_p_p(Point p1, Point p2, double teta = 0, int color = 15, int lw = 1) {
    int x;
    int y;
    // printf(" __>elipse_p_p called with ::x1=%d y1=%d x2=%d y2=%d ____teta=%f\n", p1.x, p1.y, p2.x, p2.y, teta);
    int xc = (p1.x + p2.x) / 2;
    int yc = (p1.y + p2.y) / 2;
    Point p;
    int a = abs(p1.x - p2.x) / 2;
    int b = abs(p1.y - p2.y) / 2;
    for (double i = 0; i < 2 * PI; i = i + 0.03) {
        x = a * cos(i * PI);
        y = b * sin(i * PI);

        p = rotation({x, y}, teta);
        // p = {x, y};
        pixel(p.x + xc, p.y + yc, color, lw);
    }
}

void ellipse_p_p_by_mouse(double teta = 0, int color = 15, int color_bk = 0, int lw = 1) {
    Point p1, p2, p3;
    clearmouseclick(WM_LBUTTONDOWN);
    while (!ismouseclick(WM_LBUTTONDOWN)) {}
    p1.x = mousex() - getmaxx() / 2;
    p1.y = getmaxy() / 2 - mousey();


    while (true) {
        elipse_p_p(p1, p2, teta, color_bk, lw);
        p2.x = mousex() - getmaxx() / 2;
        p2.y = getmaxy() / 2 - mousey();

        elipse_p_p(p1, p2, teta, color, lw);
        if (ismouseclick(WM_LBUTTONUP)) {
            break;
        }
    }
    clearmouseclick(WM_LBUTTONDOWN);
    clearmouseclick(WM_LBUTTONUP);
    while (true) {
        elipse_p_p(p1, p2, teta, color_bk, lw);

        p3.y = getmaxy() / 2 - mousey();

        teta = (double) 2 * PI * ((p3.y - (float) p2.y) / (float) getmaxy());

        elipse_p_p(p1, p2, teta, color, lw);

        if (ismouseclick(WM_LBUTTONDOWN)) {
            break;
        }
    }


}

void ellipse_p_p_teta_by_mouse(int color = 15, int color_bk = 0, int lw = 1) {


}

void ellipse_teta_full(int a, int b, int xc = 0, int yc = 0, double teta = 0, int color = 15) {
    for (int b_ = b; b_ >= 0; b_ -= 3) {
        ellipse_teta(a, b_, xc, yc, teta, color);
    }
}

void ellipse_full_by_ligne(int a, int b, int xc = 0, int yc = 0, double teta = 0, int color = 15, int lw = 1) {
    int y;
    int x1, y1, x2, y2;

    for (int x = -a; x <= a; x++) {
        y = (int) (b * sqrt(1 - (x * x / (float) (a * a))));

        Point p1 = rotation({x, y}, teta);
        Point p2 = rotation({x, -y}, teta);

        line_bresenham(p1.x + xc, p1.y + yc, p2.x + xc, p2.y + yc, color, lw);
    }

}

