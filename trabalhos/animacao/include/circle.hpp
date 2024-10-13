#ifndef __CIRCLE_HPP__
#define __CIRCLE_HPP__

#include "opengl_manager.hpp"
#include "point.hpp"

struct Circle{
    Point center;
    GLdouble rad;
};

void draw_circle(Circle c);

#endif