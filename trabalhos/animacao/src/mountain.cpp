#include "../include/mountain.hpp"
#include "../include/ground.hpp"
#include "../include/circle.hpp"
#include "../include/tree.hpp"

int r = 55;

void draw_mountains(){
    draw_mountain_triangular({-25,GROUND_HEIGHT}, 150, 150);
    draw_mountain_triangular({50,GROUND_HEIGHT}, 150, 100);

    draw_mountain_triangular({SIZE-125,GROUND_HEIGHT}, 150, 150);
    draw_mountain_triangular({SIZE-170,GROUND_HEIGHT}, 150, 120);

    draw_mountain_circular({SIZE/2 - 50, GROUND_HEIGHT}, true);
    draw_mountain_circular({150, GROUND_HEIGHT});
}

void draw_trees_on_mountain(Point p, bool fruto = false){
    draw_tree_2_circles({p.x + 20 - r/2, p.y + r + 2}, fruto);
    draw_tree_triangle({p.x + 65 - r/2, p.y + r + 8}, fruto);
    draw_tree_2_circles({p.x + 85, p.y + r}, fruto);
    draw_tree_triangle({p.x + 115, p.y + r/2 - 2}, fruto);
}

void draw_mountain_circular(Point p, bool trees, bool fruto){

    if(trees) draw_trees_on_mountain(p, fruto);

    //x = 430, y = 90
    glColor3fv(verde_escuro);

    // glColor3f(1,0,0);
    draw_circle({{p.x, p.y},(double) r});

    // glColor3f(1,1,1);
    draw_circle({{p.x + 10, p.y + 3},(double) r});

    // glColor3f(0,1,0);
    draw_circle({{p.x + 20, p.y + 10},(double) r});
    
    // glColor3f(0.5,0.5,0.5);
    draw_circle({{p.x + 30, p.y + 10},(double) r});
    
    // glColor3f(0,0,0);
    draw_circle({{p.x + 40, p.y + 20},(double) r});

    draw_circle({{p.x + 40 + 70, p.y - 20},(double) r});
    draw_circle({{p.x + 30 + 70, p.y - 10},(double) r});
    draw_circle({{p.x + 20 + 70, p.y - 10},(double) r});
    draw_circle({{p.x + 10 + 70, p.y + 3},(double) r});
}

void draw_mountain_triangular(Point p, int w, int h){
    glColor3fv(verde_claro);
    glBegin(GL_TRIANGLES);
        glVertex2i(p.x, p.y);
        glVertex2i(p.x + w/2, p.y + h);
        glVertex2i(p.x + w, p.y);
    glEnd();

    glColor3f(0.1, 0.5, 0.2);
    glBegin(GL_TRIANGLES);
        glVertex2i(p.x, p.y);
        glVertex2i(p.x + w/2, p.y + h);
        glVertex2i(p.x + w/2, p.y);
    glEnd();

};