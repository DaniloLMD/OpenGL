#ifndef _POINTS_HPP__
#define _POINTS_HPP__

#include <GL/glut.h>

typedef struct Point{
    int x, y, z;
    int cor;
} Point;

void draw_point(Point p);

Point subtract(Point a, Point b);

Point scale(Point v, double s);

Point add(Point a, Point b);

Point cross(Point a, Point b);

int dot(Point a, Point b);

Point normalize(Point v);



#endif