#include "../include/sun.hpp"
#include <stdio.h>

double ang = 0;

void update_sun(){
    glPushMatrix();
    glTranslated(SIZE/2, GROUND_HEIGHT, 0);
    glRotated(-ang, 0, 0, 1);
    glTranslated(-SIZE/2, -GROUND_HEIGHT, 0);

    ang += 0.1;
    glColor3f(1, 1, 0);
    draw_circle(sun);

    glColor3f(1, 1, 1);
    draw_circle(moon);
    
    glColor3fv(sky_color);
    draw_circle(moon2);

    glPopMatrix();


}