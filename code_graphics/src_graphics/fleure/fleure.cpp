//
// Created by lenovo on 02/11/2024.
//

#include "../../includs/graphics_utils.h"



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
          int nb_vertical_branch = 6,int rf=10, point_2d_t racine = {50, -200}) {


    int x =(int) (r * cos(angle));
    int y = (int)(r * sin(angle));
    point_2d_t s1 = {racine[0] + x, racine[1] + y};
    point_2d_t s2 = {racine[0] - x,racine[1] + y};

    printf("x=%d y=%d\n",x,y);
    printf("s1[0]=%d s1[1]=%d\n",s1[0],s1[1]);
    printf("s2[0]=%d s2[1]=%d\n",s2[0],s2[1]);

   if(nb_vertical_branch>0) {
       line_bresenham(racine, s1,  GREEN,9);
       line_bresenham(racine, s2,  GREEN,9);
   }else{
       fleur(racine[0],racine[1],rf,20,10);
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

