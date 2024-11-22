#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "../include/transformacoes_geometricas.hpp"

#define PI acos(-1)

// Função que recebe um ângulo em graus e retorna o mesmo em radianos
double rad(double ang) {
    return ang * PI /   180; 
}

// Função que recebe um conjunto de pontos e os transladam (x, y, z)
void translate(Point v[3], int size, GLfloat x, GLfloat y, GLfloat z) {
    for (int i = 0; i < size; i++) {
        v[i].x += x;
        v[i].y += y;
        v[i].z += z;
    }
}

// Função que calcula o ponto central de um conjunto de pontos
Point center(Point v[], int size) {
    Point c = {0,0,0};
    for (int i = 0; i < size; i++) {
        c.x += v[i].x / size;
        c.y += v[i].y / size;
        c.z += v[i].z / size;
    }
    return c;
}

// Função que recebe um conjunto de pontos e os rotaciona em torno de um eixo em 3D
void rotate(Point v[], int size, double angX, double angY, double angZ) {
    Point c = center(v, size);
    angX = rad(angX);
    angY = rad(angY);
    angZ = rad(angZ);


    double cosX = cos(angX);
    double sinX = sin(angX);

    double cosY = cos(angY);
    double sinY = sin(angY);

    double cosZ = cos(angZ);
    double sinZ = sin(angZ);


    for (int i = 0; i < size; i++) {
        GLfloat x = v[i].x - c.x;
        GLfloat y = v[i].y - c.y;
        GLfloat z = v[i].z - c.z;

        // Rotação em torno de X
        GLfloat tempY = y * cosX - z * sinX;
        GLfloat tempZ = y * sinX + z * cosX;
        y = tempY;
        z = tempZ;

        // Rotação em torno de Y
        GLfloat tempX = x * cosY + z * sinY;
        z = -x * sinY + z * cosY;
        x = tempX;

        // Rotação em torno de Z
        tempX = x * cosZ - y * sinZ;
        tempY = x * sinZ + y * cosZ;
        x = tempX;
        y = tempY;

        v[i].x = x + c.x;
        v[i].y = y + c.y;
        v[i].z = z + c.z;
    }
}
