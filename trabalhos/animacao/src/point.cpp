#include "../include/point.hpp"

void draw_point(Point p){
    glBegin(GL_POINTS);
        glVertex2i(p.x, p.y);
    glEnd();
}
