#include "../include/cubo.hpp"
#include "../include/z_buffer.hpp"
#include "../include/transformacoes_geometricas.hpp"
#include <math.h>
#include <stdio.h>

GLfloat cores[][3] = {
    {1,0,0},
    {0,1,0},  
    {0, 0, 1},
    {1,0,1}, 
    {1,1,0}, 
    {1,1,1},  
    {0.5, 0.5, 0.5},
    {0, 0, 0} 
};

Cubo::Cubo(Point center, int tam) : center(center), tam(tam){
    int tmp = tam/2;

    vertices[0] = {center.x + tmp, center.y + tmp, center.z + tmp, center.cor}; // + + +
    vertices[1] = {center.x + tmp, center.y + tmp, center.z - tmp, center.cor}; // + + -
    vertices[2] = {center.x + tmp, center.y - tmp, center.z + tmp, center.cor}; // + - +
    vertices[3] = {center.x - tmp, center.y - tmp, center.z + tmp, center.cor}; // - - +
    vertices[4] = {center.x - tmp, center.y + tmp, center.z - tmp, center.cor}; // - + -
    vertices[5] = {center.x - tmp, center.y + tmp, center.z + tmp, center.cor}; // - + +
    vertices[6] = {center.x - tmp, center.y - tmp, center.z - tmp, center.cor}; // - - -
    vertices[7] = {center.x + tmp, center.y - tmp, center.z - tmp, center.cor}; // + - -

    Rotate(0,0,0);
}

void Cubo::Draw(){
    for(int i = 0; i < 6; i++){
        DrawFace(i);
    }
}

void Cubo::Render(Point* p, int face){
    Point P1 = p[0];
    Point P2 = p[1];
    Point P3 = p[2];
    Point P4 = p[3];

    Point u = normalize(subtract(P2, P1));
    Point n = normalize(cross(u, subtract(P3, P1)));
    Point v = normalize(cross(n, u));

    double x1 = dot(subtract(P1, P1), u), y1 = dot(subtract(P1, P1), v);
    double x2 = dot(subtract(P2, P1), u), y2 = dot(subtract(P2, P1), v);
    double x3 = dot(subtract(P3, P1), u), y3 = dot(subtract(P3, P1), v);
    double x4 = dot(subtract(P4, P1), u), y4 = dot(subtract(P4, P1), v);

    int x_min = (int)ceil(fmin(fmin(x1, x2), fmin(x3,x4)));
    int x_max = (int)ceil(fmax(fmax(x1, x2), fmax(x3,x4)));
    int y_min = (int)ceil(fmin(fmin(y1, y2), fmin(y3,y4)));
    int y_max = (int)ceil(fmax(fmax(y1, y2), fmax(y3,y4)));


    sizes[face] = 0;
    for (int x = x_min; x <= x_max; x++) {
        for (int y = y_min; y <= y_max; y++) {
            Point pixel = add(P1, add(scale(u, x), scale(v, y)));
            faces[face][sizes[face]++] = pixel;
        }
    }
}

void Cubo::Rotate(double angX, double angY, double angZ){
    Point f[6][4] = {
            {vertices[6], vertices[3], vertices[2], vertices[7]}, //G D C H
            {vertices[6], vertices[4], vertices[5], vertices[3]}, //G E F D
            {vertices[6], vertices[7], vertices[1], vertices[4]}, //G H B D

            {vertices[4], vertices[1], vertices[0], vertices[5]}, //E B A F
            {vertices[1], vertices[0], vertices[2], vertices[7]}, //B A C H
            {vertices[0], vertices[2], vertices[5], vertices[7]}  //E B D C
    };

    for(int i = 0; i < 6; i++){
        Render(f[i], i);
        rotate(faces[i], sizes[i], angX, angY, angZ);
    }
}

void Cubo::DrawFace(int face){
    glColor3fv(cores[face]);
    for(int i = 0; i < sizes[face]; i++){
        check(faces[face][i]);
    }
}

void Cubo::Translate(int x, int y, int z){
    for(int i = 0; i < 8; i++){
        vertices[i].x += x;
        vertices[i].y += y;
        vertices[i].z += z;
    }
}