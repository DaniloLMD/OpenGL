#ifndef _CUBO_HPP__
#define _CUBO_HPP__

#include "point.hpp"

struct Cubo{
    Point center;
    Point vertices[8];  
    int tam;

   Point faces[6][int(1e6+500)];
   int sizes[6];

    Cubo(Point center = {0,0,0}, int tam = 0);
    void Draw();
    void DrawFace(int face);
    void Render(Point* p, int face);
    void Rotate(double angX, double angY, double angZ);

};

#endif