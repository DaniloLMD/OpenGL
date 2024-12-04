#include "../include/opengl_manager.hpp"
#include "../include/point.hpp"
#include "../include/transformacoes_geometricas.hpp"
#include "../include/z_buffer.hpp"
#include "../include/cubo.hpp"
#include "../include/cores.hpp"
#include <stdio.h>

double angX = 0, angY = 0, angZ = 0;
int translate_change = 15;
double rotate_change = 5;

bool eixo = false;
bool stop_rotation = false;

#define N_CUBOS 3
const int size = 65;
const int distance = 2*size;
int sizes[] = {size, size, size};
GLfloat cores[3][6][3] = {
    {RED, GREEN, BLUE, YELLOW, PINK, WHITE},
    {YELLOW, PINK, RED, WHITE, GREEN, BLUE},
    {BROWN, RED, GREEN, BLUE, WHITE, GRAY}
};
Cubo cubos[] = {
    Cubo({0, 0, 0}, sizes[0], cores[0]),
    Cubo({distance, 0, 50}, sizes[1], cores[1]),
    Cubo({-distance, 0, -50}, sizes[1], cores[1])
};

void draw_eixos(){
    glColor3f(1,1,1);

    for(int x = -SIZE; x <= SIZE; x++){
        check({double(x), 0, 0});
    }

    for(int y = -SIZE; y <= SIZE; y++){
        check({0, double(y), 0});
    }

    for(int z = -SIZE; z <= SIZE; z++){
        check({0, 0, double(z)});
    }

}

void initialize_cubos(){
    for(int i = 0; i < N_CUBOS; i++){
        for(int j = 0; j < j; j++){
            for(int k = 0; k < 3; k++){
                cubos[i].cores[j][k] = cores[i][j][k];
            }
        }
    }
}

void draw_cubos(){
    for(int i = 0; i < N_CUBOS; i++){
        cubos[i].Draw();
    }
}

void rotate_cubos(){
    for(int i = 0; i < N_CUBOS; i++){
        if(i && stop_rotation) break;
        cubos[i].Rotate(angX, angY, angZ);
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);


    double scale = 2;
    glOrtho(left, right, bottom, top, -INF, INF);

    glScalef(scale, scale, scale);

    initialize_z_buffer();

    if(eixo) draw_eixos();
    draw_cubos();
    

    glutSwapBuffers();
    glFlush();

}

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

    if(key == 'z') angZ += rotate_change, rotate_cubos();
    if(key == 'x') angZ -= rotate_change, rotate_cubos();
    if(key == ' ') eixo = !eixo;
    if(key == '*') stop_rotation = !stop_rotation;

    int movx = 0, movy = 0, movz = 0;

    if(key == 'a'){
        movx = -translate_change;
    }
    if(key == 'd'){
        movx = translate_change;
    }
    if(key == 'w'){
        movy = translate_change;
    }
    if(key == 's'){
        movy = -translate_change;
    }
    if(key == 'q'){
        movz = translate_change;
    }
    if(key == 'e'){
        movz = -translate_change;
    }
    cubos[0].Translate(movx, movy, movz);

    display();  
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    initialize();

    initialize_cubos();

    //Funções a serem chamadas durante a execução do programa
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    glutKeyboardFunc(key);


    //Inicio do programa
    glutMainLoop();

    return 0;
}
