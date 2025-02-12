#include "graphics.h"
#include <cmath>
#include <vector>
#include <iomanip>
#include <iostream>


using namespace std;
typedef vector<vector<double>> matrix_t;
typedef vector<double> vector_t;

/////////////////////////////////////////////////////////////////////
/////////////// declard functions ///////////////////////////////////
/////////////////////////////////////////////////////////////////////

void line_bresenham(int x1, int y1, int x2, int y2, int color, int lw);

matrix_t operator*(const matrix_t &a, const matrix_t &b);

///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////  GRAPHICS UTILS  ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
void init_graph_() {
    int g = DETECT, m;
    initgraph(&g, &m, (char *) "");
}

void centre(int *x, int *y) {
    *x = *x + getmaxx() / 2;
    *y = getmaxy() / 2 - *y;
}

void d_centre(int *x, int *y) {
    *x = *x - getmaxx() / 2;
    *y = getmaxy() / 2 - *y;
}

void repere(int xc, int yc) {
    int xm = getmaxx() / 2;
    int ym = getmaxy() / 2;
    line(xc - xm, yc + 0, xc + xm, yc + 0);
    line(xc + 0, yc - ym, xc + 0, yc + ym);
}

void pixel5(int x, int y, int color) {
    centre(&x, &y);
    putpixel(x, y, color);
    putpixel(x + 1, y - 1, color);
    putpixel(x - 1, y + 1, color);
    putpixel(x + 1, y + 1, color);
    putpixel(x - 1, y - 1, color);
    d_centre(&x, &y);
}

void pixel9(int x, int y, int color) {
    centre(&x, &y);
    putpixel(x, y, color);
    putpixel(x + 1, y, color);
    putpixel(x, y + 1, color);
    putpixel(x - 1, y, color);
    putpixel(x, y - 1, color);
    putpixel(x + 1, y - 1, color);
    putpixel(x - 1, y + 1, color);
    putpixel(x + 1, y + 1, color);
    putpixel(x - 1, y - 1, color);
    d_centre(&x, &y);
}

void pixel13(int x, int y, int color) {
    putpixel(x, y, color);
    putpixel(x + 1, y, color);
    putpixel(x, y + 1, color);
    putpixel(x + 1, y + 1, color);
    putpixel(x - 1, y, color);
    putpixel(x, y - 1, color);
    putpixel(x - 1, y - 1, color);
    putpixel(x + 1, y - 1, color);
    putpixel(x - 1, y + 1, color);
    putpixel(x + 2, y, color);
    putpixel(x, y + 2, color);
    putpixel(x + 2, y + 2, color);
    putpixel(x - 2, y, color);
    putpixel(x, y - 2, color);
    putpixel(x - 2, y - 2, color);
    putpixel(x + 2, y - 2, color);
    putpixel(x - 2, y + 2, color);
}

void pixel(int x, int y, int color, int lw = 1) {
    centre(&x, &y);
    switch (lw) {
        case 5:
            pixel5(x, y, color);
            break;
        case 9:
            pixel9(x, y, color);
            break;
        case 13:
            pixel13(x, y, color);
            break;
        default:
            putpixel(x, y, color);
            break;
    }
    d_centre(&x, &y);
}

