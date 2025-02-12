//
// Created by lenovo on 11/11/2024.
//
#include "../../includs/chapes.h"
#include <conio.h>
#include <iostream>
#include <chrono>


void pendule(long long int t0,Point C,int r=100,double f= 1/4.0,double a= 0.08, double teta_m =PI/3){
    line_bresenham({C.x-15,C.y},{C.x+15,C.y},15,9);
    int x,y,x_,y_;
    double teta;
    double t;
    while (true){

        auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()
        ).count();

        t= (t1-t0)/1000.0;

        teta = (teta_m*exp(-a*t))* cos(2*PI*f*t) -PI/2;

        x = r*cos(teta);
        y = r*sin(teta);


        x_=x;
        y_=y;
        line_bresenham({x+C.x,y+C.y},C,15,1);
        delay(10);
        break;
        line_bresenham({x_+C.x,y_+C.y},C,0,1);


    }
}

int main(){

    init_graph_();
    int X_MAX = 640, Y_MAX = 480;
    auto t0 = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
    Point C = {100,100};
    int x,y;
    double angle = 0;
    int r = 100;
    while(true){
        x= r*cos(angle);
        y= r*sin(angle);
        pendule(t0,{x,y},80);
        angle+=PI/180;
        cleardevice();
    }
    pendule(t0,C,80);
    getch();

    return 0;
}