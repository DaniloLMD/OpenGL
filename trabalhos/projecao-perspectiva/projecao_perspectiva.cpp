#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define PI acos(-1)

// estrutura para representar pontos 3D
typedef struct Point {
    double x, y, z;
} Point;

// estrutura para representar o cubo
typedef struct Cubo {
    Point centro;
    double tamanho;
    Point vertices[8];

    Cubo(Point centro, double tamanho);
    void Draw();
    void Rotate(double angX, double angY, double angZ);
    Point vertices_rotacionados[8];
} Cubo;

const int SIZE = 700; // tamanho da tela

//variaveis de rotacao
GLdouble angX = 0, angY = 0, angZ = 0.0; 
const double rotate_change = 5;
//variaveis de translacao
GLfloat translateX = 0.0, translateY = 0.0, translateZ = 0.0;
GLfloat translate_change = 0.1;


//cores disponiveis
enum color_names {
    RED = 0, GREEN, BLUE, YELLOW, PURPLE, WHITE, GRAY, BROWN, CYAN 
};
GLfloat cores[][3] = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1},
    {1.0, 1.0, 0.0},
    {1.0, 0.0, 1.0},
    {1, 1, 1},
    {0.5, 0.5, 0.5},
    {0.6,0.3,0},
    {0, 1, 1}
};


//inicializa um cubo (construtor)
Cubo::Cubo(Point centro, double tamanho) : centro(centro) {
    double tam = tamanho / 2.0f;
    this->tamanho = tam;

    // Definição dos vértices
    vertices[0] = {centro.x - tam, centro.y - tam, centro.z - tam};
    vertices[1] = {centro.x + tam, centro.y - tam, centro.z - tam};
    vertices[2] = {centro.x + tam, centro.y + tam, centro.z - tam};
    vertices[3] = {centro.x - tam, centro.y + tam, centro.z - tam};
    vertices[4] = {centro.x - tam, centro.y - tam, centro.z + tam};
    vertices[5] = {centro.x + tam, centro.y - tam, centro.z + tam};
    vertices[6] = {centro.x + tam, centro.y + tam, centro.z + tam};
    vertices[7] = {centro.x - tam, centro.y + tam, centro.z + tam};
}

//projeta um ponto com perspectiva: calculamos um W diretamente proporcional à distancia do ponto
//ao plano em que será desenhado. Então, o ponto a ser desenhado será (x/w, y/w, z)
//Ou seja, os pontos mais longe do plano, terão coordenadas X e Y menores, gerando uma sensacao de distancia.
void perspectiveProjection(Point& p, double left, double right, double bottom, double top, double near, double far) {
    double w = 1.5 - p.z/2;
    p.x *= w;
    p.y *= w;
    // p.z *= w;
}


double rad(double ang) {
    return ang * PI /   180; 
}

void Cubo::Rotate(double angX, double angY, double angZ) {
    angX = rad(angX);
    angY = rad(angY);
    angZ = rad(angZ);


    double cosX = cos(angX);
    double sinX = sin(angX);

    double cosY = cos(angY);
    double sinY = sin(angY);

    double cosZ = cos(angZ);
    double sinZ = sin(angZ);


    for (int i = 0; i < 8; i++) {
        GLfloat x = vertices[i].x - centro.x;
        GLfloat y = vertices[i].y - centro.y;
        GLfloat z = vertices[i].z - centro.z;

        // Rotação em torno de X
        GLfloat tempY = y * cosX - z * sinX;
        GLfloat tempZ = y * sinX + z * cosX;
        y = tempY;
        z = tempZ;

        // Rotação em torno de Y
        GLfloat tempX = x * cosY + z * sinY;
        z = -x * sinY + z * cosY;
        x = tempX;

        // Rotação em torno de Z
        tempX = x * cosZ - y * sinZ;
        tempY = x * sinZ + y * cosZ;
        x = tempX;
        y = tempY;

        vertices_rotacionados[i].x = x + centro.x;
        vertices_rotacionados[i].y = y + centro.y;
        vertices_rotacionados[i].z = z + centro.z;
    }
}

