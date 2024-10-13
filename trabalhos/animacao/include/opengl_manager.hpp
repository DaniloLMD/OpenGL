#ifndef __SDL_MANAGER_HPP__
#define __SDL_MANAGER_HPP__

#include <math.h>
#include <GL/glut.h>

#define PI acos(-1)

#define SIZE 800  // tamanho da janela e da viewport

int h = SIZE, w = SIZE; //dimensoes da janela
GLfloat left = 0, right = SIZE, bottom = 0, top = SIZE; //dimensoes da janela de visualização


void initialize();


#endif