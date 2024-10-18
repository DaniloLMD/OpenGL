#include "../include/sun.hpp"
#include <stdio.h>

double ang = 0;

void update_sun(){
    glPushMatrix();
    glTranslated(SIZE/2, GROUND_HEIGHT, 0);
    glRotated(-ang, 0, 0, 1);
    glTranslated(-SIZE/2, -GROUND_HEIGHT, 0);


    int a = ang;
    a = a % 360;
    int cor_ceu = (a <= 180) ? 0 : 1;

    glClearColor(sky_color[cor_ceu][0],sky_color[cor_ceu][1], sky_color[cor_ceu][2], 1);

    ang += 0.25;
    glColor3f(1, 1, 0);
    draw_circle(sun);

    glColor3f(1, 1, 1);
    draw_circle(moon);
    
    glColor3fv(sky_color[cor_ceu]);
    draw_circle(moon2);

    glPopMatrix();


}