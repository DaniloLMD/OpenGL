#include "../include/opengl_manager.hpp"
#include <stdlib.h>

void initialize(int w, int h, int left, int right, int bottom, int top){
    //Inicialização do OpenGL, da janela principal e da janela de visualização
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(w, h); 
    glutCreateWindow("OpenGL CPP Template");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    gluOrtho2D(left, right, bottom, top);
}