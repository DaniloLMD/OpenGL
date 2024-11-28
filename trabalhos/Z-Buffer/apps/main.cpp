#include "../include/opengl_manager.hpp"
#include "../include/point.hpp"
#include "../include/transformacoes_geometricas.hpp"
#include "../include/z_buffer.hpp"
#include "../include/cubo.hpp"
#include <stdio.h>

double angX = 0, angY = 0, angZ = 0;

bool eixo = false;

#define N_CUBOS 3
const int size = 50;
const int distance = 200;
int sizes[N_CUBOS] = {size, size, size};
Cubo cubos[N_CUBOS] = {
    Cubo({0, 0, 0}, sizes[0]),
    Cubo({distance, 0, 50}, sizes[1]),
    Cubo({-distance, 0, -50}, sizes[1])
};

void draw_eixos(){
    glColor3f(1,1,1);

    for(int x = -SIZE; x <= SIZE; x++){
        check({x, 0, 0});
    }

    for(int y = -SIZE; y <= SIZE; y++){
        check({0, y, 0});
    }

    for(int z = -SIZE; z <= SIZE; z++){
        check({0, 0, z});
    }

}

void draw_cubos(){
    for(int i = 0; i < N_CUBOS; i++){
        cubos[i].Draw();
    }
}

void rotate_cubos(){
    for(int i = 0; i < N_CUBOS; i++){
        cubos[i].Rotate(angX, angY, angZ);
    }
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

    glScalef(3,3,3);
    glOrtho(left, right, bottom, top, -SIZE, SIZE);

    initialize_z_buffer();

    draw_cubos();
    if(eixo) draw_eixos();

    glutSwapBuffers();
    glFlush();

}

double rotate_change = 5;
void keyboard(int key, int x, int y){
    if(key < GLUT_KEY_LEFT || key > GLUT_KEY_DOWN) return;
    if(key == GLUT_KEY_DOWN){
        angX += rotate_change;
    }
    if(key == GLUT_KEY_UP){
        angX -= rotate_change;
    }
    if(key == GLUT_KEY_LEFT){
        angY += rotate_change;
    }
    if(key == GLUT_KEY_RIGHT){
        angY -= rotate_change;
    }

    rotate_cubos();
    display();
}   

void key(unsigned char key, int x, int y){

    if(key == 'z') angZ += rotate_change;
    if(key == 'x') angZ -= rotate_change;
    if(key == ' ') eixo = !eixo;
    
    rotate_cubos();
    display();  
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    initialize(w, h, left, right, bottom, top);

    //Funções a serem chamadas durante a execução do programa
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    glutKeyboardFunc(key);

    //Inicio do programa
    glutMainLoop();

    return 0;
}
