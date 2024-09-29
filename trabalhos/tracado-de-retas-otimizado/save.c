#include <stdio.h>
#include <GL/glut.h>

typedef struct point{
    int x, y;
} Point;

void inc_line(Point a, Point b){
    int x1 = a.x, y1 = a.y;
    int x2 = b.x, y2 = b.y;

    int dx = x2 - x1;
    int dy = y2 - y1;
    int d = 2 * dy - dx;
    int incE = 2 * dy;
    int incNE = 2 * (dy - dx);
    int x = x1;
    int y = y1;

    draw_pixel(x, y);

    while(x < x2){
        if(d <= 0){ //escolhe E
            d += incE;
        }
        else{ //escolhe NE
            d += incNE;
            y++;    
        }
        x++;
        draw_pixel(x, y);
    }
}


int main(){


    return 0;
}