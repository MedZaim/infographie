//
// Created by lenovo on 06/11/2024.
//
#include "../../includs/graphics_utils.h"


int main() {
    initwindow(640, 480, "Draw Shapes by mouse click");
    repere(getmaxx() / 2, getmaxy() / 2);

    segment_t l1, l2, l3;

    l1 = ligne_by_mouse(14, 0, 9);
    draw_seg(l1,15, 9);
    l2 = ligne_by_mouse(13, 0, 1);
    l3 = ajuster(l1, l2);

    log(l1);
    log(l2);
    log(l3);

    draw_seg(l3,10, 9);
    getch();
    closegraph();
    return 0;
}
