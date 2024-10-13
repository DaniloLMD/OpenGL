#include "../include/opengl_manager.hpp"
#include "../include/point.hpp"
#include "../include/circle.hpp"
#include "../include/sun.hpp"
#include "../include/ground.hpp"
#include "../include/house.hpp"
#include "../include/tree.hpp"
#include "../include/car.hpp"

#include <stdio.h>

void display(int){
    glClear(GL_COLOR_BUFFER_BIT);

    update_sun();



    draw_trees();

    draw_ground();  
    update_cars();
    draw_houses();


    glutSwapBuffers();
}

void idle(){
    glutTimerFunc(500, display, 3);
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    initialize();

    //Funções a serem chamadas durante a execução do programa
    glutIdleFunc(idle);

    //Inicio do programa
    glutMainLoop();

    return 0;
}