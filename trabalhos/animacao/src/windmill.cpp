#include "../include/windmill.hpp"
#include "../include/circle.hpp"
#include "../include/ground.hpp"

int windmill_d = 10;
int windmill_w = 40;
int windmill_h = 200;
double windmill_r = 20;

int helice_w = 125;
int helice_d = 10;

void draw_windmill(Point p, double angulo = 0){
    //base
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_QUADS);
        glVertex2i(p.x, p.y);
        glVertex2i(p.x + windmill_d, p.y + windmill_h);
        glVertex2i(p.x + windmill_w - windmill_d, p.y + windmill_h);
        glVertex2i(p.x + windmill_w, p.y);
    glEnd();

    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_POLYGON);
        glVertex2i(p.x, p.y);
        glVertex2i(p.x + windmill_d, p.y + windmill_h);
        glVertex2i(p.x + windmill_w/2, p.y + windmill_h);
        glVertex2i(p.x + windmill_w/2, p.y);
    glEnd();
    
    glColor3f(0.8, 0.8, 0.8);
    Circle head = {{p.x + windmill_w/2, p.y + windmill_h}, windmill_r}; 
    draw_circle(head);

    //helices
    int x, y;

    x = head.center.x;
    y = head.center.y + head.rad;


    //helice do centro
    glColor3f(0.8,0.8,0.8);

    for(int i = 0; i < 3; i++){
        glPushMatrix();
        glTranslated(head.center.x, head.center.y, 0);
        glRotated(120*i + angulo, 0, 0, 1);
        glTranslated(-head.center.x, -head.center.y, 0);

        glBegin(GL_POLYGON);
                glVertex2i(x, y);

                glVertex2i(x + helice_d, y +helice_w / 4);

                glVertex2i(x, y + helice_w);
                glVertex2i(x - helice_d, y + helice_w / 4);
        glEnd();

        glPopMatrix();
    }
}

double angulo = 0;
void update_windmills(){
    draw_windmill({330, GROUND_HEIGHT}, angulo);
    draw_windmill({SIZE/2 + 125, GROUND_HEIGHT}, angulo);

    angulo += 0.8;
}
