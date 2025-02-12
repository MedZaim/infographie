#include <graphics.h>
#include <iostream>
#include <cmath>

using namespace std;

// Struct to represent a 3D point or vector
struct Point_3d {
    double x, y, z;

    // Constructors
    Point_3d() : x(0), y(0), z(0) {}
    Point_3d(double x, double y, double z) : x(x), y(y), z(z) {}
};

// Function to normalize a vector
Point_3d normalize(const Point_3d &v) {
    double length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (length == 0) return v; // Avoid division by zero
    return {v.x / length, v.y / length, v.z / length};
}

// Function to compute the cross product of two vectors
Point_3d cross(const Point_3d &a, const Point_3d &b) {
    return {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
    };
}

// Function to align a vector to the Z-axis
Point_3d aligner_to_z(const Point_3d &v, double rotation_matrix[3][3]) {
    // Step 1: Normalize the input vector
    Point_3d unit_v = normalize(v);

    // Step 2: Compute the rotation axis (cross product of unit_v and Z-axis)
    Point_3d z_axis = {0, 0, 1};
    Point_3d rotation_axis = cross(unit_v, z_axis);

    // Step 3: Normalize the rotation axis
    rotation_axis = normalize(rotation_axis);

    // Step 4: Compute the rotation angle (angle between unit_v and Z-axis)
    double cos_theta = unit_v.z; // Dot product of unit_v and Z-axis
    double sin_theta = sqrt(1 - cos_theta * cos_theta);

    // Step 5: Construct the rotation matrix using the axis-angle formula
    double ux = rotation_axis.x;
    double uy = rotation_axis.y;
    double uz = rotation_axis.z;

    rotation_matrix[0][0] = cos_theta + ux * ux * (1 - cos_theta);
    rotation_matrix[0][1] = ux * uy * (1 - cos_theta) - uz * sin_theta;
    rotation_matrix[0][2] = ux * uz * (1 - cos_theta) + uy * sin_theta;

    rotation_matrix[1][0] = uy * ux * (1 - cos_theta) + uz * sin_theta;
    rotation_matrix[1][1] = cos_theta + uy * uy * (1 - cos_theta);
    rotation_matrix[1][2] = uy * uz * (1 - cos_theta) - ux * sin_theta;

    rotation_matrix[2][0] = uz * ux * (1 - cos_theta) - uy * sin_theta;
    rotation_matrix[2][1] = uz * uy * (1 - cos_theta) + ux * sin_theta;
    rotation_matrix[2][2] = cos_theta + uz * uz * (1 - cos_theta);

    // Step 6: Apply the rotation matrix to the input vector
    Point_3d aligned_v = {
            rotation_matrix[0][0] * v.x + rotation_matrix[0][1] * v.y + rotation_matrix[0][2] * v.z,
            rotation_matrix[1][0] * v.x + rotation_matrix[1][1] * v.y + rotation_matrix[1][2] * v.z,
            rotation_matrix[2][0] * v.x + rotation_matrix[2][1] * v.y + rotation_matrix[2][2] * v.z
    };

    return aligned_v;
}

// Function to apply the inverse transformation
Point_3d inverse_transform(const Point_3d &v, const double rotation_matrix[3][3]) {
    // Compute the transpose of the rotation matrix (inverse for rotation matrices)
    double inverse_matrix[3][3] = {
            {rotation_matrix[0][0], rotation_matrix[1][0], rotation_matrix[2][0]},
            {rotation_matrix[0][1], rotation_matrix[1][1], rotation_matrix[2][1]},
            {rotation_matrix[0][2], rotation_matrix[1][2], rotation_matrix[2][2]}
    };

    // Apply the inverse transformation
    Point_3d restored_v = {
            inverse_matrix[0][0] * v.x + inverse_matrix[0][1] * v.y + inverse_matrix[0][2] * v.z,
            inverse_matrix[1][0] * v.x + inverse_matrix[1][1] * v.y + inverse_matrix[1][2] * v.z,
            inverse_matrix[2][0] * v.x + inverse_matrix[2][1] * v.y + inverse_matrix[2][2] * v.z
    };

    return restored_v;
}

// Function to project a 3D point to 2D using perspective projection (side view)
Point_3d project_to_2d_side(const Point_3d &v, double fov = 500) {
    // Rotate the scene to view from the side (rotate around Y-axis by 90 degrees)
    double theta = M_PI / 3; // 90 degrees in radians
    double cos_theta = cos(theta);
    double sin_theta = sin(theta);

    // Apply rotation around Y-axis
    double x_rot = v.x * cos_theta + v.z * sin_theta;
    double z_rot = -v.x * sin_theta + v.z * cos_theta;

    // Perspective projection
    double scale = fov / (fov + z_rot); // Perspective scaling factor
    return {x_rot * scale, v.y * scale, 0}; // Z is ignored for 2D projection
}

// Function to draw a 3D vector on the screen (side view)
void draw_vector_3d_side(Point_3d v, int color, const char* label,int lw=1) {
    // Project the 3D vector to 2D with side perspective
    Point_3d v_2d = project_to_2d_side(v);

    // Scale and offset for better visualization
    int scale = 1;
    int offsetX = getmaxx() / 2;
    int offsetY = getmaxy() / 2;

    // Draw the vector as a line from the origin
    line(offsetX, offsetY, offsetX + v_2d.x * scale, offsetY - v_2d.y * scale);

    // Display the label
    outtextxy(offsetX + v_2d.x * scale + 10, offsetY - v_2d.y * scale - 10, (char*)label);
}

int main() {
    // Initialize graphics window
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char *)"");

    // Define a vector
    Point_3d v = {100, 100, 100};

    // Step 1: Draw the original vector in 3D (side view)
    draw_vector_3d_side(v, WHITE, "Original",5);

    // Step 2: Align the vector to the Z-axis
    double rotation_matrix[3][3];
    Point_3d aligned_v = aligner_to_z(v, rotation_matrix);

    // Step 3: Draw the aligned vector in 3D (side view)
    draw_vector_3d_side(aligned_v, RED, "Aligned");

    // Step 4: Apply the inverse transformation to restore the vector
    Point_3d restored_v = inverse_transform(aligned_v, rotation_matrix);

    // Step 5: Draw the restored vector in 3D (side view)
    draw_vector_3d_side(restored_v, GREEN, "Restored");

    // Print the vectors to the console
    cout << "Original vector: (" << v.x << ", " << v.y << ", " << v.z << ")" << endl;
    cout << "Aligned vector: (" << aligned_v.x << ", " << aligned_v.y << ", " << aligned_v.z << ")" << endl;
    cout << "Restored vector: (" << restored_v.x << ", " << restored_v.y << ", " << restored_v.z << ")" << endl;

    // Wait for user input to close the window
    getch();
    closegraph();
    return 0;
}