//
// Created by LENOVO i7 on 24/10/2025.
//
#include "../../includs/graphics_utils.h"


int main() {
    initwindow(640, 480, "Rectangle - Rotate by mouse click");
    rectangle_by_mouse_click_rotate(15, 0, 1);
    getch();
    closegraph();
    return 0;
}
