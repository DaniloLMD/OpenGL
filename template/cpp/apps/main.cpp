#include "../include/opengl_manager.hpp"
#include "../include/point.hpp"

#define SIZE 800 // tamanho da janela e da viewport

int h = SIZE, w = SIZE; //dimensoes da janela
GLfloat left = -SIZE, right = SIZE, bottom = -SIZE, top = SIZE; //dimensoes da janela de visualização

void display(){
    glPointSize(20);
    draw_point({(int) (left + right) / 2, (int) (bottom + top) / 2});
    glPointSize(1);

    glutSwapBuffers();
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    initialize(w, h, left, right, bottom, top);

    //Funções a serem chamadas durante a execução do programa
    display();

    //Inicio do programa
    glutMainLoop();

    return 0;
}