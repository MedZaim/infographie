//
// Created by LENOVO i7 on 25/10/2025.
//
#include "../../includs/graphics_utils.h"


void rectangle_by_mouse_click_(int color = 15, int color_bk = 0, int lw = 1) {
    int x1, y1, x2, y2;
    int prev_x2 = 0, prev_y2 = 0;
    bool hasPrev = false;

    // Clear any stale clicks
    clearmouseclick(WM_LBUTTONDOWN);
    clearmouseclick(WM_LBUTTONUP);

    // Wait for first click to set the anchor corner
    while (!ismouseclick(WM_LBUTTONDOWN)) {
        delay(10);
    }
    x1 = mousex() - getmaxx() / 2;
    y1 = getmaxy() / 2 - mousey();
    clearmouseclick(WM_LBUTTONDOWN);

    // Live preview until the user releases the left button
    while (true) {
        // Current mouse corner (convert to centered coordinates)
        x2 = mousex() - getmaxx() / 2;
        y2 = getmaxy() / 2 - mousey();

        // Erase previous preview rectangle (if any)
        if (hasPrev) {
            rectangle_(x1, y1, prev_x2, prev_y2, color_bk, lw);
        }

        // Draw current preview rectangle
        rectangle_(x1, y1, x2, y2, color, lw);
        hasPrev = true;
        prev_x2 = x2;
        prev_y2 = y2;

        // Finish on release; keep the final rectangle in 'color'
        if (ismouseclick(WM_LBUTTONUP)) {
            clearmouseclick(WM_LBUTTONUP);
            break;
        }

        delay(10); // reduce CPU usage and flicker
    }


}
int main() {

    initwindow(640, 480, "Rectangle avec la sourie-  click&hold right button");
    rectangle_by_mouse_click_();
    getch();
    closegraph();

}