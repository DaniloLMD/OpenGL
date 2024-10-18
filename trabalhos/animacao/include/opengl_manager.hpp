#ifndef __SDL_MANAGER_HPP__
#define __SDL_MANAGER_HPP__

#include <math.h>
#include <GL/glut.h>

#define PI acos(-1)

// #define SIZE 1000  // tamanho da janela e da viewport
int SIZE = 1000;

const int SCREEN_W = SIZE, SCREEN_H = SIZE;


int h = SIZE, w = SIZE; //dimensoes da janela
GLfloat left = 0, right = SIZE, bottom = 0, top = SIZE; //dimensoes da janela de visualização


void initialize();

double rad(double ang);


#endif