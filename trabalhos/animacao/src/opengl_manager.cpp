#include "../include/opengl_manager.hpp"
#include <stdlib.h>
#include <time.h>

void initialize(){
    srand(time(0));

    //Inicialização do OpenGL, da janela principal e da janela de visualização
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(w, h); 
    glutCreateWindow("Animation");

    glClearColor(0.3f, 0.3f, 0.5f, 1.0f);
    gluOrtho2D(left, right, bottom, top);
}