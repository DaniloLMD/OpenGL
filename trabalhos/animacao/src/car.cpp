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

Car bus = {{0, ROAD_Y +  ROAD_HEIGHT / 2 + (int)wheel_rad}, 175, 75, 1};
Car car = {{SIZE, ROAD_Y + 2* (int)wheel_rad}, 130, 30, -1};

void handle_car(Car* c){
    if(!c) return;
    if(c->p.x > SIZE && c->direction > 0) c->p.x = - c->w - 100;
    else if(c->p.x + c->w < 0 && c->direction < 0) c->p.x = SIZE + c->w;
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

    //farol
    glColor3f(1, 1, 1);
    Circle farol = {{c->p.x + c->w + front_w/2, c->p.y + front_h/ 2}, 4};
    draw_circle(farol);
    
    
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


void draw_car(Car* c){    
    handle_car(c);
    int x, y, diag;

    //lataria
    glColor3f(1.0, 0.1, 0.1);
    glBegin(GL_QUADS);
        glVertex2i(c->p.x, c->p.y);
        glVertex2i(c->p.x, c->p.y + c->h);
        glVertex2i(c->p.x + c->w, c->p.y + c->h);
        glVertex2i(c->p.x + c->w, c->p.y);
    glEnd();   

    //topo
    x = c->p.x;
    y = c->p.y + c->h;
    int altura = 25;
    int d = 20;

    glBegin(GL_POLYGON);
        glVertex2i(x, y);
        glVertex2i(x + d, y + altura);
        glVertex2i(x + c->w -d, y + altura);
        glVertex2i(x + c->w, y);
    glEnd(); 

    //tras
    d = 20;
    x = c->p.x + c->w; 
    y = c->p.y;
    diag = 10;

    glBegin(GL_POLYGON);
        glVertex2i(x, y);
        glVertex2i(x, y + c->h);
        glVertex2i(x + d, y + c->h - diag);
        glVertex2i(x + d, y);
    glEnd(); 

    //frente
    d = 15;
    x = c->p.x; 
    y = c->p.y;
    diag = 15;

    glBegin(GL_POLYGON);
        glVertex2i(x, y);
        glVertex2i(x, y + c->h);
        glVertex2i(x - d, y + c->h);
        glVertex2i(x - d - diag, y);
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
    int padding = 7;
    int window_h = 22;
    int window_w = 45;
    x = c->p.x + 2* padding;
    y = c->p.y + c->h;
    diag = 15;

    glColor3f(0.4, 0.7, 1);     
    glBegin(GL_QUADS);
        glVertex2i(x, y);
        glVertex2i(x + diag, y + window_h);
        glVertex2i(x + window_w, y + window_h);
        glVertex2i(x + window_w, y);    

        x += window_w + 2*padding;

        glVertex2i(x, y);
        glVertex2i(x, y + window_h);
        glVertex2i(x + window_w - diag, y + window_h);
        glVertex2i(x + window_w, y);    
    glEnd();

    //farol

    glColor3f(1, 1, 0.0);
    Circle farol = {{c->p.x - 13,c->p.y + c->h/ 2}, 4};
    draw_circle(farol);
}


void change_direction(Car* c){
    glPushMatrix();
    glTranslated(c->p.x, c->p.y , 0);
    glRotated(180, 0, 1, 0);
    glTranslated(-c->p.x, -c->p.y , 0);
    glPopMatrix();

    c->direction = -c->direction;
    if(c->direction > 0){
        c->p.x = 0 - c->w;
        if(c->p.y < ROAD_Y +  ROAD_HEIGHT / 2){
            c->p.y = ROAD_Y +  ROAD_HEIGHT / 2 + (int) wheel_rad;
        }
    }
    if(c->direction < 0){
        c->p.x = SIZE + c->w;
        if(c->p.y >= ROAD_Y +  ROAD_HEIGHT / 2){
            c->p.y = ROAD_Y + (int) wheel_rad;
        }
    }

}

bool coisa = false;
void update_cars(){
    bus.p.x += bus.direction;
    car.p.x += car.direction;

    draw_bus(&bus);
    draw_car(&car);

}

