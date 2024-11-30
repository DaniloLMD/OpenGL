#ifndef _POINTS_HPP__
#define _POINTS_HPP__

#include <GL/glut.h>

typedef struct Point{
    double x, y, z;
    int cor;

    bool operator==(Point a){
        return x == a.x && y == a.y && z == a.z;
    }
} Point;

void draw_point(Point p);

Point subtract(Point a, Point b);

Point scale(Point v, double s);

Point add(Point a, Point b);

Point cross(Point a, Point b);

int dot(Point a, Point b);

Point normalize(Point v);

double len(Point v);


#endif