//
// Created by LENOVO i7 on 25/10/2025.
//
#include "../../includs/graphics_utils.h"


int main()
{
    initwindow(1000, 800, "Fleur avec tige et feuilles");

    flower_stem_leaves(point_t{0.0, 0.0}, 200, GREEN, LIGHTGREEN, 9, 1);

    getch();
    closegraph();
    return 0;
}