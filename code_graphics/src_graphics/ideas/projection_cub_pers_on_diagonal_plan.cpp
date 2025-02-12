//
// Created by lenovo on 16/12/2024.
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

// Normalize a vector
Point_3d normalize(const Point_3d& v) {
    double magnitude = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return {v.x / magnitude, v.y / magnitude, v.z / magnitude};
}

// Compute cross product of two vectors
Point_3d cross_product(const Point_3d& v1, const Point_3d& v2) {
    return {
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x
    };
}

// Compute dot product of two vectors
double dot_product(const Point_3d& v1, const Point_3d& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// Compute the rotation matrix from v1 to v2
std::vector<std::vector<double>> compute_rotation_matrix(const Point_3d& v1, const Point_3d& v2) {
    Point_3d u1 = normalize(v1);
    Point_3d u2 = normalize(v2);

    // Compute the cross product and dot product
    Point_3d cross = cross_product(u1, u2);
    double dot = dot_product(u1, u2);

    // Skew-symmetric matrix K from cross product
    std::vector<std::vector<double>> K = {
            {0, -cross.z, cross.y},
            {cross.z, 0, -cross.x},
            {-cross.y, cross.x, 0}
    };

    // Compute K^2 (K squared)
    std::vector<std::vector<double>> K_squared = {
            {-(cross.y * cross.y + cross.z * cross.z), cross.x * cross.y, cross.x * cross.z},
            {cross.x * cross.y, -(cross.x * cross.x + cross.z * cross.z), cross.y * cross.z},
            {cross.x * cross.z, cross.y * cross.z, -(cross.x * cross.x + cross.y * cross.y)}
    };

    // Identity matrix
    std::vector<std::vector<double>> I = {
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1}
    };

    // Compute the rotation matrix: R = I + K + K^2 / (1 + dot)
    std::vector<std::vector<double>> R = I;
    double scale = 1 / (1 + dot);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            R[i][j] += K[i][j] + scale * K_squared[i][j];
        }
    }

    return R;
}

// Apply the rotation matrix to a vector
Point_3d apply_matrix(const std::vector<std::vector<double>>& matrix, const Point_3d& point) {
    return {
            matrix[0][0] * point.x + matrix[0][1] * point.y + matrix[0][2] * point.z,
            matrix[1][0] * point.x + matrix[1][1] * point.y + matrix[1][2] * point.z,
            matrix[2][0] * point.x + matrix[2][1] * point.y + matrix[2][2] * point.z
    };
}

// Project 3D point onto 2D screen
std::pair<int, int> project_to_screen(const Point_3d& point, int screen_width, int screen_height) {
    double fov = 500; // Field of view
    double x = point.x * fov / (point.z + fov);
    double y = point.y * fov / (point.z + fov);
    int screen_x = static_cast<int>(screen_width / 2 + x);
    int screen_y = static_cast<int>(screen_height / 2 - y);
    return {screen_x, screen_y};
}

// Function to project a point onto a plane
Point_3d project_onto_plane(const Point_3d& point, const Point_3d& plane_point, const Point_3d& normal) {
    // Vector from plane_point to point
    Point_3d vec_to_point = point - plane_point;

    // Calculate t = (vec_to_point · normal) / (normal · normal)
    double t = vec_to_point.dot(normal) / normal.dot(normal);

    // Calculate the projection: point - t * normal
    Point_3d projected_point = point - normal * t;

    return projected_point;
}
//// Fonction pour centrer les points 3D
//void centre3D(int *X, int *Y, int *Z) {
//    int centreX = getmaxx() / 2;
//    int centreY = getmaxy() / 2;
//    int length = 350;
//
//    // Ajuster les coordonnées X et Y pour centrer le cube
//    *X = *X + centreX;
//    *Y = centreY - *Y;
//
//    // Calculer la perspective en utilisant le Z
//    double facteur = (double)length / (length + *Z); // Facteur de perspective
//    *X = (int)(*X * facteur);
//    *Y = (int)(*Y * facteur);
//}

// Fonction pour tracer les arêtes du cube
void Tracer_polyedre(matrix_t  points, matrix_t  edges, int color) {

    for (int i = 0; i < edges.size(); i++) {
        int p1 = edges[i][0], p2 = edges[i][1];

        // Points 3D
        int x1 = points[p1][0], y1 = points[p1][1], z1 = points[p1][2];
        int x2 = points[p2][0], y2 = points[p2][1], z2 = points[p2][2];

        Point A={x1,y1};
        Point B={x2,y2};
        line_bresenham(A,B,color);

    }
    // Afficher les étiquettes des sommets
    for (int i = 0; i < points.size(); i++) {
        int x = points[i][0], y = points[i][1], z = points[i][2];
        centre3D(&x, &y,&z);
        char label[3] = {(char) ('A' + i), '\0'}; // Nommer les sommets A, B, C...
        outtextxy(x, y, label);
    }
}


int main() {
    using namespace std;



    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");
    // Define the point to project



    double x = 100, y = 100, z = 100;
    matrix_t  points = {
            //  {X, Y, Z, H}
            {0, 0, 0, 1},   // A
            {x, 0, 0, 1},   // B
            {x, y, 0, 1},   // C
            {0, y, 0, 1},   // D
            {0, y, z, 1},   // E
            {0, 0, z, 1},   // F
            {x, 0, z, 1},   // G
            {x, y, z, 1} ,   // H
            //{x+50, y+30, z+20, 1}    // I
    };
    matrix_t  edges= {
            {0, 1}, {1, 2}, {2, 3}, {3, 0},
            {4, 5}, {5, 6}, {6, 7}, {7, 4},
            {0, 5}, {1, 6}, {2, 7}, {3, 4},
            // {2,8},{3,8},{4,8},{7,8}
    };
    matrix_t  M_Homogine = {
            //  {X, Y, Z, H}
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {sqrt(2)/2, sqrt(2)/2, 0, 0},
            {0,0,0, 1}
    };


    matrix_t    polyedre = matrix_multiply(points, M_Homogine);
    Tracer_polyedre(polyedre,edges, 14);



    Point_3d point(300, 300, 300);
    // Define a point on the plane
    Point_3d plane_point(100, 0, 0);

    // Define the plane normal vector
    Point_3d normal(1, 1, 1); // Plane normal along z-axis

    // Compute the projection
    Point_3d projected_point = project_onto_plane(point, plane_point, normal);

    cout << "Original point: ";
    point.print();

    cout << "Projected point: ";
    projected_point.print();

    // Screen dimensions
    int screen_width = getmaxx();
    int screen_height = getmaxy();

    // Define two vectors
    Point_3d v1 = {1, 2, 3};
    Point_3d v2 = {0, 0, 5};

    // Compute the rotation matrix
    std::vector<std::vector<double>> rotation = compute_rotation_matrix(v1, v2);

    // Transform vector v1 to align with v2
    Point_3d aligned_v1 = apply_matrix(rotation, v1);


    getch();
    closegraph();
    return 0;
}
