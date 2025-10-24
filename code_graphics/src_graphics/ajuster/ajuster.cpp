//
// Created by Med on 2/28/2025.
//
#include "../../includs/graphics_utils.h"

void ajuster() {
    segment_t l1, l2, l3;

    l1 = ligne_by_mouse(14, 0, 9);
    draw_seg(l1,15, 9);
    l2 = ligne_by_mouse(13, 0, 1);
    draw_seg(l1,15, 9);
    l3 = ajuster(l1, l2);

    log(l1);
    log(l2);
    log(l3);

    draw_seg(l3,10, 9);
}

int main() {
    initwindow(640, 480, "Ajuster 2 seg par mouse click | click left --> right");
    // repere(getmaxx() / 2, getmaxy() / 2);

    ajuster();
    getch();
    closegraph();
    return 0;
}
