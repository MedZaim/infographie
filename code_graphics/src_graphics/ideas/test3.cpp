#include <graphics.h>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Function to perform matrix multiplication for dynamic dimensions
vector<vector<float>> matrixMultiply(const vector<vector<float>> &mat1, const vector<vector<float>> &mat2) {
    int rows1 = mat1.size();
    int cols1 = mat1[0].size();
    int cols2 = mat2[0].size();

    // Initialize the result matrix with zeros
    vector<vector<float>> result(rows1, vector<float>(cols2, 0.0f));

    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            for (int k = 0; k < cols1; ++k) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    return result;
}

// Function for perspective projection using matrix transformations
void perspectiveProjectionGeneral(float x, float y, float z,
                                  float xc, float yc, float zc, // Centre de projection
                                  float x0, float y0, float z0, // Plan de projection
                                  float n1, float n2, float n3, // Vecteur normal
                                  float &x_proj, float &y_proj, float &z_proj) {

    float A = n1;
    float B = n2;
    float C = n3;
    float D = -(A * x0 + B * y0 + C * z0);

    // Check if D is zero to avoid division by zero
    if (D == 0) {
        cerr << "Error: Division by zero in perspective projection. Plane is invalid." << endl;
        x_proj = y_proj = z_proj = 0;
        return;
    }

    // Create the perspective transformation matrix
    vector<vector<float>> perspectiveMatrix = {
            {1, 0, 0, -A / D},
            {0, 1, 0, -B / D},
            {0, 0, 1, -C / D},
            {0, 0, 0, 1}
    };

    // Create the point vector for the input coordinates
    vector<vector<float>> pointVector = {
            {x - xc},
            {y - yc},
            {z - zc},
            {1}
    };

    // Perform the matrix multiplication
    vector<vector<float>> result = matrixMultiply(perspectiveMatrix, pointVector);

    // Extract the projected coordinates
    float w = result[3][0]; // Homogeneous coordinate
    if (w == 0) {
        cerr << "Error: Homogeneous coordinate w is zero." << endl;
        x_proj = y_proj = z_proj = 0;
        return;
    }

    x_proj = result[0][0] / w + xc;
    y_proj = result[1][0] / w + yc;
    z_proj = result[2][0] / w + zc;
}

int main() {
    // Initialisation de la fenêtre graphique
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char *) "");

    // Centre de projection
    float xc = 400, yc = 0, zc = 0; // Origine (modifiable)

    // Plan de projection : Ax + By + Cz + D = 0
    float n1 = 10, n2 = 0, n3 = 10; // Vecteur normal
    float x0 = 0, y0 = 0, z0 = 200; // Point sur le plan (modifié pour éviter D = 0)

    // Points 3D à projeter
    float points[8][3] = {
            {0, 0, 0},
            {200, 0, 0},
            {200, 200, 0},
            {0, 200, 0},
            {0, 0, 200},
            {200, 0, 200},
            {200, 200, 200},
            {0, 200, 200}
    };

    // Projeter les points sur le plan
    float projected[8][3];
    for (int i = 0; i < 8; i++) {
        perspectiveProjectionGeneral(
                points[i][0], points[i][1], points[i][2], // Point 3D
                xc, yc, zc, // Centre de projection
                x0, y0, z0, // Plan de projection
                n1, n2, n3,
                projected[i][0], projected[i][1], projected[i][2] // Résultat projeté
        );
    }

    // Scale and translate projected points for display
    int scale = 1; // Scaling factor for better visualization
    int offsetX = getmaxx() / 2;
    int offsetY = getmaxy() / 2;

    // Print projected points for debugging
    for (int i = 0; i < 8; i++) {
        cout << "P[" << i << "](" << projected[i][0] << ", " << projected[i][1] << ", " << projected[i][2] << ")" << endl;
    }

    // Dessiner les lignes entre les points projetés
    for (int i = 0; i < 4; i++) {
        // Connecter la face avant
        line(projected[i][0] * scale + offsetX, projected[i][1] * scale + offsetY,
             projected[(i + 1) % 4][0] * scale + offsetX, projected[(i + 1) % 4][1] * scale + offsetY);

        // Connecter la face arrière
        line(projected[i + 4][0] * scale + offsetX, projected[i + 4][1] * scale + offsetY,
             projected[((i + 1) % 4) + 4][0] * scale + offsetX, projected[((i + 1) % 4) + 4][1] * scale + offsetY);

        // Connecter les faces avant et arrière
        line(projected[i][0] * scale + offsetX, projected[i][1] * scale + offsetY,
             projected[i + 4][0] * scale + offsetX, projected[i + 4][1] * scale + offsetY);
    }

    // Attendre que l'utilisateur ferme la fenêtre
    getch();
    closegraph();
    return 0;
}