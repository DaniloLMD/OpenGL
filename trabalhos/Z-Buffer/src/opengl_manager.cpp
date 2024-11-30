#include "../include/opengl_manager.hpp"
#include <stdlib.h>

void initialize(){
    //Inicialização do OpenGL, da janela principal e da janela de visualização
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB);

    glutInitWindowSize(w, h); 
    glutCreateWindow("Z-Buffer");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    gluOrtho2D(left, right, bottom, top);
}