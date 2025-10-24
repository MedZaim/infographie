//
// Created by lenovo on 16/12/2024.
//
#include <graphics.h>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <vector>
#include <iostream>

// Structure to hold 3D points
struct Point_3d_h {
    double x, y, z, w = 1; // Homogeneous coordinates (w defaults to 1)
};

// Perform matrix multiplication
std::vector<std::vector<double>>
matrix_multiply(const std::vector<std::vector<double>> &mat1, const std::vector<std::vector<double>> &mat2) {
    std::vector<std::vector<double>> result(mat1.size(), std::vector<double>(mat2[0].size(), 0));
    for (size_t i = 0; i < mat1.size(); ++i) {
        for (size_t j = 0; j < mat2[0].size(); ++j) {
            for (size_t k = 0; k < mat1[0].size(); ++k) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return result;
}

// Perspective projection
Point_3d_h perspective_projection(const Point_3d_h &point, double fov, double aspect, double z_near, double z_far) {
    double f = 1.0 / tan(fov / 2.0);

    std::vector<std::vector<double>> projection_matrix = {
            {f / aspect, 0, 0,                                   0},
            {0,          f, 0,                                   0},
            {0,          0, (z_far + z_near) / (z_near - z_far), (2 * z_far * z_near) / (z_near - z_far)},
            {0,          0, -1,                                  0}
    };

    std::vector<std::vector<double>> point_matrix = {
            {point.x},
            {point.y},
            {point.z},
            {point.w}
    };

    std::vector<std::vector<double>> projected = matrix_multiply(projection_matrix, point_matrix);

    double w = projected[3][0];
    if (w == 0) w = 1;

    return {projected[0][0] / w, projected[1][0] / w, projected[2][0] / w, 1};
}

// Map normalized device coordinates to screen
std::pair<int, int> viewport_mapping(const Point_3d_h &point, int screen_width, int screen_height) {
    int x = static_cast<int>((point.x + 1.0) * 0.5 * screen_width);
    int y = static_cast<int>((1.0 - point.y) * 0.5 * screen_height);
    return {x, y};
}

void drow_cube(std::vector<std::pair<int, int>> screen_points, int labeled = 1) {
    // Draw the edges of the cube
    // Front face
    line(screen_points[0].first, screen_points[0].second, screen_points[1].first, screen_points[1].second);
    line(screen_points[1].first, screen_points[1].second, screen_points[2].first, screen_points[2].second);
    line(screen_points[2].first, screen_points[2].second, screen_points[3].first, screen_points[3].second);
    line(screen_points[3].first, screen_points[3].second, screen_points[0].first, screen_points[0].second);

    // Back face
    line(screen_points[4].first, screen_points[4].second, screen_points[5].first, screen_points[5].second);
    line(screen_points[5].first, screen_points[5].second, screen_points[6].first, screen_points[6].second);
    line(screen_points[6].first, screen_points[6].second, screen_points[7].first, screen_points[7].second);
    line(screen_points[7].first, screen_points[7].second, screen_points[4].first, screen_points[4].second);

    // Connect front and back faces
    for (int i = 0; i < 4; ++i) {
        line(screen_points[i].first, screen_points[i].second, screen_points[i + 4].first,
             screen_points[i + 4].second);
    }
    if (labeled) {
        // display the labels of the vertices
        for (int i = 0; i < 8; i++) {
            int x = screen_points[i].first, y = screen_points[i].second;
            char label[3] = {(char) ('A' + i), '\0'}; // Nommer les sommets A, B, C...
            outtextxy(x, y, label);
        }
    }
}

int main() {
    // Initialize the graphics window
    // Initialize graphics window (no 'press key' hint because this program animates continuously)
    int screen_w = 640, screen_h = 480;
    initwindow(screen_w, screen_h, "Perspective (americain)");

    // Screen dimensions
    const int screen_width = getmaxx();
    const int screen_height = getmaxy();

    // Define some 3D points for testing (e.g., a cube)
    std::vector<Point_3d_h> points = {
            {-1, -1, -5,  1},
            {1,  -1, -5,  1},
            {1,  1,  -5,  1},
            {-1, 1,  -5,  1}, // Front face
            {-1, -1, -10, 1},
            {1,  -1, -10, 1},
            {1,  1,  -10, 1},
            {-1, 1,  -10, 1} // Back face
    };

    // Projection parameters
    double fov = M_PI / 4.0;  // 45 degrees
    double aspect = static_cast<double>(screen_width) / screen_height;
    double z_near = 1.0;
    double z_far = 100.0;

    // Project and draw the points
    while (true) {
        cleardevice(); // Clear the screen

        // Project points and map to 2D
        std::vector<std::pair<int, int>> screen_points;
        for (const auto &point: points) {
            Point_3d_h projected = perspective_projection(point, fov, aspect, z_near, z_far);
            screen_points.push_back(viewport_mapping(projected, screen_width, screen_height));
        }


        drow_cube(screen_points, 1);

        delay(50); // Add a small delay for better visualization
    }

    // Close the graphics window
    closegraph();
    return 0;
}
