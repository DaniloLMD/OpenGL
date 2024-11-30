#ifndef _CUBO_HPP__
#define _CUBO_HPP__

#include "point.hpp"
#include <vector>

struct Cubo{
    Point center;
    Point vertices[8];  
    int tam;


    Cubo(Point center = {0,0,0}, int tam = 0, GLfloat cores[6][3] = NULL);
    void Draw();
    void Rotate(double angX, double angY, double angZ);
    void Translate(int x, int y, int z);

    Point vertices_rotacionados[8];
    std::vector<Point> face_vertices[6];
    void DrawFace(std::vector<Point>& v);
    void DrawVertices();
    void RenderFaces();

    GLfloat cores[6][3];
};

#endif