#include <GL/glut.h>
#include <stdio.h>

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
GLdouble angX = 0, angY = 0; 
const double rotate_change = 5;

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

/* projecao ortogonal manual: transformamos as coordenadas do ponto para o intervalo [0, -1]
1 passo: subtraimos o centro da tela no ponto
X' = X - (right+left)/2;

2 passo: normalizar o valor, dividir o resultado pelo tamanho total
X'' = X' / ((right - left) / 2),    substituindo X':
X'' = ((X - (right+left))/2) / ((right - left)/2), multiplicando por 2 o denominador e o numerador:
X'' = (2X - (right+left)) / (right - left)

Portanto, o objetivo é centralizar o ponto dentro da área de visualização limitada por left->right, bottom->top e near->far
*/
void orthogonalProjection(Point& p, double left, double right, double bottom, double top, double near, double far) {
    p.x = (2.0f * p.x - (right + left)) / (right - left);
    p.y = (2.0f * p.y - (top + bottom)) / (top - bottom);
    p.z = (2.0f * p.z - (far + near)) / (far - near);
}

// desenha o cubo
void Cubo::Draw() {
    Point transformed[8];

    //aplica a projeção ortogonal
    for (int i = 0; i < 8; ++i) {
        transformed[i] = vertices[i];
        orthogonalProjection(transformed[i], -SIZE, SIZE, -SIZE, SIZE, -SIZE, SIZE);
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
    glRotatef(angX, 1, 0, 0);
    glRotatef(angY, 0, 1, 0);

    //deseha um cubo
    Cubo cubo({0, 0, 0}, 300);
    cubo.Draw();

    glutSwapBuffers();
}

//lida com as setinhas do teclado(para rotacionar)
void special_keyboard(int key, int x, int y) {
    if (key == GLUT_KEY_UP) angX += rotate_change;
    if (key == GLUT_KEY_DOWN) angX -= rotate_change;
    if (key == GLUT_KEY_LEFT) angY += rotate_change;
    if (key == GLUT_KEY_RIGHT) angY -= rotate_change;

    glutPostRedisplay();
}

//inicializa a janela e o Z-Buffer para evitar sobrescrita de pontos
void initialize() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(SIZE, SIZE);
    glutCreateWindow("Projecao Ortogonal");
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    initialize();

    glutDisplayFunc(display);
    glutSpecialFunc(special_keyboard);

    glutMainLoop();
    return 0;
}