void Tracer_cube(matrix_t resRot, int color = WHITE, int lw = 1) {
    line_bresenham(resRot[0][0], resRot[0][1], resRot[1][0], resRot[1][1], color, lw); // A--> B : plan de projection
    line_bresenham(resRot[0][0], resRot[0][1], resRot[3][0], resRot[3][1], color, lw); // A--> D
    line_bresenham(resRot[0][0], resRot[0][1], resRot[4][0], resRot[4][1], color, lw); // A--> E
    line_bresenham(resRot[1][0], resRot[1][1], resRot[2][0], resRot[2][1], color, lw); // B--> C
    line_bresenham(resRot[1][0], resRot[1][1], resRot[5][0], resRot[5][1], color, lw); // B--> G
    line_bresenham(resRot[2][0], resRot[2][1], resRot[3][0], resRot[3][1], color, lw); // C--> D

    line_bresenham(resRot[2][0], resRot[2][1], resRot[6][0], resRot[6][1], color, lw); // C--> H
    line_bresenham(resRot[3][0], resRot[3][1], resRot[7][0], resRot[7][1], color, lw); // D--> H
    line_bresenham(resRot[4][0], resRot[4][1], resRot[5][0], resRot[5][1], color, lw); // E--> F
    line_bresenham(resRot[4][0], resRot[4][1], resRot[7][0], resRot[7][1], color, lw); // E--> H :
    line_bresenham(resRot[5][0], resRot[5][1], resRot[6][0], resRot[6][1], color, lw); // F--> G
    line_bresenham(resRot[6][0], resRot[6][1], resRot[7][0], resRot[7][1], color, lw); // G--> H

    // Display the labels of the vertices
    setcolor(color);
    for (int i = 0; i < 8; i++) {
        int x = resRot[i][0], y = resRot[i][1], z = resRot[i][2];
        centre(&x, &y);
        char label[3] = {(char) ('A' + i), '\0'}; // Nommer les sommets A, B, C...
        outtextxy(x, y, label);
    }

}

////////////////////////////////////////////////////////////////////////
// Function to perform matrix multiplication for dynamic dimensions
////////////////////////////////////////////////////////////////////////////


string get_dimensions(const matrix_t &mat);


//////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  MATRIX UTILS  /////////////////////////////////////////



// Transformation matrices
const matrix_t Tcv = {{1.0,         0.0,         0.0, 0.0},
                      {0.0,         1.0,         0.0, 0.0},
                      {sqrt(2) / 2, sqrt(2) / 2, 0.0, 0.0},
                      {0.0,         0.0,         0.0, 1.0}};

const matrix_t Tcb = {{1.0,         0.0,     0.0, 0.0},
                      {0.0,         1.0,     0.0, 0.0},
                      {sqrt(3) / 4, 1.0 / 4, 0.0, 0.0},
                      {0.0,         0.0,     0.0, 1.0}};

// Polyhedre class
class Polyhedre {

public:
    matrix_t sommets;
    matrix_t aretes;

    Polyhedre(matrix_t sommets, matrix_t aretes) {
        this->sommets = sommets;
        this->aretes = aretes;
    }

    void affiche() const {
        for (const auto &sommet: sommets) {
            for (double coord: sommet) {
                std::cout << coord << " ";
            }
            std::cout << endl;
        }
    }
};

// matrix_t multiplication function

