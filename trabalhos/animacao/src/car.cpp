#include "../include/car.hpp"
#include "../include/ground.hpp"
#include "../include/point.hpp"
#include "../include/circle.hpp"


double wheel_rad = 15;
double center_rad = wheel_rad/2;

struct Car{
    Point p;
    int w, h;
    int direction;
};

Car bus = {{0, ROAD_Y +  ROAD_HEIGHT / 2 + (int)wheel_rad}, 200, 75, 1};

void handle_car(Car* c){
    if(!c) return;
    if(c->p.x > SIZE) c->p.x = -(c->w) - 50;
}

void draw_bus(Car* c){    
    handle_car(c);

    //lataria
    glColor3f(0.7, 0.7, 0.0);
    glBegin(GL_QUADS);
        glVertex2i(c->p.x, c->p.y);
        glVertex2i(c->p.x, c->p.y + c->h);
        glVertex2i(c->p.x + c->w, c->p.y + c->h);
        glVertex2i(c->p.x + c->w, c->p.y);
    glEnd();    

    int front_h = 35;
    int front_w = 16;
    glBegin(GL_QUADS);
        glVertex2i(c->p.x + c->w, c->p.y);
        glVertex2i(c->p.x + c->w, c->p.y + front_h);
        glVertex2i(c->p.x + c->w + front_w, c->p.y + front_h);
        glVertex2i(c->p.x + c->w + front_w, c->p.y);
    glEnd();    
    
    
    //rodas
    Circle r1 = {{c->p.x + 20, c->p.y}, wheel_rad};
    Circle c1 = {{c->p.x + 20, c->p.y}, center_rad};
    glColor3f(0.0, 0.0, 0.0);
    draw_circle(r1);
    glColor3f(0.5, 0.5, 0.5);
    draw_circle(c1);


    Circle r2 = {{c->p.x + c->w - 20, c->p.y}, wheel_rad};
    Circle c2 = {{c->p.x + c->w - 20, c->p.y}, center_rad};

    glColor3f(0.0, 0.0, 0.0);
    draw_circle(r2);
    glColor3f(0.5, 0.5, 0.5);
    draw_circle(c2);


    //janelas
    int window_dimension = 20;
    int padding = 7;


    glColor3f(0.4, 0.7, 1);
    glBegin(GL_QUADS);
        for(int x = c->p.x + padding; x+window_dimension <= c->p.x + c->w; x += padding + window_dimension){
            glVertex2i(x, c->p.y + c->h - (wheel_rad + padding));
            glVertex2i(x, c->p.y + c->h - (wheel_rad + padding + window_dimension));
            glVertex2i(x + window_dimension, c->p.y + c->h - (wheel_rad + padding + window_dimension));
            glVertex2i(x + window_dimension, c->p.y + c->h - (wheel_rad + padding));    
        }

    glEnd();

}

void update_cars(){
    bus.p.x += bus.direction;


    draw_bus(&bus);

}

