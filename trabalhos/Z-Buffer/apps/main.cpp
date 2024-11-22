#include "../include/opengl_manager.hpp"
#include "../include/point.hpp"
#include "../include/transformacoes_geometricas.hpp"
#include "../include/z_buffer.hpp"
#include "../include/cubo.hpp"
#include <stdio.h>

const int N = int(1e5);

double angX = 0, angY = 0, angZ = 0;

#define N_CUBOS 3
const int size = 100;
int sizes[N_CUBOS] = {size, size, size};
Cubo cubos[N_CUBOS] = {
    Cubo({0, 0, 0}, sizes[0]),
    Cubo({300, 0, 50}, sizes[1]),
    Cubo({-300, 0, -50}, sizes[1])
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
    glOrtho(left, right, bottom, top, -SIZE, SIZE);
    // glRotatef(angX, 1.0, 0.0, 0.0);
    // glRotatef(angY, 0.0, 1.0, 0.0);
    // glRotatef(angZ, 0.0, 0.0, 1.0);

    initialize_z_buffer();

    draw_cubos();
    // draw_eixos();

    glutSwapBuffers();
    glFlush();

}

double rotate_change = 4;
void keyboard(int key, int x, int y){
    if(key < GLUT_KEY_LEFT || key > GLUT_KEY_DOWN) return;
    if(key == GLUT_KEY_DOWN){
        angX += rotate_change;
    }
    if(key == GLUT_KEY_UP){
        angX -= rotate_change;
    }
    if(key == GLUT_KEY_LEFT){
        // angZ += rotate_change;
        angY += rotate_change;
    }
    if(key == GLUT_KEY_RIGHT){
        // angZ -= rotate_change;
        angY -= rotate_change;
    }

    rotate_cubos();
    display();
}   

void key(unsigned char key, int x, int y){

    if(key == 'z') angZ += rotate_change;
    if(key == 'x') angZ -= rotate_change;
    
    

    rotate_cubos();
    display();  
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    initialize(w, h, left, right, bottom, top);

    //Funções a serem chamadas durante a execução do programa
    display();

    glutSpecialFunc(keyboard);
    glutKeyboardFunc(key);

    //Inicio do programa
    glutMainLoop();

    return 0;
}
