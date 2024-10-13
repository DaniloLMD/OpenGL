#include "../include/cloud.hpp"
#include "../include/circle.hpp"

struct Cloud{
    Point pos;
    int direction;
};

int start = 50;
void handle_cloud(Cloud* c){
    if(c->pos.x > SIZE && c->direction > 0) c->pos.x = 0 - start;
    if(c->pos.x < 0 && c->direction < 0) c->pos.x = SIZE + start;
}

void draw_cloud(Cloud* c){
    if(!c) return;
    handle_cloud(c);   

    c->pos.x += c->direction;

    Point p = c->pos;

    glColor3f(0.95, 0.95, 0.95);

    draw_circle({{p.x + 15, p.y + 6}, 15});

    draw_circle({{p.x + 35, p.y + 21}, 16});

    draw_circle({{p.x + 55, p.y + 6}, 16});

    draw_circle({{p.x + 45, p.y + 6}, 16});

    for(int i = 40; i >= 0; i -= 5){
        draw_circle({{p.x + i, p.y}, 10});
    }

}

Cloud clouds[] = {
    {{0, SIZE - 80},1},
    {{SIZE + 10, SIZE - 200},-1},
    {{-10, SIZE - 350},1},
    {{SIZE + 10, SIZE - 425},-1},
};

void update_clouds(){

    for(int i = 0; i < sizeof(clouds) / sizeof(Cloud); i++)
        draw_cloud(&clouds[i]);

}