#include "../include/cubo.hpp"
#include "../include/z_buffer.hpp"
#include "../include/transformacoes_geometricas.hpp"
#include "../include/cores.hpp"
#include <math.h>
#include <stdio.h>

GLfloat cor_padrao[][3] = {RED, GREEN, BLUE, YELLOW, PINK, WHITE};


Cubo::Cubo(Point center, int tam, GLfloat cores[6][3]) : center(center), tam(tam){
    int dist = tam/2;

    vertices[0] = {center.x + dist, center.y + dist, center.z + dist, center.cor}; // + + +
    vertices[1] = {center.x + dist, center.y + dist, center.z - dist, center.cor}; // + + -
    vertices[2] = {center.x + dist, center.y - dist, center.z + dist, center.cor}; // + - +
    vertices[3] = {center.x - dist, center.y - dist, center.z + dist, center.cor}; // - - +
    vertices[4] = {center.x - dist, center.y + dist, center.z - dist, center.cor}; // - + -
    vertices[5] = {center.x - dist, center.y + dist, center.z + dist, center.cor}; // - + +
    vertices[6] = {center.x - dist, center.y - dist, center.z - dist, center.cor}; // - - -
    vertices[7] = {center.x + dist, center.y - dist, center.z - dist, center.cor}; // + - -

    if(cores){
        for(int i = 0; i < 6; i++){
            for(int j = 0; j < 3; j++){
                this->cores[i][j] = cores[i][j];
            }
        }
    }

    Rotate(0,0,0);
}

void Cubo::DrawVertices(){
    glPointSize(10);

    glBegin(GL_POINTS);
        for(int i = 0; i < 8; i++){
            glColor3fv(cores[i]);
            glVertex3i(vertices_rotacionados[i].x, vertices_rotacionados[i].y, vertices_rotacionados[i].z);
        }
    glEnd();

    glPointSize(1);
}

void Cubo::Draw(){
    RenderFaces();
    for(int i = 0; i < 6; i++){
        glColor3fv(cores[i]);
        DrawFace(face_vertices[i]);
    }
}

void Cubo::RenderFaces(){
    face_vertices[0] = {vertices_rotacionados[6], vertices_rotacionados[3], vertices_rotacionados[2], vertices_rotacionados[7]}; //G D C H
    face_vertices[1] = {vertices_rotacionados[6], vertices_rotacionados[4], vertices_rotacionados[5], vertices_rotacionados[3]}; //G E F D
    face_vertices[2] = {vertices_rotacionados[6], vertices_rotacionados[7], vertices_rotacionados[1], vertices_rotacionados[4]}; //G H B E
    face_vertices[3] = {vertices_rotacionados[4], vertices_rotacionados[1], vertices_rotacionados[0], vertices_rotacionados[5]}; //E B A F
    face_vertices[4] = {vertices_rotacionados[1], vertices_rotacionados[0], vertices_rotacionados[2], vertices_rotacionados[7]}; //B A C H
    face_vertices[5] = {vertices_rotacionados[0], vertices_rotacionados[2], vertices_rotacionados[3], vertices_rotacionados[5]}; //A C D F
}

void Cubo::Rotate(double angX, double angY, double angZ){
    for(int i = 0; i < 8; i++){
        vertices_rotacionados[i] = vertices[i];
    }
    rotate(vertices_rotacionados, 8, angX, angY, angZ);
}

void Cubo::Translate(int x, int y, int z){
    for(int i = 0; i < 8; i++){
        vertices[i].x += x;
        vertices[i].y += y;
        vertices[i].z += z;

        vertices_rotacionados[i].x += x;
        vertices_rotacionados[i].y += y;
        vertices_rotacionados[i].z += z;
    }
    Draw();
}


void Cubo::DrawFace(std::vector<Point>& v){
    Point w = subtract(v[1], v[0]);
    Point u = subtract(v[3], v[0]);

    int len_w = len(w);
    int len_u = len(u);
    
    w = normalize(w);
    u = normalize(u);

    int rodados = 0;
    for(double i = 0; i <= len_w; i += 0.5){
        Point w2 = scale(w, i); 
        for(double j = 0; j <= len_u; j += 0.5){
            Point u2 = scale(u, j);
            Point p = add(w2, u2);
            p = add(p, v[0]);
            check(p);
        }
    }

}