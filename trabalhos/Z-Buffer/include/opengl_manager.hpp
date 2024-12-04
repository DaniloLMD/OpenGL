#ifndef __SDL_MANAGER_HPP__
#define __SDL_MANAGER_HPP__

#include <math.h>
#include <GL/glut.h>


#define SIZE 1000 // tamanho da janela e da viewport

int h = SIZE, w = SIZE; //dimensoes da janela
int dim = 500;
GLfloat left = -dim, right = dim, bottom = -dim, top = dim; //dimensoes da janela de visualização

void initialize();


#endif