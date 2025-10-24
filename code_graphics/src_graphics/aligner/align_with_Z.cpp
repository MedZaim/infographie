#include ".\..\..\includs\graphics_utils.h"




int main() {
    // Initialize graphics mode
    // show instruction in title
    initwindow(1000, 800, "Align with Z axis - Appuyez sur une touche pour continuer");
    repere(getmaxx() / 2 , getmaxy() / 2 );

    // Original vector V(a, b, c)
    vector_t V = {100, 200, 50, 1};

    // Draw the original vector in red
    drawVector(V, "V",YELLOW, 5);

    matrix_t M_aline_with_Z = get_matrix_alin_v_with_Z(V);

    vector_t alignedV = (V * M_aline_with_Z)[0];
    getch();
    // Draw the aligned vector in green
    drawVector(alignedV, "V aligner avec Z",GREEN, 5);
    affich(M_aline_with_Z, "M_aline_with_Z");
    affich({V}, "V");
    affich({alignedV}, "alignedV");
    // Display result
    setcolor(YELLOW);
    outtextxy(10, 10, (char *) "Red: Original Vector");
    setcolor(GREEN);
    outtextxy(10, 30, (char *) "Green: Aligned Vector");

    // Wait for user to close the window
    getch();
    closegraph();

    return 0;
}
