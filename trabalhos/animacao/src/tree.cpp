#include "../include/tree.hpp"
#include "../include/circle.hpp"
#include "../include/ground.hpp"

void draw_trees(){

    draw_tree_2_circles({SIZE/2 - 35, GROUND_HEIGHT});
    draw_tree_2_circles({SIZE/2 + 10, GROUND_HEIGHT});
    draw_tree_triangle({SIZE/2 + 70, GROUND_HEIGHT});

    for(int i = 0; i < 3; i++){
        int x = 145 + 50 * i;
        if(i&1) draw_tree_triangle({x, GROUND_HEIGHT}, true);
        else draw_tree_2_circles({x, GROUND_HEIGHT}, true);
    }


}

void draw_tronco(Point p, int altura, int largura){
    //tronco
    glColor3f(0.8, 0.5, 0.1);
    glBegin(GL_QUADS);
        glVertex2i(p.x, p.y);
        glVertex2i(p.x, p.y + altura);
        glVertex2i(p.x + largura, p.y + altura);
        glVertex2i(p.x + largura, p.y);
    glEnd();
}

void draw_tree_triangle(Point p, bool frutos){

    int altura = 30;
    int largura = 10;
    int borda = 18;

    if(frutos){
        glColor3f(1.0, 0.3, 0.0);
        int rad = 5;
        draw_circle({{p.x - borda + rad + 3, p.y + altura - rad + 4}, (double) rad});
        draw_circle({{p.x + largura + borda - rad - 3, p.y + altura - rad + 4}, (double) rad});
    }



    draw_tronco(p, altura , largura);

    //folha
    glBegin(GL_TRIANGLES);
    glColor3f(0.68, 1.0, 0.18);
        glVertex2i(p.x - borda, p.y + altura);
        glVertex2i(p.x + largura / 2, p.y + altura + borda);
        glVertex2i(p.x + largura + borda, p.y + altura);
    glEnd();

    //sombra
    glColor3f(0.3, 0.7, 0.1);
    glBegin(GL_TRIANGLES);
        glVertex2i(p.x - borda, p.y + altura);
        glVertex2i(p.x + largura / 2, p.y + altura + borda);
        glVertex2i(p.x + largura / 2 , p.y + altura);
    glEnd();
}

void draw_tree_2_circles(Point p, bool frutos){
    int altura = 25;
    int largura = 10;


    draw_tronco(p, altura , largura);

    //folha
    glColor3f(0.3, 0.7, 0.1);

    int rad = 15;

    Circle c1 = {{p.x + largura/2, p.y + altura}, (double) rad};
    Circle c2 = {{p.x + largura/2, p.y + altura + rad}, (double) rad};

    glColor3f(0.3, 0.7, 0.1);
    draw_circle(c1);
    draw_circle(c2);



    if(!frutos) return;

    glColor3f(1.0, 0.0, 0.0);
    int rad_folha = rad;
    rad = 3;    

    //frutas
    draw_circle({{p.x + largura/2, p.y + altura + rad_folha + rad}, (double) rad});

    draw_circle({{p.x + largura/2, p.y + altura - rad}, (double) rad});
    
    draw_circle({{p.x + largura/2 - rad_folha, p.y + altura}, (double) rad});
    draw_circle({{p.x + largura/2 + rad_folha, p.y + altura}, (double) rad});

    draw_circle({{p.x + largura/2, p.y + altura + rad_folha / 2}, (double) rad});

    draw_circle({{p.x + largura/2 - rad_folha, p.y + altura + rad_folha}, (double) rad});
    draw_circle({{p.x + largura/2 + rad_folha, p.y + altura + rad_folha}, (double) rad});

}