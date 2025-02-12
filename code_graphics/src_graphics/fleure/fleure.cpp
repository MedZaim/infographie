//
// Created by lenovo on 02/11/2024.
//
//
// Created by lenovo on 02/11/2024.
#include "../../includs/graphics_utils.h"
#include <cmath>
#include <iostream>
#include <ctime>


void fleur(int xc = 0, int yc = 0, int r = 60,int a=60,int b=40,int nb_pital=6,
           int color = 15, int color_c = YELLOW, int color_ex = RED) {
    int xx,yy,rr=  r+a;
    for(int i=0;i<360;i+=360/nb_pital){
        xx= rr*cos(i*PI/180);
        yy= rr*sin(i*PI/180);
        ellipse_teta_full(a,b,xx+xc,yy+yc,i*PI/180,color_ex);
    }
    cercle_full_bresenham(xc, yc, r, 0, color_c);
}


void tree(int r = 100, double angle = PI / 3,int nb_branches=4,
          int nb_vertical_branch = 6,int rf=10, Point racine = {50, -200}) {


    int x =(int) (r * cos(angle));
    int y = (int)(r * sin(angle));
    Point s1 = {racine.x + x, racine.y + y};
    Point s2 = {racine.x - x,racine.y + y};

    printf("x=%d y=%d\n",x,y);
    printf("s1.x=%d s1.y=%d\n",s1.x,s1.y);
    printf("s2.x=%d s2.y=%d\n",s2.x,s2.y);

   if(nb_vertical_branch>0) {
       line_bresenham(racine, s1,  GREEN,9);
       line_bresenham(racine, s2,  GREEN,9);
   }else{
       fleur(racine.x,racine.y,rf,20,10);
       return;
   }


    tree(r - 10, angle , nb_branches - 1,--nb_vertical_branch,rf, s1);
    tree(r - 10, angle , nb_branches - 1,--nb_vertical_branch,rf, s2);
}


int main() {
    init_graph_();
    int X_MAX = 640, Y_MAX = 480;

    repere(X_MAX / 2, Y_MAX / 2);
    //tree(100,PI/3,5,3,15);
    fleur(-70,-50);
    getch();
}

