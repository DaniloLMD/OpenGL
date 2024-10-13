#ifndef _POINTS_HPP__
#define _POINTS_HPP__

#include <GL/glut.h>

typedef struct point{
    int x, y;
    int cor;
} Point;

void draw_point(Point p);

#endif