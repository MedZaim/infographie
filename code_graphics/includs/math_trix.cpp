#include <iostream>
#include <vector>
#include <cmath>
#include "graphics_utils.h"


 int      main() {
    // Cube vertices
    matrix_t cube = {{0.0, 0.0, 0.0, 1.0},
                           {1.0, 0.0, 0.0, 1.0},
                           {1.0, 1.0, 0.0, 1.0},
                           {0.0, 1.0, 0.0, 1.0},
                           {0.0, 0.0, 1.0, 1.0},
                           {1.0, 0.0, 1.0, 1.0},
                           {1.0, 1.0, 1.0, 1.0},
                           {0.0, 1.0, 1.0, 1.0}};

    // Cube edges
    matrix_t  edges = {{0, 1}, {1, 2}, {2, 3}, {3, 0},
                         {4, 5}, {5, 6}, {6, 7}, {7, 4},
                         {0, 4}, {1, 5}, {2, 6}, {3, 7}};

    // Perform projections
    matrix_t proj_cv_cub = matrix_multiply(cube, Tcv);
    matrix_t proj_cb_cub = matrix_multiply(proj_cv_cub, Tcb);

    // Display projections
    cout << "Projection cavalier:" << endl;
    affiche(proj_cv_cub);

    cout << "Projection carabine:" << endl;
    affiche(proj_cb_cub);

    // Create Polyhedre instance with projected vertices
    Polyhedre cube_poly(proj_cv_cub, edges);
    cout << "Polyhedre vertices after cavalier projection:" << endl;
    cube_poly.affiche();

    return 0;
}
