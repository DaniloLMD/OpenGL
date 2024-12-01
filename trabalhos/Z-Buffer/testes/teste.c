#include <GL/glut.h>
#include <stdio.h>

GLfloat xRotated, yRotated, zRotated;
const int WINDOW_W = 800;
const int WINDOW_H = 600;

void cubo(){
    int tam = 2;

    int a[3] = {0, 0, 0};
    int b[3] = {tam, 0, 0};
    int c[3] = {0, tam, 0};
    int d[3] = {tam, tam, 0};
    int e[3] = {0, 0, tam};
    int f[3] = {tam, 0, tam};
    int g[3] = {0, tam, tam};
    int h[3] = {tam, tam, tam};

    for(int i = 0; i < 3; i++){
        a[i] -= tam/2;
        b[i] -= tam/2;
        c[i] -= tam/2;
        d[i] -= tam/2;
        e[i] -= tam/2;
        f[i] -= tam/2;
        g[i] -= tam/2;
        h[i] -= tam/2;
    }

    //face debaixo
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
        glVertex3iv(a);
        glVertex3iv(c);
        glVertex3iv(d);
        glVertex3iv(b);
    glEnd();

    //face de cima
    glColor3f(1, 0, 0); 
    glBegin(GL_QUADS);
        glVertex3iv(e);
        glVertex3iv(g);
        glVertex3iv(h);
        glVertex3iv(f);
    glEnd();    

    //face da frente
    glColor3f(0, 1, 0); 
    glBegin(GL_QUADS);
        glVertex3iv(a);
        glVertex3iv(b);
        glVertex3iv(f);
        glVertex3iv(e);
    glEnd();

    //face de tras
    glColor3f(0, 0, 1); 
    glBegin(GL_QUADS);
        glVertex3iv(c);
        glVertex3iv(d);
        glVertex3iv(h);
        glVertex3iv(g);
    glEnd();
    
    //face direita
    glColor3f(1, 1, 0); 
    glBegin(GL_QUADS);
        glVertex3iv(b);
        glVertex3iv(d);
        glVertex3iv(h);
        glVertex3iv(f);
    glEnd();

    //face esquerda
    glColor3f(0.5, 0, 0.5); 
    glBegin(GL_QUADS);
        glVertex3iv(a);
        glVertex3iv(c);
        glVertex3iv(g);
        glVertex3iv(e);
    glEnd();   
}

void single_color(){
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1, 1, 1);
    glVertex3f(0, 2, 0);
    glVertex3f(-1, 0, 1);
    glVertex3f(1, 0, 1);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1, 0, 0); 
    glVertex3f(-1, 0, 1);
    glVertex3f(1, 0, 1);
    glVertex3f(0, 0, -1.4);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0, 1, 0);
    glVertex3f(1, 0, 1);
    glVertex3f(0, 0, -1.4);
    glVertex3f(0, 2, 0);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, -1.4);
    glVertex3f(0, 2, 0);
    glVertex3f(-1, 0, 1);
    glEnd();
}

void mix_color(){
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1, 1, 1); glVertex3f(0, 2, 0);
    glColor3f(1, 0, 0); glVertex3f(-1, 0, 1);
    glColor3f(0, 1, 0); glVertex3f(1, 0, 1);
    glColor3f(0, 0, 1); glVertex3f(0, 0, -1.4);
    glColor3f(1, 1, 1); glVertex3f(0, 2, 0);
    glColor3f(1, 0, 0); glVertex3f(-1, 0, 1);
    glEnd();
}

void draw_eixos(){
    glBegin(GL_LINES);
        glVertex3i(-WINDOW_W, 0,0);
        glVertex3i(WINDOW_W, 0,0);

        glVertex3i(0, -WINDOW_H, 0);
        glVertex3i(0, WINDOW_H, 0);

        glVertex3i(0, 0, -500);
        glVertex3i(0, 0, 500);
    glEnd();
}

void display(void) {
    glMatrixMode(GL_MODELVIEW);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glColor3f(0.5, 0.5, 0.5);
    glLineWidth(50);

    // draw_eixos();
    cubo();
    // single_color();


    glLoadIdentity();
    glTranslatef(0.0, 0.0, -8.0);
    glRotatef(xRotated, 1.0, 0.0, 0.0);
    glRotatef(yRotated, 0.0, 1.0, 0.0);
    glRotatef(zRotated, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);


    
    
    glFlush();
}

void reshape(int x, int y) {
    if (y == 0 || x == 0) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);
    glViewport(0, 0, x, y);
}

int pressed[4];
void idle(){
    double rotate_change = 0.03;
    if(pressed[GLUT_KEY_DOWN - GLUT_KEY_LEFT]){
        xRotated += rotate_change;
    }
    if(pressed[GLUT_KEY_UP - GLUT_KEY_LEFT]){
        xRotated -= rotate_change;
    }
    if(pressed[GLUT_KEY_LEFT - GLUT_KEY_LEFT]){
        // zRotated += rotate_change;
        yRotated += rotate_change;
    }
    if(pressed[GLUT_KEY_RIGHT - GLUT_KEY_LEFT]){
        // zRotated -= rotate_change;
        yRotated -= rotate_change;
    }

    display();
}

void keyboard(int key, int x, int y){
    if(key < GLUT_KEY_LEFT || key > GLUT_KEY_DOWN) return;
    pressed[key - GLUT_KEY_LEFT] = 1;
}   

void up(int key, int x, int y){
    if(key < GLUT_KEY_LEFT || key > GLUT_KEY_DOWN) return;
    pressed[key - GLUT_KEY_LEFT] = 0;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB);
    
    glutCreateWindow("Z-Buffer");
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glutInitWindowSize(WINDOW_W, WINDOW_H);
    glutInitWindowPosition(10, 10);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    // glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboard);
    glutSpecialUpFunc(up);


    glutMainLoop();
}