// desenha o cubo
void Cubo::Draw() {
    Point transformed[8];

    Rotate(angX, angY, angZ);

    //aplica a projeção ortogonal
    for (int i = 0; i < 8; ++i) {
        transformed[i] = vertices_rotacionados[i];
        perspectiveProjection(transformed[i], -SIZE, SIZE, -SIZE, SIZE, -SIZE, SIZE);
    }

    //desenha as faces do cubo
    glBegin(GL_QUADS);

    glColor3fv(cores[RED]);
    glVertex3f(transformed[0].x, transformed[0].y, transformed[0].z);
    glVertex3f(transformed[1].x, transformed[1].y, transformed[1].z);
    glVertex3f(transformed[2].x, transformed[2].y, transformed[2].z);
    glVertex3f(transformed[3].x, transformed[3].y, transformed[3].z);

    glColor3fv(cores[GREEN]);
    glVertex3f(transformed[4].x, transformed[4].y, transformed[4].z);
    glVertex3f(transformed[5].x, transformed[5].y, transformed[5].z);
    glVertex3f(transformed[6].x, transformed[6].y, transformed[6].z);
    glVertex3f(transformed[7].x, transformed[7].y, transformed[7].z);

    glColor3fv(cores[BLUE]);
    glVertex3f(transformed[3].x, transformed[3].y, transformed[3].z);
    glVertex3f(transformed[2].x, transformed[2].y, transformed[2].z);
    glVertex3f(transformed[6].x, transformed[6].y, transformed[6].z);
    glVertex3f(transformed[7].x, transformed[7].y, transformed[7].z);

    glColor3fv(cores[YELLOW]);
    glVertex3f(transformed[0].x, transformed[0].y, transformed[0].z);
    glVertex3f(transformed[1].x, transformed[1].y, transformed[1].z);
    glVertex3f(transformed[5].x, transformed[5].y, transformed[5].z);
    glVertex3f(transformed[4].x, transformed[4].y, transformed[4].z);

    glColor3fv(cores[PURPLE]);
    glVertex3f(transformed[1].x, transformed[1].y, transformed[1].z);
    glVertex3f(transformed[2].x, transformed[2].y, transformed[2].z);
    glVertex3f(transformed[6].x, transformed[6].y, transformed[6].z);
    glVertex3f(transformed[5].x, transformed[5].y, transformed[5].z);

    glColor3fv(cores[CYAN]);
    glVertex3f(transformed[0].x, transformed[0].y, transformed[0].z);
    glVertex3f(transformed[3].x, transformed[3].y, transformed[3].z);
    glVertex3f(transformed[7].x, transformed[7].y, transformed[7].z);
    glVertex3f(transformed[4].x, transformed[4].y, transformed[4].z);

    glEnd();
}

void display(){
    //limpa a tela
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //rotaciona os pontos
    glLoadIdentity();

    glTranslatef(translateX, translateY, translateZ);

    //deseha um cubo
    Cubo cubo({0, 0, 0}, 0.8);
    cubo.Draw();

    glutSwapBuffers();
}

//inicializa a janela e o Z-Buffer para evitar sobrescrita de pontos
void initialize() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(SIZE, SIZE);
    glutCreateWindow("Projecao Perspectiva");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glOrtho(-1.3, 1.3, -1.3, 1.3, -1.3, 1.3);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}


//lida com as setinhas do teclado(para rotacionar)
void special_keyboard(int key, int x, int y) {
    if (key == GLUT_KEY_UP) angX += rotate_change;
    if (key == GLUT_KEY_DOWN) angX -= rotate_change;
    if (key == GLUT_KEY_LEFT) angY += rotate_change;
    if (key == GLUT_KEY_RIGHT) angY -= rotate_change;

    glutPostRedisplay();
}

int ok(double sumX, double sumY, double sumZ){
    double lim = 0.85;
    double limZ = 0.7;
    if(translateX + sumX >= lim) return 0;
    if(translateX + sumX <= -lim) return 0;

    if(translateY + sumY >= lim) return 0;
    if(translateY + sumY <= -lim) return 0;

    if(translateZ + sumZ >= limZ) return 0;
    if(translateZ + sumZ <= -limZ) return 0;

    return 1;
}

void keyboard(unsigned char key, int, int) {
    double sumX = 0, sumY = 0, sumZ = 0;
    if(key == 'w') {
        sumY += translate_change;
    }
    if(key == 's') {
        sumY -= translate_change;
    }
    if(key == 'a') {
        sumX -= translate_change;
    }
    if(key == 'd') {
        sumX += translate_change;
    }
    if(key == 'q') {
        sumZ -= translate_change;
    }
    if(key == 'e') {
        sumZ += translate_change;
    }

    if(key == 'x') {
        angZ += rotate_change;
    }
    if(key == 'z') {
        angZ -= rotate_change;
    }


    if(ok(sumX, sumY, sumZ)){
        translateX += sumX;
        translateY += sumY;
        translateZ += sumZ;
    }

    glutPostRedisplay();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);

    initialize();

    glutDisplayFunc(display);
    glutSpecialFunc(special_keyboard);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
