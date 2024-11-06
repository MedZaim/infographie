#include "chapes.h"
int main() {
    // testing main function:

    init_graph_();
    int X_MAX = 640, Y_MAX = 480;
    // line_bresenham(0, 0, 100, 100);
    repere(X_MAX / 2, Y_MAX / 2);
    //ellipse_p_p_by_mouse();
    //rectangle_by_mouse_click();
    //rectangle_teta({0, 0}, {100, 150}, 0);
    //rectangle_teta({0, 0}, {100, 150}, PI/4);
     rectangle_by_mouse_click_rotate();
    getch();
    closegraph();
    return 0;
}