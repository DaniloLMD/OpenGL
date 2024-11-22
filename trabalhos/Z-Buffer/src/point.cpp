#include "../include/point.hpp"
#include <math.h>
    
void draw_point(Point p){
    glBegin(GL_POINTS);
        glVertex3i(p.x, p.y, p.z);
    glEnd();
}

Point subtract(Point a, Point b) {
    return (Point){a.x - b.x, a.y - b.y, a.z - b.z};
}

Point scale(Point v, double s) {
    int x = v.x * s;
    int y = v.y * s;
    int z = v.z * s;
    return (Point){x, y, z};
}

Point add(Point a, Point b) {
    return (Point){a.x + b.x, a.y + b.y, a.z + b.z};
}

Point cross(Point a, Point b) {
    return (Point){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

int dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Point normalize(Point v) {
    double len = sqrt(dot(v, v));
    if (len == 0) { 
        return (Point){0, 0, 0}; // Evitar divisão por zero
    }
    return scale(v, 1.0 / len);
}