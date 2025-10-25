
#include"../../includs/graphics_utils.h"
using namespace std;

int main(){
    int gd=DETECT,gm;
    initgraph(&gd,&gm,"");

//display text
    outtextxy(360, 420, "Hello, Graphics!");
    circle_trigonometric(-200, 130, 100, WHITE, 5);
    //draw a rectangle teta
    rectangle_teta({50,-50}, {250,180}, PI / 4, YELLOW, 5);

    // drow an ellipse teta
    ellipse_teta(240, 90, -80, 100, PI / 6, GREEN,5);
    // draw a smol fleur in (240, -100)
    fleur(240, -100, 30, 60, 30);
    // draw a flower stem leaves
    flower_stem_leaves({10, -100}, 120, GREEN, LIGHTGREEN, 7, 1);

    //drow smol horloge in (-200, -200)
    clock_(-180, -100, 60, WHITE, GREEN, YELLOW, RED, 0);
    getch();
    closegraph();
    return 0;
}