#ifndef __Z_BUFFER_HPP__
#define __Z_BUFFER_HPP__

#include "point.hpp"
#include "opengl_manager.hpp"

#define Z_SIZE (2*SIZE+50)

const int INF = int(1e9);

double z_buffer[Z_SIZE][Z_SIZE];

void initialize_z_buffer();
void check(Point p);

#endif