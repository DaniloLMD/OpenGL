#include "../include/house.hpp"
#include "../include/point.hpp"
#include "../include/ground.hpp"

void draw_house(Point p){
    p.x += 30;
    p.y += 35;
    ///telhado
    glColor3f(0.990, 0.0, 0.0);
	glBegin(GL_POLYGON);
        glVertex2i(p.x, p.y - 1);
        glVertex2i(p.x, p.y + 25);
        glVertex2i(p.x + 95, p.y + 10);
        glVertex2i(p.x + 95, p.y - 1);
	glEnd();

    ///sombra do telhado
    glColor3f(0.890, 0.0, 0.0);
	glBegin(GL_POLYGON);
        glVertex2i(p.x, p.y - 1);
        glVertex2i(p.x, p.y + 15);
        glVertex2i(p.x + 95, p.y);
	glEnd();

    ///cerca
    glColor3f(.555, 1.0, 1.0);
	glBegin(GL_POLYGON);
        glVertex2i(p.x + 5, p.y - 35);
        glVertex2i(p.x + 5, p.y - 1);
        glVertex2i(p.x + 90, p.y - 1);
        glVertex2i(p.x + 90, p.y - 35);
	glEnd();

    ///sombra da cerca
    glColor3f(.555, 0.924, 0.930);
	glBegin(GL_POLYGON);
        glVertex2i(p.x + 25, p.y - 35);
        glVertex2i(p.x + 65, p.y - 1);
        glVertex2i(p.x + 90, p.y - 1);
        glVertex2i(p.x + 90, p.y - 35);
	glEnd();

    //porta
    glColor3f(0.38, 0.41, 0.36);
	glBegin(GL_POLYGON);
        glVertex2i(p.x + 45, p.y - 35);
        glVertex2i(p.x + 45, p.y - 5);
        glVertex2i(p.x + 65, p.y - 5);
        glVertex2i(p.x + 65, p.y - 35);
	glEnd();

    ///janelas
    glColor3f(0.38, 0.21, 0.26);
	glBegin(GL_POLYGON);
        glVertex2i(p.x + 10, p.y - 30);
        glVertex2i(p.x + 10, p.y - 15);
        glVertex2i(p.x + 25, p.y - 15);
        glVertex2i(p.x + 25, p.y - 30);
	glEnd();

    glColor3f(0.38, 0.21, 0.26);
	glBegin(GL_POLYGON);
        glVertex2i(p.x + 27, p.y - 30);
        glVertex2i(p.x + 27, p.y - 15);
        glVertex2i(p.x + 42, p.y - 15);
        glVertex2i(p.x + 42, p.y - 30);
	glEnd();

    glColor3f(0.38, 0.21, 0.26);
	glBegin(GL_POLYGON);
        glVertex2i(p.x + 70, p.y - 30);
        glVertex2i(p.x + 70, p.y - 15);
        glVertex2i(p.x + 85, p.y - 15);
        glVertex2i(p.x + 85, p.y - 30);
	glEnd();

    ///telhado secundario
    glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
        glVertex2i(p.x - 35, p.y - 15);
        glVertex2i(p.x - 28, p.y - 1);
        glVertex2i(p.x + 5, p.y - 1);
        glVertex2i(p.x + 5, p.y - 15);
	glEnd();

    ///parede secundaria
    glColor3f(0.555, 0.724, 0.930);
	glBegin(GL_POLYGON);
        glVertex2i(p.x - 30, p.y - 35);
        glVertex2i(p.x - 30, p.y - 15);
        glVertex2i(p.x + 5, p.y - 15);
        glVertex2i(p.x + 5, p.y - 35);
	glEnd();

    ///porta secundaria
    glColor3f(0.11, 0.23, 0.36);
	glBegin(GL_POLYGON);
        glVertex2i(p.x - 25, p.y - 35);
        glVertex2i(p.x - 25, p.y - 25);
        glVertex2i(p.x, p.y - 25);
        glVertex2i(p.x, p.y - 35);
	glEnd();
}

void draw_houses(){

    draw_house({0, GROUND_HEIGHT});

    draw_house({SIZE/2 - 120, GROUND_HEIGHT});

    draw_house({SIZE - 200, GROUND_HEIGHT});

}