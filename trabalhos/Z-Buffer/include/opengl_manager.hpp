#ifndef __SDL_MANAGER_HPP__
#define __SDL_MANAGER_HPP__

#include <math.h>
#include <GL/glut.h>


#define SIZE 900 // tamanho da janela e da viewport

int h = SIZE, w = SIZE; //dimensoes da janela
GLfloat left = -SIZE, right = SIZE, bottom = -SIZE, top = SIZE; //dimensoes da janela de visualização

void initialize(int w, int h, int left, int right, int bottom, int top);


#endif