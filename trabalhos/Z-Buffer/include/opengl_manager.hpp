#ifndef __SDL_MANAGER_HPP__
#define __SDL_MANAGER_HPP__

#include <math.h>
#include <GL/glut.h>


#define SIZE 1000 // tamanho da janela e da viewport

int h = SIZE, w = SIZE; //dimensoes da janela
GLfloat left = -SIZE/2, right = SIZE/2, bottom = -SIZE/2, top = SIZE/2; //dimensoes da janela de visualização

void initialize(int w, int h, int left, int right, int bottom, int top);


#endif