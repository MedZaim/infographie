//
// Created by lenovo on 02/11/2024.
//
//
// Created by lenovo on 02/11/2024.
#include "./../trigonometrique/elipse_teta.cpp"
#include "./../bresenhame/bresenham_cercle.cpp"
#include "./../bresenhame/bresenham_line.cpp"
#include <cmath>
#include <iostream>
#include <ctime>


void fleur(int xc = 0, int yc = 0, int r = 60,int a=60,int b=40,
           int color = 15, int color_c = YELLOW, int color_ex = RED) {
    int xx,yy,rr=  r+a/2;
    for(int i=0;i<360;i+=45){
        xx= rr*cos(i*PI/180);
        yy= rr*sin(i*PI/180);
        elipse_teta_full(a,b,xx+xc,yy+yc,i*PI/180,color_ex);
    }
    bresenham_full_cercle(xc, yc, r, 0, color_c);
}

int main() {
    init_graph_();
    int X_MAX = 640, Y_MAX = 480;

    repere(X_MAX / 2, Y_MAX / 2);
    fleur(-70,-50);
    getch();
}

