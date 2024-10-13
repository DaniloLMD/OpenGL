#include "../include/ground.hpp"

void draw_ground(){

    glColor3fv(verde_escuro);
    glBegin(GL_QUADS);
        glVertex2i(0,0);
        glVertex2i(0,GROUND_HEIGHT);
        glVertex2i(SIZE, GROUND_HEIGHT);
        glVertex2i(SIZE,0);
    glEnd();

    int new_h = GROUND_HEIGHT - 50;
    glColor3fv(verde_claro);
    glBegin(GL_QUADS);
        glVertex2i(0, new_h);
        glVertex2i(0, GROUND_HEIGHT);
        glVertex2i(SIZE, GROUND_HEIGHT);
        glVertex2i(SIZE,new_h);
    glEnd();

    //desenhando a estrada
    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_QUADS);
        glVertex2i(0, ROAD_Y);
        glVertex2i(0, ROAD_HEIGHT);
        glVertex2i(SIZE, ROAD_HEIGHT);
        glVertex2i(SIZE, ROAD_Y);
    glEnd();

    int line_size = 20;
    int line_space = 20;
    new_h = (ROAD_Y + ROAD_HEIGHT) / 2;
    glColor3f(0.8, 0.8, 0.8);
    glLineWidth(2);
    glBegin(GL_LINES);
        for(int i = 0; i < SIZE; i += line_size + line_space){
            glVertex2i(i, new_h);
            glVertex2i(i + line_size, new_h);
        }
    glEnd();
    glLineWidth(3);
}