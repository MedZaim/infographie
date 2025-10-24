#include "C:\Users\LENOVO i7\Desktop\ligacy_progects\infographie\code_graphics\Graphics\graphics.h"
#include <cmath>
#include <vector>
#include <iomanip>
#include <iostream>


using namespace std;
typedef vector<vector<double> > matrix_t;
typedef vector<double> vector_t;

typedef vector<double> point_2d_t;
typedef vector<point_2d_t> polygon_t;

typedef vector<double> point_3d_h_t;

typedef vector<point_2d_t> segment_t;
typedef vector_t point_t;

/////////////////////////////////////////////////////////////////////
/////////////// declared functions ///////////////////////////////////
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

void repere(int xc, int yc) {
    int xm = getmaxx() / 2;
    int ym = getmaxy() / 2;
    line(xc - xm, yc + 0, xc + xm, yc + 0);
    line(xc + 0, yc - ym, xc + 0, yc + ym);
}

void pixel5(int x, int y, int color) {
    putpixel(x, y, color);
    putpixel(x + 1, y - 1, color);
    putpixel(x - 1, y + 1, color);
    putpixel(x + 1, y + 1, color);
    putpixel(x - 1, y - 1, color);
}

void pixel9(int x, int y, int color) {
    putpixel(x, y, color);
    putpixel(x + 1, y, color);
    putpixel(x, y + 1, color);
    putpixel(x - 1, y, color);
    putpixel(x, y - 1, color);
    putpixel(x + 1, y - 1, color);
    putpixel(x - 1, y + 1, color);
    putpixel(x + 1, y + 1, color);
    putpixel(x - 1, y - 1, color);
}

void pixeseg13(int x, int y, int color) {
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
    x += getmaxx() / 2;
    y = getmaxy() / 2 - y;
    switch (lw) {
        case 5:
            pixel5(x, y, color);
            break;
        case 9:
            pixel9(x, y, color);
            break;
        case 13:
            pixeseg13(x, y, color);
            break;
        default:
            putpixel(x, y, color);
            break;
    }
}

