//
// Created by lenovo on 17/12/2024.
//

//


#include "../../includs/graphics_utils.h"
#include <conio.h>
#include <cmath>
#include <string>
#include <cstdio>

#ifndef PI
#define PI 3.14159265358979323846
#endif

// Define a structure for 3D points
class Point_3d {
public:
    double x, y, z;
    Point_3d() : x(0), y(0), z(0) {}
    Point_3d(double x, double y, double z) : x(x), y(y), z(z) {}

    // Subtraction operator
    Point_3d operator-(const Point_3d& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    // Addition operator
    Point_3d operator+(const Point_3d& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    // Scalar multiplication
    Point_3d operator*(double scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }

    // Dot product
    double dot(const Point_3d& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    void print() const {
        std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
    }
};

class Object_3d_Homogine {
    std::vector<Point_3d> points;
    std::vector<std::vector<int>> edges; // each edge: {i,j}
    int n_points{};

    // projection parameters
    bool use_perspective = true;
    double persp_d = 600.0; // distance for perspective (larger = weaker perspective)
    double par_alpha = PI / 4.0; // cavalier-like angle for parallel projection
    double par_k = 0.5; // scaling for z contribution in parallel projection

    static double toRad(double deg) { return deg * PI / 180.0; }

public:
    Object_3d_Homogine() = default;
    Object_3d_Homogine(std::vector<Point_3d> pts, std::vector<std::vector<int>> e)
        : points(std::move(pts)), edges(std::move(e)) {
        n_points = static_cast<int>(points.size());
    }

    void set_perspective(double d) { use_perspective = true; persp_d = d; }
    void set_parallel(double alpha_rad = PI/4.0, double k = 0.5) { use_perspective = false; par_alpha = alpha_rad; par_k = k; }

    // Transformations (in place)
    void translate(const Point_3d &t) {
        for (auto &p : points) { p = p + t; }
    }

    void scale(double sx, double sy, double sz, const Point_3d &center = {0,0,0}) {
        for (auto &p : points) {
            p.x = center.x + (p.x - center.x) * sx;
            p.y = center.y + (p.y - center.y) * sy;
            p.z = center.z + (p.z - center.z) * sz;
        }
    }

    void rotate_x(double angle_rad, const Point_3d &center = {0,0,0}) {
        double c = std::cos(angle_rad), s = std::sin(angle_rad);
        for (auto &p : points) {
            double y = p.y - center.y;
            double z = p.z - center.z;
            double y_ = y * c - z * s;
            double z_ = y * s + z * c;
            p.y = y_ + center.y;
            p.z = z_ + center.z;
        }
    }

    void rotate_y(double angle_rad, const Point_3d &center = {0,0,0}) {
        double c = std::cos(angle_rad), s = std::sin(angle_rad);
        for (auto &p : points) {
            double x = p.x - center.x;
            double z = p.z - center.z;
            double x_ = x * c + z * s;
            double z_ = -x * s + z * c;
            p.x = x_ + center.x;
            p.z = z_ + center.z;
        }
    }

    void rotate_z(double angle_rad, const Point_3d &center = {0,0,0}) {
        double c = std::cos(angle_rad), s = std::sin(angle_rad);
        for (auto &p : points) {
            double x = p.x - center.x;
            double y = p.y - center.y;
            double x_ = x * c - y * s;
            double y_ = x * s + y * c;
            p.x = x_ + center.x;
            p.y = y_ + center.y;
        }
    }

    Point_3d centroid() const {
        Point_3d c{0,0,0};
        if (points.empty()) return c;
        for (const auto &p : points) { c.x += p.x; c.y += p.y; c.z += p.z; }
        c.x /= points.size(); c.y /= points.size(); c.z /= points.size();
        return c;
    }

    // Project a 3D point to 2D using current projection settings
    point_2d_t project(const Point_3d &p) const {
        if (use_perspective) {
            double denom = 1.0 + (p.z / persp_d);
            if (denom < 1e-6) denom = 1e-6; // avoid blow-up
            return { p.x / denom, p.y / denom };
        } else {
            // simple cavalier-like oblique projection
            double dx = par_k * p.z * std::cos(par_alpha);
            double dy = par_k * p.z * std::sin(par_alpha);
            return { p.x + dx, p.y + dy };
        }
    }

    // Draw edges using current projection
    void draw(int color = WHITE, int lw = 1, bool labels = false) const {
        setcolor(color);
        for (const auto &e : edges) {
            int i = e[0], j = e[1];
            point_2d_t A = project(points[i]);
            point_2d_t B = project(points[j]);
            line_bresenham(A, B, color, lw);
        }
        if (labels) {
            setcolor(color);
            for (int i = 0; i < (int)points.size(); ++i) {
                point_2d_t P = project(points[i]);
                int x = (int)P[0] + getmaxx()/2;
                int y = getmaxy()/2 - (int)P[1];
                char label[8];
                snprintf(label, sizeof(label), "%d", i);
                outtextxy(x + 4, y + 4, label);
            }
        }
    }

    void print() {
        for (int i = 0; i < (int)points.size(); ++i) {
            std::cout << "Point " << i << ": (" << points[i].x << ", " << points[i].y << ", " << points[i].z << ")\n";
        }
    }
};

// Build a cube centered at origin with edge length L
static Object_3d_Homogine make_cube(double L) {
    double a = L/2.0;
    std::vector<Point_3d> pts = {
        {-a,-a,-a}, { a,-a,-a}, { a, a,-a}, {-a, a,-a},
        {-a,-a, a}, { a,-a, a}, { a, a, a}, {-a, a, a}
    };
    std::vector<std::vector<int>> es = {
        {0,1},{1,2},{2,3},{3,0}, // bottom
        {4,5},{5,6},{6,7},{7,4}, // top
        {0,4},{1,5},{2,6},{3,7}  // verticals
    };
    return Object_3d_Homogine(pts, es);
}

int main(){
    // Open window with a descriptive title
    initwindow(900, 700, "3D Object Demo - Rotating Cube (Perspective)");

    // Draw axes/crosshair at center
    repere(getmaxx()/2, getmaxy()/2);

    Object_3d_Homogine obj = make_cube(200);
    obj.set_perspective(800.0);

    // animate rotation around all axes
    double deg2rad = PI/180.0;
    double base_deg_per_frame = 2.0; // degrees per frame
    double speed_scale = 1.0;        // multiplier for speed

    bool labels = false;
    bool paused = false;
    bool perspective = true;
    double persp_d = 800.0;

    while (true) {
        // handle input if any
        if (kbhit()) {
            int ch = getch();
            if (ch == 27) { // ESC
                break;
            } else if (ch == ' ' ) {
                paused = !paused;
            } else if (ch == 'p' || ch == 'P') {
                perspective = !perspective;
                if (perspective) obj.set_perspective(persp_d);
                else obj.set_parallel(PI/4.0, 0.5);
            } else if (ch == 'l' || ch == 'L') {
                labels = !labels;
            } else if (ch == 'o' || ch == '+') {
                persp_d += 100.0; if (persp_d > 5000.0) persp_d = 5000.0;
                if (perspective) obj.set_perspective(persp_d);
            } else if (ch == 'i' || ch == '-') {
                persp_d -= 100.0; if (persp_d < 100.0) persp_d = 100.0;
                if (perspective) obj.set_perspective(persp_d);
            } else if (ch == 's' || ch == 'S') {
                speed_scale *= 0.5; if (speed_scale < 0.25) speed_scale = 1.0;
            } else if (ch == 'f' || ch == 'F') {
                speed_scale *= 2.0; if (speed_scale > 8.0) speed_scale = 1.0;
            } else if (ch == 'r' || ch == 'R') {
                // reset object and settings
                obj = make_cube(200);
                if (perspective) obj.set_perspective(persp_d); else obj.set_parallel(PI/4.0, 0.5);
                labels = false; paused = false; speed_scale = 1.0;
            }
        }

        cleardevice();
        repere(getmaxx()/2, getmaxy()/2);

        // rotate around origin to keep object centered in world
        if (!paused) {
            double ang = base_deg_per_frame * speed_scale * deg2rad;
            Point_3d c{0,0,0};
            obj.rotate_x(ang, c);
            obj.rotate_y(0.7 * ang, c);
            obj.rotate_z(0.5 * ang, c);
        }

        // draw object
        obj.draw(WHITE, 1, labels);

        // HUD
        setcolor(WHITE);
        char buf[200];
        snprintf(buf, sizeof(buf), "Mode:%s  d=%.0f  Speed:x%.2f  [P] toggle  [+/-] d  [L] labels  [S/F] speed  [Space] pause  [R] reset  [ESC] quit",
                 perspective?"Perspective":"Parallel", persp_d, speed_scale);
        outtextxy(10, 10, buf);

        delay(16); // ~60 FPS
    }
    closegraph();
    return 0;
}