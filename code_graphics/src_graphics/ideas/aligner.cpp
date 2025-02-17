#include "../../includs/graphics_utils.h"
#include <iostream>
#include <iomanip> // For std::setprecision





int main() {
    initwindow(1000, 800, "Align with Z axis");

    point_t v = {100, 100, 100, 1};

    // Draw the original vector
    drawVector(v, "Original", WHITE, 5);
    getch();

    matrix_t alignment_matrix = get_matrix_alin_v_with_Z(v);
    vector_t aligned_v = (v * alignment_matrix)[0];

    // Debug: Print alignment matrix and aligned vector
    affich(alignment_matrix, "Alignment Matrix");
    cout << "Aligned Vector: (" << aligned_v[0] << ", " << aligned_v[1] << ", " << aligned_v[2] << ")" << endl;

    // Draw the aligned vector in 3D (side view)
    drawVector(aligned_v, "Aligned", RED, 5);
    getch();

    matrix_t inverse_matrix = alignment_matrix^'t'; // Transpose the matrix

    vector_t restored_v = (matrix_t{aligned_v} * inverse_matrix)[0];

    // Debug: Print inverse matrix and restored vector
    affich(inverse_matrix, "Inverse Matrix");
    cout << "Restored Vector: (" << restored_v[0] << ", " << restored_v[1] << ", " << restored_v[2] << ")" << endl;

    // Draw the restored vector in 3D (side view)
    drawVector(restored_v, "Restored", GREEN, 5);

    // Print the vectors to the console
    cout << "Original vector: (" << v[0] << ", " << v[1] << ", " << v[2] << ")" << endl;
    cout << "Aligned vector: (" << aligned_v[0] << ", " << aligned_v[1] << ", " << aligned_v[2] << ")" << endl;
    cout << "Restored vector: (" << restored_v[0] << ", " << restored_v[1] << ", " << restored_v[2] << ")" << endl;


    getch();
    closegraph();

    return 0;
}