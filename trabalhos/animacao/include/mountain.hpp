#ifndef __MOUNTAIN_HPP__
#define __MOUNTAIN_HPP__

#include "opengl_manager.hpp"
#include "point.hpp"

void draw_mountains();

void draw_mountain_circular(Point p, bool trees = false, bool frutos = false);
void draw_mountain_triangular(Point p, int w, int h);

#endif