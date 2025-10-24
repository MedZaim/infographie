//
// Created by lenovo on 06/11/2024.
//
#include "../../includs/graphics_utils.h"


int main() {
    initwindow(640, 480, "Ellipse teta by mouse click");
   // repere(getmaxx() / 2, getmaxy() / 2);
    ellipse_p_p_by_mouse(0, 15, 0, 9);
    getch();
    closegraph();
    initwindow(640, 480, "rectangle tete by mouse click");

    rectangle_by_mouse_click_rotate(15, 0, 1);
    getch();
    closegraph();
    return 0;
}