matrix_t matrix_multiply(matrix_t mat1, matrix_t mat2) {
    int rows = mat1.size();
    int cols = mat2[0].size();
    int inner_dim = mat1[0].size();

    matrix_t res(rows, vector_t(cols, 0));

    if (mat1[0].size() != mat2.size()) {
        cout << "Invalid matrix_t multiplication" << endl;
        cout << get_dimensions(mat1) + "!" + get_dimensions(mat2) << endl;
        return res;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int k = 0; k < inner_dim; ++k) {
                res[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    return res;
}

// Utility function to display a matrix
void affich(matrix_t mat, string label) {
    cout << label << ":[" << endl;
    for (int i = 0; i < mat.size(); i++) {
        cout << "     {";
        for (int j = 0; j < mat[i].size(); j++) {
            cout << setw(8) << std::round(mat[i][j] * 1000) / 1000 << " ";
        }
        cout << "}" << endl;
    }
    cout << "]" << endl;
}

matrix_t inverse(const matrix_t &mat) {
    int n = mat.size();

    // Check if the matrix_t is square
    if (n == 0 || mat[0].size() != n) {
        cout << "matrix_t must be square to calculate the inverse." << endl;
        return {};
    }

    // Create an augmented matrix_t [mat | identity]
    matrix_t augmented(n, vector<double>(2 * n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            augmented[i][j] = mat[i][j];
        }
        augmented[i][n + i] = 1.0; // Append the identity matrix
    }

    // Perform Gaussian elimination
    for (int i = 0; i < n; ++i) {
        // Find the pivot
        double pivot = augmented[i][i];
        if (fabs(pivot) < 1e-9) {
            cout << "matrix_t is singular and cannot be inverted." << endl;
            return {};
        }

        // Normalize the pivot row
        for (int j = 0; j < 2 * n; ++j) {
            augmented[i][j] /= pivot;
        }

        // Eliminate other rows
        for (int k = 0; k < n; ++k) {
            if (k == i) continue;
            double factor = augmented[k][i];
            for (int j = 0; j < 2 * n; ++j) {
                augmented[k][j] -= factor * augmented[i][j];
            }
        }
    }

    // Extract the inverse matrix_t from the augmented matrix
    matrix_t inv(n, vector_t(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inv[i][j] = augmented[i][j + n];
        }
    }
    return inv;
}

matrix_t transpose(const matrix_t &mat) {
    int rows = mat.size();
    int cols = mat[0].size();

    matrix_t transposed(cols, vector_t(rows, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposed[j][i] = mat[i][j];
        }
    }

    return transposed;
}

string get_dimensions(const matrix_t &mat) {
    int rows, cols;
    rows = mat.size();
    cols = mat[0].size();
    return "[" + to_string(rows) + "x" + to_string(cols) + "]";
}




//////////////////////////////////////////////////////////////////////////
/////////////////////////////////////  chapes  ///////////////////////////
/////////////////////////////////////////////////////////////////////////////



#include "random"
#include "iostream"

#define PI 3.14159265358979323846


class Point {
public:
    int x, y;

    Point() {}

    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }

    Point rotation(double teta = 0, Point C = {0, 0}) {
        int x_ = (this->x - C.x) * cos(teta) - (this->y - C.y) * sin(teta) + C.x;
        int y_ = (this->x - C.x) * sin(teta) + (this->y - C.y) * cos(teta) + C.y;
        return {x_, y_};
    }

    void draw(int color, int lw = 1) {
        pixel(x, y, color, lw);
    }
};

Point rotation(Point p, double teta) {
    int x_ = p.x * cos(teta) - p.y * sin(teta);
    int y_ = p.x * sin(teta) + p.y * cos(teta);
    return {x_, y_};
}

void line_bresenham(int x1, int y1, int x2, int y2, int color, int lw);

int random(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

double random(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(min, max);
    return dist(gen);
}

void line_bresenham(int x1, int y1, int x2, int y2, int color = 15, int lw = 1);

void line_bresenham(Point p1, Point p2, int color = 15, int lw = 1);

class Line {
public:
    Point points[2];

    Line() {
        points[0] = {0, 0};
        points[1] = {0, 0};
    }

    Line(Point p1, Point p2) {
        points[0] = p1;
        points[1] = p2;
    }

    void draw(int color = 15, int lw = 1) {
        line_bresenham(points[0], points[1], color, lw);
    }

    Point get_medium() {
        return {(points[0].x + points[1].x) / 2, (points[0].y + points[1].y) / 2};
    }

    Line rotation(double teta) {
        Line l;
        l.points[0] = points[0].rotation(teta, get_medium());
        l.points[1] = points[1].rotation(teta, get_medium());
        return l;
    }

    Point get_point(int i) {
        return points[i];
    }

    double get_pente() {
        return (points[1].y - points[0].y) / (double) (points[1].x - points[0].x);
    }

    Point get_intersection(Line l) {
        double a1 = get_pente();
        double a2 = l.get_pente();
        double b1 = points[0].y - a1 * points[0].x;
        double b2 = l.get_point(0).y - a2 * l.get_point(0).x;

        if (a1 == a2) {
            throw std::runtime_error("Lines are parallel and do not intersect.");
        }

        double x = (b2 - b1) / (a1 - a2);
        double y = a1 * x + b1;
        return {(int) x, (int) y};
    }


    void log() {
        std::cout << "Line {p1(" << points[0].x << ", " << points[0].y << ")--p2(" <<
                  points[1].x << ", " << points[1].y << ")" << std::endl;

    }
};

Point get_intersection(Point p1, Point p2, Point p3, Point p4) {
    double a1 = (p2.y - p1.y) / (double) (p2.x - p1.x);
    double a2 = (p4.y - p3.y) / (double) (p4.x - p3.x);
    double b1 = p1.y - a1 * p1.x;
    double b2 = p3.y - a2 * p3.x;

    if (a1 == a2) {
        throw std::runtime_error("Lines are parallel and do not intersect.");
    }

    double x = (b2 - b1) / (a1 - a2);
    double y = a1 * x + b1;
    return {(int) x, (int) y};
}

Line ajuster(Line l1, Line l2) {
    Point p = l1.get_intersection(l2);
    return {l2.get_point(0), p};

}

Line ligne_by_mouse(int color = 15, int color_bk = 0, int lw = 1) {
    int x1, y1, x2, y2;
    while (true) {

        while (!ismouseclick(WM_LBUTTONDOWN)) {}
        x1 = mousex() - getmaxx() / 2;
        y1 = getmaxy() / 2 - mousey();
        clearmouseclick(WM_LBUTTONDOWN);

        while (!ismouseclick(WM_LBUTTONDOWN)) {
            clearmouseclick(WM_LBUTTONDOWN);
            x2 = mousex() - getmaxx() / 2;
            y2 = getmaxy() / 2 - mousey();
            line_bresenham(x1, y1, x2, y2, color, 1);
            line_bresenham(x1, y1, x2, y2, color_bk, 1);
            if (ismouseclick(WM_RBUTTONDOWN)) {
                goto out;
            }

        }
    }
    out:
    //line_bresenham(x1, y1, x2, y2, color, lw);
    clearmouseclick(WM_LBUTTONDOWN);
    clearmouseclick(WM_RBUTTONDOWN);
    return {Point(x1, y1), Point(x2, y2)};
}
//  BRESENHAM ALGORITHMS


// Bresenham's line algorithm
void line_bresenham(int x1, int y1, int x2, int y2, int color, int lw) {
    // printf("__> line_bresenhame called with ::x1=%d y1=%d x2=%d y2=%d color=%d lw=%d \n", x1, y1, x2, y2, color, lw);
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

/*void line_bresenham(double x1, double y1, double x2, double y2, int color, int lw) {
    line_bresenham((int) x1, (int) y1, (int) x2, (int) y2, color, lw);
}*/

void line_bresenham(Point p1, Point p2, int color, int lw) {
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


void cercle_full_bresenham(int xc, int yc, int r2, int r1 = 0, int color = 15, int lw = 13) {
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

void line_polynomial(int xd, int yd, int xf, int yf, int color, int lw = 1) {
    int dx = xf - xd;
    int dy = yf - yd;
    int px = (xf > xd) ? 1 : -1;
    int py = (yf > yd) ? 1 : -1;

    pixel(xd, yd, color, lw);
    pixel(xf, yf, color, lw);

    // Use float for accurate line drawing
    if (abs(dx) >= abs(dy)) {
        float a = (float) dy / dx; // Slope
        float b = yd - xd * a;    // Intercept
        for (int x = xd + px; x != xf; x += px) {
            int y = a * x + b;
            pixel(x, y, color, lw);
        }
    } else {
        float a = (float) dx / dy; // Slope for steep lines
        float b = xd - yd * a;    // Intercept
        for (int y = yd + py; y != yf; y += py) {
            int x = a * y + b;
            pixel(x, y, color, lw);
        }
    }
}

void line_polynomial(Point p1, Point p2, int color, int lw = 1) {
    line_polynomial(p1.x, p1.y, p2.x, p2.y, color, lw);
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
        pixel(p.x + xc, p.y + yc, color);
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

void ellipse_p_p_by_mouse(double teta = 0, int color = 15, int color_bk = 0, int lw = 9) {
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

////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////  3D transforamtions functions  //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
// Function to print matrix for debugging
void print_matrix(const matrix_t matrix) {
    cout << "[";
    for (int i = 0; i < matrix.size(); ++i) {
        cout << "[";
        for (int j = 0; j < matrix[0].size(); ++j) {
            cout << matrix[i][j] << "  ";
        }
        cout << "]" << endl;
    }
    cout << "]";
    cout << endl;
}

matrix_t rotation_x(matrix_t cube, double angle) {

    matrix_t mat_rot_X = {
            {1, 0,           0,          0},
            {0, cos(angle),  sin(angle), 0},
            {0, -sin(angle), cos(angle), 0},
            {0, 0,           0,          1}
    };
    return cube * mat_rot_X;
}

matrix_t rotation_y(matrix_t cube, double angle) {

    matrix_t mat_rot_y = {
            {cos(angle), 0, -sin(angle), 0},
            {0,          1, 0,           0},
            {sin(angle), 0, cos(angle),  0},
            {0,          0, 0,           1}
    };
    return  cube*mat_rot_y;
}

matrix_t rotation_z(matrix_t cube, double angle) {

    matrix_t mat_rot_z = {
            {cos(angle),  sin(angle), 0, 0},
            {-sin(angle), cos(angle), 0, 0},
            {0,           0,          1, 0},
            {0,           0,          0, 1}
    };
    return  cube * mat_rot_z;
}

matrix_t scaling(matrix_t cube, double sx, double sy, double sz) {
    matrix_t mat_scale = {
            {sx, 0,  0,  0},
            {0,  sy, 0,  0},
            {0,  0,  sz, 0},
            {0,  0,  0,  1}
    };
    return cube * mat_scale;
}

matrix_t operator*(const matrix_t &a, const matrix_t &b) {
    return matrix_multiply(a, b);
}


matrix_t get_perspective_matrix_Z_d(double d) {
    matrix_t T_perspective = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 1.0 / d},
            {0, 0, 0, 0}
    };
    return T_perspective;
}

matrix_t get_perspective_calculated_matrix(vector_t viewpoint, vector_t r0, vector_t n) {
    double a = viewpoint[0];
    double b = viewpoint[1];
    double c = viewpoint[2];

    double x0 = r0[0];
    double y0 = r0[1];
    double z0 = r0[2];

    double n1 = n[0];
    double n2 = n[1];
    double n3 = n[2];

    double d0 = n1 * x0 + n2 * y0 + n3 * z0;

    matrix_t mat_perspective = {
            {1, 0, 0, n1 / d0},
            {0, 1, 0, n2 / d0},
            {0, 0, 1, n3 / d0},
            {0, 0, 0, 1}
    };
    matrix_t mat_translation_to_center = {
            {1,  0,  0,  0},
            {0,  1,  0,  0},
            {0,  0,  1,  0},
            {-a, -b, -c, 1}
    };


    matrix_t mat_translation_invers = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {a, b, c, 1}
    };
    return mat_translation_to_center * mat_perspective * mat_translation_invers;
};

matrix_t get_perspective_calculated_matrix(double a, double b, double c, double x0, double y0, double z0, double n1, double n2,
                                  double n3) {
    vector_t viewpoint = {a, b, c};
    vector_t r0 = {x0, y0, z0};
    vector_t n = {n1, n2, n3};
    return get_perspective_calculated_matrix(viewpoint, r0, n);
}

matrix_t divid_on_w(matrix_t points) {
    matrix_t res = points;
    for (int i = 0; i < points.size(); ++i) {
        for (int j = 0; j < points[0].size(); ++j) {
            res[i][j] = points[i][j] / points[i][3];
        }
    }
    return res;
}

// Perspective projection matrix for viewpoint at (a,b,c)
matrix_t perspective(matrix_t points, vector_t viewpoint, vector_t r0, vector_t n) {
   matrix_t res = points ;//* get_perspective_matrix(viewpoint, r0, n);
    return divid_on_w(res);
};

// Perspective projection matrix for viewpoint at (a,b,c)
matrix_t perspective(vector_t point, vector_t viewpoint, vector_t r0, vector_t n) {
    matrix_t points = {point};
    return perspective(points, viewpoint, r0, n);
};

matrix_t perspective(matrix_t cube, double a, double b, double c, double x0, double y0, double z0, double n1, double n2,
                     double n3) {
    vector_t viewpoint = {a, b, c};
    vector_t r0 = {x0, y0, z0};
    vector_t n = {n1, n2, n3};
    return perspective(cube, viewpoint, r0, n);
};

matrix_t cavalier(matrix_t points) {
    matrix_t result = points * Tcv;
    return result;
}

void centre3D(int *X, int *Y, int *Z) {
    int centreX = getmaxx() / 2;
    int centreY = getmaxy() / 2;
    int length = 350;

    // Ajuster les coordonnées X et Y pour centrer le cube
    *X = *X + centreX;
    *Y = centreY - *Y;

    // Calculer la perspective en utilisant le Z
    double facteur = (double) length / (length + *Z); // Facteur de perspective
    *X = (int) (*X * facteur);
    *Y = (int) (*Y * facteur);
}

matrix_t get_cavalier_matrix(double angle) {
    double angle_rad = angle * PI / 180;
    return Tcv;
}
////////////////////////////////////////////////////////////////////////////////////////////////

/*
vector_t find_intersection(const vector_t p1, const vector_t p2,const vector_t p3, const vector_t p4) {
    double a1 = (p2[1] - p1[1]) / (double) (p2[0] - p1[0]);
    double a2 = (p4[1] - p3[1]) / (double) (p4[0] - p3[0]);
    double b1 = p1[1] - a1 * p1[0];
    double b2 = p3[1] - a2 * p3[0];

    if (a1 == a2) {
        throw std::runtime_error("Lines are parallel and do not intersect.");
    }

    double x = (b2 - b1) / (a1 - a2);
    double y = a1 * x + b1;
    vector_t intr_point = {x, y};
    return intr_point;
}
/*  Point p = get_intersection(Point(p1[0], p1[1]), Point(p2[0], p2[1]), Point(p3[0], p3[1]), Point(p4[0], p4[1]){
    vector_t intr_point(2)={p.x, p.y};
    return intr_point;
}*/
/*
vector_t find_intersection(double x1, double y1, double x2, double y2) {
    vector_t vecteur1 = {x1, y1};
    vector_t vecteur2 = {x2, y2};
    return find_intersection(vecteur1, vecteur2);
}

void tracer_points_de_fuit(matrix_t resRot, int color = YELLOW, int lw = 1) {
    {
        vector_t vecteur01 = find_intersection(resRot[0][0], resRot[0][1],resRot[1][0], resRot[1][1], resRot[3][0], resRot[3][1]);
        vector_t vecteur02 = find_intersection(resRot[4][0], resRot[4][1], resRot[7][0], resRot[7][1]);

        vector_t resultat = find_intersection(vecteur01, vecteur02);


        line_bresenham(resRot[0][0], resRot[0][1], resultat[0], resultat[1], color, lw);
        line_bresenham(resRot[4][0], resRot[4][1], resultat[0], resultat[1], color, lw);
        line_bresenham(resRot[1][0], resRot[1][1], resultat[0], resultat[1], color, lw);
        line_bresenham(resRot[5][0], resRot[5][1], resultat[0], resultat[1], color, lw);


        vector_t vecteur11 = find_intersection(resRot[0][0], resRot[0][1], resRot[4][0], resRot[4][1]);
        vector_t vecteur12 = find_intersection(resRot[3][0], resRot[3][1], resRot[7][0], resRot[7][1]);
        vector_t resultat1 = find_intersection(vecteur11, vecteur12);


        line_bresenham(resRot[0][0], resRot[0][1], resultat1[0], resultat1[1], color, lw);
        line_bresenham(resRot[3][0], resRot[3][1], resultat1[0], resultat1[1], color, lw);
        line_bresenham(resRot[1][0], resRot[1][1], resultat1[0], resultat1[1], color, lw);
        line_bresenham(resRot[5][0], resRot[5][1], resultat1[0], resultat1[1], color, lw);

        vector_t vecteur21 = find_intersection(resRot[0][0], resRot[0][1], resRot[1][0], resRot[1][1]);
        vector_t vecteur22 = find_intersection(resRot[6][0], resRot[6][1], resRot[7][0], resRot[7][1]);
        vector_t resultat2 = find_intersection(vecteur21, vecteur22);


        line_bresenham(resRot[6][0], resRot[6][1], resultat2[0], resultat2[1], color, lw);
        line_bresenham(resRot[0][0], resRot[0][1], resultat2[0], resultat2[1], color, lw);
        line_bresenham(resRot[3][0], resRot[3][1], resultat2[0], resultat2[1], color, lw);
        line_bresenham(resRot[7][0], resRot[7][1], resultat2[0], resultat2[1], color, lw);
    };
    */
//////////////////////////////////////////////////////////////////////////////////////////


#include <graphics.h>
#include <iostream>
#include <cmath>

using namespace std;

// Fonction pour calculer les points d'une courbe de Bézier linéaire
void bezierLinear(int x0, int y0, int x1, int y1) {
    for (float t = 0; t <= 1; t += 0.001) {
        float x = (1 - t) * x0 + t * x1;
        float y = (1 - t) * y0 + t * y1;
        putpixel(x, y, WHITE);
    }
}

// Fonction pour calculer les points d'une courbe de Bézier quadratique
void bezierQuadratic(int x0, int y0, int x1, int y1, int x2, int y2) {
    for (float t = 0; t <= 1; t += 0.001) {
        float x = pow(1 - t, 2) * x0 + 2 * (1 - t) * t * x1 + pow(t, 2) * x2;
        float y = pow(1 - t, 2) * y0 + 2 * (1 - t) * t * y1 + pow(t, 2) * y2;
        putpixel(x, y, WHITE);
    }
}

// Fonction pour calculer les points d'une courbe de Bézier cubique
void bezierCubic(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3) {
    for (float t = 0; t <= 1; t += 0.001) {
        float x = pow(1 - t, 3) * x0 + 3 * pow(1 - t, 2) * t * x1 + 3 * (1 - t) * pow(t, 2) * x2 + pow(t, 3) * x3;
        float y = pow(1 - t, 3) * y0 + 3 * pow(1 - t, 2) * t * y1 + 3 * (1 - t) * pow(t, 2) * y2 + pow(t, 3) * y3;
        pixel(x, y, WHITE);
    }
}


matrix_t get_parallelogram(double a, double b, double c, double is_homogen = 0) {
    if (is_homogen) {

        return {
                {0, 0, 0, 1},   // A
                {a, 0, 0, 1},   // B
                {a, b, 0, 1},   // C
                {0, b, 0, 1},   // D

                {0, 0, c, 1},   // E
                {a, 0, c, 1},   // F
                {a, b, c, 1},   // G
                {0, b, c, 1},   // H
        };
    } else {
        return {
                {0, 0, 0},   // A
                {a, 0, 0},   // B
                {a, b, 0},   // C
                {0, b, 0},   // D

                {0, 0, c},   // E
                {a, 0, c},   // F
                {a, b, c},   // G
                {0, b, c},   // H
        };
    }
}