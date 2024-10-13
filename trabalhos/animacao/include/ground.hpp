#ifndef __GROUND_HPP__
#define __GROUND_HPP__

#include "opengl_manager.hpp"

#define GROUND_HEIGHT SIZE/4

#define ROAD_Y 15
#define ROAD_HEIGHT (GROUND_HEIGHT - 75)

GLfloat verde_claro[] = {0.2, 0.7, 0.2};
GLfloat verde_escuro[] = {0.2, 0.5, 0.2};


void draw_ground();


#endif