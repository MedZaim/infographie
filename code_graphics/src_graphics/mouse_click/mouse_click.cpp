//
// Created by lenovo on 06/11/2024.
//
#include "../../includs/graphics_utils.h"

#include <iostream>

using namespace std;



int main() {
    init_graph_();
    repere(getmaxx() / 2, getmaxy() / 2);

    Line l1, l2, l3;

    l1 = ligne_by_mouse(14, 0, 9);
    l1.draw(15,9);
    l2 = ligne_by_mouse(13, 0, 1);
    l3 = ajuster(l1, l2);

l1.log();
l2.log();
l3.log();

    l3.draw(10,9);
    getch();
    closegraph();
    return 0;
}