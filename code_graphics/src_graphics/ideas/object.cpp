//
// Created by lenovo on 17/12/2024.
//

//


#include "../../includs/graphics_utils.h"

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
    vector<Point_3d> points;
    vector<vector<int>> edges;
    int n_points;
public:
    Object_3d_Homogine();
    Object_3d_Homogine(vector<Point_3d> points, vector<vector<int>> edges);

    void draw(){
        for (int i = 0; i < edges.size(); i++) {
            int p1 = edges[i][0], p2 = edges[i][1];

            // Points 3D
            int x1 = points[p1].x, y1 = points[p1].y, z1 = points[p1].z;
            int x2 = points[p2].x, y2 = points[p2].y, z2 = points[p2].z;

            Point A={x1,y1};
            Point B={x2,y2};
            line_bresenham(A,B,14);

        }
        // Afficher les étiquettes des sommets
        for (int i = 0; i < points.size(); i++) {
            int x = points[i].x, y = points[i].y, z = points[i].z;
            std::cout << "Point " << i << ": (" << x << ", " << y << ", " << z << ")" << std::endl;
        }
    };
    void rotate();
    void translate(Point_3d t){
        for (int i = 0; i < n_points; i++) {
            points[i] = points[i] + t;
        }
    };
    void scale();
    void shear();
    void project();

    void animate();
    void texture();
    void light();
    void split();
    void combine();
    void group();
    void ungroup();
    void align();

    void print();
};



int main(){

}