#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

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
} Cubo;

const int SIZE = 800; // tamanho da tela

//variaveis de rotacao
GLdouble angX = 0, angY = 0, angZ = 0; 
const double rotate_change = 5;
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

    vertices[0] = {centro.x - tam, centro.y - tam, centro.z - tam};
    vertices[1] = {centro.x + tam, centro.y - tam, centro.z - tam};
    vertices[2] = {centro.x + tam, centro.y + tam, centro.z - tam};
    vertices[3] = {centro.x - tam, centro.y + tam, centro.z - tam};
    vertices[4] = {centro.x - tam, centro.y - tam, centro.z + tam};
    vertices[5] = {centro.x + tam, centro.y - tam, centro.z + tam};
    vertices[6] = {centro.x + tam, centro.y + tam, centro.z + tam};
    vertices[7] = {centro.x - tam, centro.y + tam, centro.z + tam};

}


//aplica a projecao perspectiva no ponto utilizando semelhanca de triangulo
void perspectiveProjection(Point& p) { 
    Point visao = {0,0,-1};
    double visao_z = visao.z; //coordenada Z do observador
    double plano_z = 1; //coordenada Z do plano a ser projetado

    double Zp = p.z - plano_z;
    double d = plano_z - visao_z;

    double dx = (p.x) / ((p.z/d) + 1);
    double dy = (p.y) / ((p.z/d) + 1);

    p.x = visao.x + dx;
    p.y = visao.y + dy;
}

// desenha o cubo
void Cubo::Draw() {
    Point transformed[8];

    //aplica a projeção perspectiva
    for (int i = 0; i < 8; ++i) {
        transformed[i] = vertices[i];
        transformed[i].x += translateX;
        transformed[i].y += translateY;
        transformed[i].z += translateZ;
        perspectiveProjection(transformed[i]);
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

    glLoadIdentity();

    //rotaciona os pontos
    glRotatef(angX, 1, 0, 0);
    glRotatef(angY, 0, 1, 0);
    glRotatef(angZ, 0, 0, 1);

    //deseha um cubo
    Cubo cubo({0, 0, 0}, 0.5);
    cubo.Draw();

    glutSwapBuffers();
}

//lida com as setinhas do teclado(para rotacionar)
void special_keyboard(int key, int x, int y) {
    if (key == GLUT_KEY_UP) angX += rotate_change;
    if (key == GLUT_KEY_DOWN) angX -= rotate_change;
    if (key == GLUT_KEY_LEFT) angY -= rotate_change;
    if (key == GLUT_KEY_RIGHT) angY += rotate_change;

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

//inicializa a janela e o Z-Buffer para evitar sobrescrita de pontos
void initialize() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(SIZE, SIZE);
    glutCreateWindow("Projecao Perspectiva");
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
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
