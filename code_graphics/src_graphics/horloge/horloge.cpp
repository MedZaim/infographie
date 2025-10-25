//
// Created by lenovo on 02/11/2024.

#include "./../../includs/graphics_utils.h"




int main() {
    init_graph_();
    int X_MAX = 640, Y_MAX = 480;
    //setbkcolor(5);
    repere(X_MAX / 2, Y_MAX / 2);
    clock_(80, 50, 100, 15);
    //Dessine_Cadran_Horloge(100, 0, 0);
    getch();
}