void display_vertices_labels(const matrix_t &points, int color = WHITE) {
    setcolor(color);
    for (size_t i = 0; i < points.size(); ++i) {
        int x = points[i][0] + getmaxx() / 2;
        int y = getmaxy() / 2 - points[i][1];
        char label[4];
        snprintf(label, sizeof(label), "%c", 'A' + i); // Label vertices as A, B, C, ...
        outtextxy(x, y, label);
    }
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
        x += getmaxx() / 2;
        y = getmaxy() / 2 - y;
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
const matrix_t Tcv = {
    {1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {sqrt(2) / 2, sqrt(2) / 2, 0.0, 0.0},
    {0.0, 0.0, 0.0, 1.0}
};

const matrix_t Tcb = {
    {1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {sqrt(2) / 4, sqrt(2) / 4, 0.0, 0.0},
    {0.0, 0.0, 0.0, 1.0}
};

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


point_2d_t rotation_point(point_2d_t p, double teta = 0, point_2d_t C = {0, 0}) {
    double x_ = (p[0] - C[0]) * cos(teta) - (p[1] - C[1]) * sin(teta) + C[0];
    double y_ = (p[0] - C[0]) * sin(teta) + (p[1] - C[1]) * cos(teta) + C[1];
    return {x_, y_};
}


point_2d_t rotation(point_2d_t p, double teta) {
    double x_ = p[0] * cos(teta) - p[1] * sin(teta);
    double y_ = p[0] * sin(teta) + p[1] * cos(teta);
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

void line_bresenham(point_2d_t p1, point_2d_t p2, int color = 15, int lw = 1);


void draw_seg(segment_t seg, int color = 15, int lw = 1) {
    line_bresenham(seg[0], seg[1], color, lw);
}

point_2d_t get_medium(segment_t seg) {
    return {(seg[0][0] + seg[1][0]) / 2, (seg[0][1] + seg[1][1]) / 2};
}

segment_t rotation_seg(segment_t seg, double teta) {
    return {rotation_point(seg[0], teta, get_medium(seg)), rotation_point(seg[1], teta, get_medium(seg))};
}


double get_pente(segment_t seg) {
    return (seg[1][1] - seg[0][1]) / (double) (seg[1][0] - seg[0][0]);
}

point_2d_t get_intersection(segment_t seg1, segment_t seg2) {
    double a1 = get_pente(seg1);
    double a2 = get_pente(seg2);
    double b1 = seg1[0][1] - a1 * seg1[0][0];
    double b2 = seg2[0][1] - a2 * seg2[0][0];

    if (a1 == a2) {
        throw std::runtime_error("Lines are parallel and do not intersect.");
    }

    double x = (b2 - b1) / (a1 - a2);
    double y = a1 * x + b1;
    point_2d_t p = {x, y};
    cout<<"p created successfully"<<endl;
    return p;
}


void log(segment_t seg) {
    std::cout << "segment {p1(" << seg[0][0] << ", " << seg[0][1] << "), p2("
            << seg[1][0] << ", " << seg[1][1] << ")}" << std::endl;
}


point_2d_t get_intersection(point_2d_t p1, point_2d_t p2, point_2d_t p3, point_2d_t p4) {
return get_intersection({p1, p2}, {p3, p4});
}

segment_t ajuster(segment_t seg1, segment_t seg2) {
    point_t p = get_intersection(seg1, seg2);
    segment_t s= {seg2[0], p};
    cout<<"s created successfully"<<endl;
    return s;
}

// Function to draw a line using mouse input
segment_t ligne_by_mouse(int color = 15, int color_bk = 0, int lw = 1) {
    double x1, y1, x2, y2;

    // Wait for the first mouse click (left button)
    clearmouseclick(WM_LBUTTONDOWN);
    while (!ismouseclick(WM_LBUTTONDOWN)) {
        delay(10); // Avoid busy-waiting
    }
    x1 = mousex() - getmaxx() / 2;
    y1 = getmaxy() / 2 - mousey();
    clearmouseclick(WM_LBUTTONDOWN);

    // Draw the line dynamically while moving the mouse
    bool drawing = true;
    while (drawing) {
        // Get the current mouse position
        x2 = mousex() - getmaxx() / 2;
        y2 = getmaxy() / 2 - mousey();

        // Draw the line in the current color
        line_bresenham(x1, y1, x2, y2, color, lw);

        // Check for right-click to finish drawing
        if (ismouseclick(WM_RBUTTONDOWN)) {
            drawing = false;
            clearmouseclick(WM_RBUTTONDOWN);
        } else {
            // Erase the previous line by drawing it in the background color
            delay(10); // Small delay to reduce flickering
            line_bresenham(x1, y1, x2, y2, color_bk, lw);
        }
    }

    // Draw the final line in the specified color and width
    line_bresenham(x1, y1, x2, y2, color_bk, lw);
segment_t s = {{x1, y1}, {x2, y2}};
    return s;
}

//  BRESENHAM ALGORITHMS


// Bresenham's line algorithm
void line_bresenham(int x1, int y1, int x2, int y2, int color, int lw) {
    //  printf("__> line_bresenham called with :: x1=%d y1=%d x2=%d y2=%d color=%d lw=%d \n", x1, y1, x2, y2, color, lw);
    if (x1 == x2 && y1 == y2) {
        pixel(x1, y1, color, lw);
        printf("line_bresenham :///!!\\\\ p1==p2\n");
        return;
    }
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int px = (x2 > x1) ? 1 : -1;
    int py = (y2 > y1) ? 1 : -1;

    int x = x1, y = y1;
    pixel(x, y, color, lw); // Ensure first pixel is drawn

    long s;
    if (dx > dy) {
        // Case: horizontal-ish line
        s = 2 * dy - dx;
        do {
            x += px;
            if (s >= 0) {
                y += py;
                s -= 2 * dx;
            }
            s += 2 * dy;
            pixel(x, y, color, lw);
        } while (x != x2);
    } else {
        // Case: vertical-ish line
        s = 2 * dx - dy;
        do {
            y += py;
            if (s >= 0) {
                x += px;
                s -= 2 * dy;
            }
            s += 2 * dx;
            pixel(x, y, color, lw);
        } while (y != y2);
    }
}


void line_bresenham(point_2d_t p1, point_2d_t p2, int color, int lw) {
    line_bresenham(p1[0], p1[1], p2[0], p2[1], color, lw);
}


// Bresenham's circle algorithm


void cercle_bresenham(int xc, int yc, int r, int color, int wl = 1) {
    int x = 0;
    int y = r;
    int s = 3 - 2 * r;


    for (int i = 1; x <= y; i++) {
        pixel(x + xc, y + yc, color, wl); // Draw  at (x, y)
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
    int s1 = 2 * b * b - 2 * a * a * b + a * a; // Initial decision parameter for Region 1
    int s2;


    while (y > 0 && x < a) {
        if (a * a * (y) > b * b * (x)) {
            // First Region
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
        float b = yd - xd * a; // Intercept
        for (int x = xd + px; x != xf; x += px) {
            int y = a * x + b;
            pixel(x, y, color, lw);
        }
    } else {
        float a = (float) dx / dy; // Slope for steep lines
        float b = xd - yd * a; // Intercept
        for (int y = yd + py; y != yf; y += py) {
            int x = a * y + b;
            pixel(x, y, color, lw);
        }
    }
}

void line_polynomial(point_2d_t p1, point_2d_t p2, int color, int lw = 1) {
    line_polynomial(p1[0], p1[1], p2[0], p2[1], color, lw);
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

void rectangle_(point_2d_t p1, point_2d_t p2, int color = 15, int lw = 1) {
    rectangle_(p1[0], p1[1], p2[0], p2[1], color, lw);
}

void rectangle_teta(point_2d_t p1, point_2d_t p2, double teta = 0, int color = 15, int lw = 1) {
    cout<<"rectangle_teta called  with p1=("<<p1[0]<<", "<<p1[1]<<") p2=("<<p2[0]<<", "<<p2[1]<<") teta="<<teta<<endl;
    point_2d_t center = {(p1[0] + p2[0]) / 2, (p1[1] + p2[1]) / 2};

    point_2d_t p11 = {p1[0], p2[1]};
    point_2d_t p22 = {p2[0], p1[1]};

    point_2d_t p1_ = rotation_point(p1, teta, center);
    point_2d_t p2_ = rotation_point(p2, teta, center);
    point_2d_t p11_ = rotation_point(p11, teta, center);
    point_2d_t p22_ = rotation_point(p22, teta, center);
    line_bresenham(p1_, p22_, color, lw);
    line_bresenham(p1_, p11_, color, lw);
    line_bresenham(p2_, p11_, color, lw);
    line_bresenham(p2_, p22_, color, lw);
}


void rectangle_by_mouse_click(int color = 15, int color_bk = 0, int lw = 1) {
    int x1, y1, x2, y2;
    clearmouseclick(WM_LBUTTONDOWN);
    while (!ismouseclick(WM_LBUTTONDOWN)) {
    }
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
    point_2d_t p1(2), p2(2), p3(2);  // Initialize with 2 elements (x, y)
    point_2d_t center(2);

    double teta = 0;
    clearmouseclick(WM_LBUTTONDOWN);
    while (!ismouseclick(WM_LBUTTONDOWN)) {
    }
    p1[0] = mousex() - getmaxx() / 2;
    p1[1] = getmaxy() / 2 - mousey();


    while (true) {
        rectangle_(p1[0], p1[1], p2[0], p2[1], color_bk, lw);
        p2[0] = mousex() - getmaxx() / 2;
        p2[1] = getmaxy() / 2 - mousey();

        rectangle_(p1[0], p1[1], p2[0], p2[1], color, lw);
        if (ismouseclick(WM_LBUTTONUP)) {
            rectangle_(p1[0], p1[1], p2[0], p2[1], color_bk, lw);
            break;
        }
    }

    clearmouseclick(WM_LBUTTONDOWN);
    clearmouseclick(WM_LBUTTONUP);
    while (true) {
        rectangle_teta(p1, p2, teta, color_bk, 1);
        p3[1] = getmaxy() / 2 - mousey();
        teta = (double) 2 * PI * ((p3[1] - (double) p2[1]) / (double) getmaxy());

        rectangle_teta(p1, p2, teta, color, 1);

        if (ismouseclick(WM_LBUTTONDOWN)) {
            rectangle_teta(p1, p2, teta, color, lw);
            break;
        }
    }
}

void ellipse_teta(int a, int b, int xc = 0, int yc = 0, double teta = 0, int color = 15) {
    double x, y;
    point_2d_t p;
    for (double i = 0; i < 2 * PI; i = i + 0.03) {
        x = a * cos(i * PI);
        y = b * sin(i * PI);

        p = rotation({x, y}, teta);
        pixel(p[0] + xc, p[1] + yc, color);
    }
}

void ellipse_p_p(point_2d_t p1, point_2d_t p2, double teta = 0, int color = 15, int lw = 1) {
    double x, y;
    // printf(" __>elipse_p_p called with ::x1=%d y1=%d x2=%d y2=%d ____teta=%f\n", p1[0], p1[1], p2[0], p2[1], teta);
    double xc = (p1[0] + p2[0]) / 2;
    double yc = (p1[1] + p2[1]) / 2;
    point_2d_t p(2);
    double a = abs(p1[0] - p2[0]) / 2;
    double b = abs(p1[1] - p2[1]) / 2;
    for (double i = 0; i < 2 * PI; i = i + 0.004) {
        x = a * cos(i * PI);
        y = b * sin(i * PI);

        p = rotation({x, y}, teta);
        // p = {x, y};
        pixel(p[0] + xc, p[1] + yc, color, lw);
    }

}

void ellipse_p_p_by_mouse(double teta = 0, int color = 15, int color_bk = 0, int lw = 9) {
    point_2d_t p1(2), p2(2), p3(2);  // Initialize with 2 elements (x, y)

    clearmouseclick(WM_LBUTTONDOWN);
    while (!ismouseclick(WM_LBUTTONDOWN)) {
    }
    p1[0] = mousex() - getmaxx() / 2;
    p1[1] = getmaxy() / 2 - mousey();


    while (true) {
        ellipse_p_p(p1, p2, teta, color_bk, 1);
        p2[0] = mousex() - getmaxx() / 2;
        p2[1] = getmaxy() / 2 - mousey();

        ellipse_p_p(p1, p2, teta, color, 1);
        if (ismouseclick(WM_LBUTTONUP)) {
            break;
        }
    }
    clearmouseclick(WM_LBUTTONDOWN);
    clearmouseclick(WM_LBUTTONUP);
    while (true) {
        ellipse_p_p(p1, p2, teta, color_bk, 1);

        p3[1] = getmaxy() / 2 - mousey();

        teta = (double) 2 * PI * ((p3[1] - (double) p2[1]) / (double) getmaxy());

        ellipse_p_p(p1, p2, teta, color, 1);

        if (ismouseclick(WM_LBUTTONDOWN)) {
            ellipse_p_p(p1, p2, teta, color, lw);
            break;
        }
    }
}



void ellipse_teta_full(int a, int b, int xc = 0, int yc = 0, double teta = 0, int color = 15) {
    for (int b_ = b; b_ >= 0; b_ -= 3) {
        ellipse_teta(a, b_, xc, yc, teta, color);
    }
}

void ellipse_full_by_ligne(int a, int b, int xc = 0, int yc = 0, double teta = 0, int color = 15, int lw = 1) {
    double y;
    double x1, y1, x2, y2;

    for (double x = -a; x <= a; x++) {
        y = (int) (b * sqrt(1 - (x * x / (float) (a * a))));

        point_2d_t p1 = rotation({x, y}, teta);
        point_2d_t p2 = rotation({x, -y}, teta);

        line_bresenham(p1[0] + xc, p1[1] + yc, p2[0] + xc, p2[1] + yc, color, lw);
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

matrix_t get_trans_matrix(double tx, double ty, double tz) {
    return {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {tx, ty, tz, 1}
    };
}

matrix_t translation(matrix_t cube, double tx, double ty, double tz) {
    return cube * get_trans_matrix(tx, ty, tz);
}

matrix_t get_matrix_rot_x(double angle) {
    matrix_t mat_rot_X = {
        {1, 0, 0, 0},
        {0, cos(angle), sin(angle), 0},
        {0, -sin(angle), cos(angle), 0},
        {0, 0, 0, 1}
    };
    return mat_rot_X;
}

matrix_t rotation_x(matrix_t cube, double angle) {
    return cube * get_matrix_rot_x(angle);
}

matrix_t get_matrix_rot_y(double angle) {
    matrix_t mat_rot_Y = {
        {cos(angle), 0, (-sin(angle)), 0},
        {0, 1, 0, 0},
        {sin(angle), 0, cos(angle), 0},
        {0, 0, 0, 1}
    };
    return mat_rot_Y;
}

matrix_t rotation_y(matrix_t cube, double angle) {
    return cube * get_matrix_rot_y(angle);
}

matrix_t get_matrix_rot_z(double angle) {
    return {
        {cos(angle), sin(angle), 0, 0},
        {-sin(angle), cos(angle), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
}

matrix_t rotation_z(matrix_t cube, double angle) {
    return cube * get_matrix_rot_z(angle);
}

matrix_t get_scaling_matrix(double sx, double sy, double sz, double sw = 1) {
    matrix_t mat_scale = {
        {sx, 0, 0, 0},
        {0, sy, 0, 0},
        {0, 0, sz, 0},
        {0, 0, 0, sw}
    };
    return mat_scale;
}

matrix_t scaling(matrix_t cube, double sx, double sy, double sz, double sw = 1) {
    return cube * get_scaling_matrix(sx, sy, sz, sw);
}
matrix_t operator-(const matrix_t &a, const matrix_t &b) {
    matrix_t res = a;
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a[0].size(); ++j) {
            res[i][j] = a[i][j] - b[i][j];
        }
    }
    return res;
}
vector_t operator-(const vector_t &v, const vector_t &w) {
    vector_t res =v;
    for (int i = 0; i < v.size(); ++i) {
        res[i] = v[i] - w[i];
    }
    return res;
}
matrix_t operator*(const matrix_t &a, const matrix_t &b) {
    return matrix_multiply(a, b);
}

matrix_t operator*(const matrix_t &a, const vector_t &v) {
    return a * matrix_t{v};
}

matrix_t operator*(const vector_t &v, const matrix_t &a) {
    return matrix_t{v} * a;
}

matrix_t operator*(const vector_t &v, const vector_t &w) {
    return matrix_t{v} * matrix_t{w};
}

matrix_t operator^(const matrix_t &mat, const char op) {
    if (op == 't') {
        return transpose(mat);
    }
    throw std::invalid_argument("Invalid operator");
}


matrix_t get_perspective_matrix_Z_d(double d) {
    matrix_t T_perspective = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 1.0 / d},
        {0, 0, 0, 1}
    };
    return T_perspective;
}

matrix_t get_perspective_calculated_matrix(point_3d_h_t viewpoint, point_3d_h_t r0, vector_t n) {
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
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
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


matrix_t divid_on_w(matrix_t points) {
    matrix_t res = points;
    for (int i = 0; i < points.size(); ++i) {
        for (int j = 0; j < points[0].size(); ++j) {
            res[i][j] = points[i][j] / points[i][3];
        }
    }
    return res;
}

matrix_t cavalier(matrix_t points) {
    matrix_t result = points * Tcv;
    return result;
}


matrix_t get_cavalier_matrix(double angle) {
    return Tcv;
}

void circle_full_bresenham(int xc, int yc, int r2, int color = 15, int r1 = 0) {
    for (int i = r1; i <= r2; i += 1) {
        cercle_bresenham(xc, yc, i, color);
    }
}

// Function to draw a vector from origin
void drawVector(vector_t v, string label = "", int color = WHITE, int lw = 5) {
    line_bresenham(0, 0, v[1], v[2], color, lw); // Draw the arrow shaft
    setcolor(color);
    circle_full_bresenham(v[1], v[2], 5, color);
    char label_c[100];
    strcpy(label_c, label.c_str());
    outtextxy(v[1] + getmaxx() / 2 + 6, getmaxy() / 2 - v[2] + 3, label_c);
}


double get_theta(vector_t V) {
    return atan2(sqrt(V[0] * V[0] + V[1] * V[1]), V[2]);
}

double get_phi(vector_t V) {
    return atan2(V[1], V[0]);
}

matrix_t get_matrix_alin_v_with_Z(vector_t V) {
    double theta = get_theta(V);
    double phi = get_phi(V);

    matrix_t T_RtZ = {
        {cos(-phi), sin(-phi), 0, 0},
        {-sin(-phi), cos(-phi), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    matrix_t T_RtY = {
        {cos(-theta), 0, -sin(-theta), 0},
        {0, 1, 0, 0},
        {sin(-theta), 0, cos(-theta), 0},
        {0, 0, 0, 1}
    };
    return T_RtZ * T_RtY;
}

//////////////////////////////////////////////////////////////////////////////////////////////
///

matrix_t M_rot_x(double angle) {
    return {
        {1, 0, 0, 0},
        {0, cos(angle), sin(angle), 0},
        {0, -sin(angle), cos(angle), 0},
        {0, 0, 0, 1}
    };
}

matrix_t M_rot_y(double angle) {
    return {
        {cos(angle), 0, -sin(angle), 0},
        {0, 1, 0, 0},
        {sin(angle), 0, cos(angle), 0},
        {0, 0, 0, 1}
    };
}

matrix_t M_rot_z(double angle) {
    return get_matrix_rot_z(angle);
}

matrix_t M_trs(vector_t v) {
    return {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        v
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// polygon functions /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
double get_pent(point_2d_t p1, point_2d_t p2) {
    return (p2[1] - p1[1]) / (double) (p2[0] - p1[0]);
}

double get_distance(point_2d_t p1, point_2d_t p2) {
    return sqrt(pow(p2[0] - p1[0], 2) + pow(p2[1] - p1[1], 2));
}

double get_produit_scalaire(vector_t p1, vector_t p2) {
    return p1[0] * p2[0] + p1[1] * p2[1];
}

double atan2_(double sn, double cs) {
    if (cs > 0) {
        return atan(sn / cs); //  1 or 4
    } else if (cs < 0 && sn >= 0) {
        return atan(sn / cs) + PI; //  2
    } else if (cs < 0 && sn < 0) {
        return atan(sn / cs) - PI; //  3
    } else if (cs == 0 && sn != 0) {
        return (sn > 0) ? PI / 2 : -PI / 2; // Positive or negative y-axis
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


//////////////////////////////////////////////////////////////////////////////////////////


#include "C:\Users\LENOVO i7\Desktop\ligacy_progects\infographie\code_graphics\Graphics\graphics.h"
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
            {0, 0, 0, 1}, // A
            {a, 0, 0, 1}, // B
            {a, b, 0, 1}, // C
            {0, b, 0, 1}, // D

            {0, 0, c, 1}, // E
            {a, 0, c, 1}, // F
            {a, b, c, 1}, // G
            {0, b, c, 1}, // H
        };
    } else {
        return {
            {0, 0, 0}, // A
            {a, 0, 0}, // B
            {a, b, 0}, // C
            {0, b, 0}, // D

            {0, 0, c}, // E
            {a, 0, c}, // F
            {a, b, c}, // G
            {0, b, c}, // H
        };
    }
}
