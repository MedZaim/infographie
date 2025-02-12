#include <graphics.h>
#include <cmath>
#include <conio.h>
#include <limits>

struct Point3D {
    float x, y, z;
};

struct Point4D {
    float x, y, z, w;
};
Point3D operator-(const Point3D& a, const Point3D& b) {
    Point3D result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}
struct Matrix4x4 {
    float m[4][4];
};

// Function to compute cross product
Point3D cross(Point3D a, Point3D b) {
    Point3D res;
    res.x = a.y * b.z - a.z * b.y;
    res.y = a.z * b.x - a.x * b.z;
    res.z = a.x * b.y - a.y * b.x;
    return res;
}

// Function to compute dot product
float dot(Point3D a, Point3D b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Function to normalize a vector
Point3D normalize(Point3D v) {
    float len = sqrt(dot(v, v));
    if (len == 0) return v;
    v.x /= len;
    v.y /= len;
    v.z /= len;
    return v;
}

// Matrix multiplication function
Point4D multiplyMatrixVector(const Matrix4x4& mat, const Point4D& vec) {
    Point4D result;
    result.x = mat.m[0][0] * vec.x + mat.m[0][1] * vec.y + mat.m[0][2] * vec.z + mat.m[0][3] * vec.w;
    result.y = mat.m[1][0] * vec.x + mat.m[1][1] * vec.y + mat.m[1][2] * vec.z + mat.m[1][3] * vec.w;
    result.z = mat.m[2][0] * vec.x + mat.m[2][1] * vec.y + mat.m[2][2] * vec.z + mat.m[2][3] * vec.w;
    result.w = mat.m[3][0] * vec.x + mat.m[3][1] * vec.y + mat.m[3][2] * vec.z + mat.m[3][3] * vec.w;
    return result;
}

int main() {
    // Initialize graphics mode
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Define eye point
    Point3D Eye = {900, 0, 0};

    // Define projection plane: point P and normal N
    Point3D P = {100, 0, 0}; // Point on the plane
    Point3D N = normalize({1, 0, 1}); // Normal vector

    // Find basis vectors U and V
    Point3D tmp = {1, 0, 0};
    if (fabs(N.x) < 1e-6) tmp = {0, 1, 0};
    Point3D U = normalize(cross(N, tmp));
    Point3D V = cross(N, U);

    // Define cube vertices
    Point3D cube[] = {
            {0, 0, 0}, {100, 0, 0}, {100, 100, 0}, {0, 100, 0}, // Bottom face
            {0, 0, 100}, {100, 0, 100}, {100, 100, 100}, {0, 100, 100} // Top face
    };

    // Define cube edges
    int edges[12][2] = {
            {0,1}, {1,2}, {2,3}, {3,0},
            {4,5}, {5,6}, {6,7}, {7,4},
            {0,4}, {1,5}, {2,6}, {3,7}
    };

    // Compute projected points on the plane
    Point3D projected[8];
    for (int i = 0; i < 8; i++) {
        Point3D Q_minus_Eye = {cube[i].x - Eye.x, cube[i].y - Eye.y, cube[i].z - Eye.z};
        float t = dot(P - Eye, N) / dot(Q_minus_Eye, N);
        projected[i].x = Eye.x + t * Q_minus_Eye.x;
        projected[i].y = Eye.y + t * Q_minus_Eye.y;
        projected[i].z = Eye.z + t * Q_minus_Eye.z;
    }

    // Find the range of u and v coordinates
    float min_u = std::numeric_limits<float>::infinity();
    float max_u = -std::numeric_limits<float>::infinity();
    float min_v = std::numeric_limits<float>::infinity();
    float max_v = -std::numeric_limits<float>::infinity();

    for (int i = 0; i < 8; i++) {
        Point3D delta = {projected[i].x - P.x, projected[i].y - P.y, projected[i].z - P.z};
        float u = dot(delta, U);
        float v = dot(delta, V);
        if (u < min_u) min_u = u;
        if (u > max_u) max_u = u;
        if (v < min_v) min_v = v;
        if (v > max_v) max_v = v;
    }

    // Create transformation matrix T
    Matrix4x4 T;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            T.m[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }

    float W = getmaxx();
    float H = getmaxy();

    float scale_u = (max_u - min_u) != 0 ? W / (max_u - min_u) : 1.0f;
    float scale_v = (max_v - min_v) != 0 ? H / (max_v - min_v) : 1.0f;

    float translate_x = -min_u * scale_u;
    float translate_y = -min_v * scale_v;

    T.m[0][0] = scale_u;
    T.m[1][1] = scale_v;
    T.m[0][3] = translate_x;
    T.m[1][3] = translate_y;

    // Transform projected points to screen coordinates
    Point4D homogeneous[8];
    for (int i = 0; i < 8; i++) {
        Point3D delta = {projected[i].x - P.x, projected[i].y - P.y, projected[i].z - P.z};
        homogeneous[i].x = dot(delta, U);
        homogeneous[i].y = dot(delta, V);
        homogeneous[i].z = 0.0f;
        homogeneous[i].w = 1.0f;
    }

    Point4D transformed[8];
    for (int i = 0; i < 8; i++) {
        transformed[i] = multiplyMatrixVector(T, homogeneous[i]);
    }

    // Map transformed points to screen coordinates
    Point3D screen[8];
    for (int i = 0; i < 8; i++) {
        if (transformed[i].w != 0) {
            screen[i].x = transformed[i].x / transformed[i].w;
            screen[i].y = transformed[i].y / transformed[i].w;
            screen[i].z = transformed[i].z / transformed[i].w;
        } else {
            screen[i].x = 0;
            screen[i].y = 0;
            screen[i].z = 0;
        }
    }

    // Draw edges
    for (int i = 0; i < 12; i++) {
        int index1 = edges[i][0];
        int index2 = edges[i][1];
        line(screen[index1].x, screen[index1].y, screen[index2].x, screen[index2].y);
    }

    // Wait for a key press and close graphics mode
    getch();
    closegraph();
    return 0;
}