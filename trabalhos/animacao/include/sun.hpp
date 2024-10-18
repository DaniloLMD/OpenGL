#ifndef __SUN_H__
#define __SUN_H__

#include "circle.hpp"
#include "opengl_manager.hpp"
#include "ground.hpp"

#define SUN_RAD 70
#define SUN_HEIGHT GROUND_HEIGHT - SUN_RAD

Circle sun = {{0, SUN_HEIGHT}, SUN_RAD};
Circle moon = {{SIZE, SUN_HEIGHT}, SUN_RAD};
Circle moon2 = {{SIZE - 30, SUN_HEIGHT}, SUN_RAD};

void update_sun();

GLfloat sky_color[][3] = {{0.6, 0.6, 0.8}, {0.3, 0.3, 0.5}};


#endif  