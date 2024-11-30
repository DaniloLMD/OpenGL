#include "../include/z_buffer.hpp"
#include <stdio.h>

void initialize_z_buffer() {
    for (int i = 0; i < Z_SIZE; i++) {
        for (int j = 0; j < Z_SIZE; j++) {
            z_buffer[i][j] = INF;
        }
    }
}

void check(Point p) {
    if (p.x <= -SIZE || p.x >= SIZE || p.y <= -SIZE || p.y >= SIZE) return;

    int x = (p.x + SIZE);
    int y = (p.y + SIZE);

    if (p.z <= z_buffer[x][y]) {
        draw_point(p);
        z_buffer[x][y] = p.z;
    }
}
