#include "../include/opengl_manager.hpp"
#include <stdlib.h>
#include <time.h>

void initialize(){
    srand(time(0));

    //Inicialização do OpenGL, da janela principal e da janela de visualização
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(SCREEN_W, SCREEN_H); 
    glutCreateWindow("Animation");

    gluOrtho2D(left, right, bottom, top);
}

//função que recebe um angulo em graus e retorna o mesmo em radianos
double rad(double ang){
    return ang * PI / 180;
}
