// Quadrado.c - Isabel H. Manssour
// Um programa OpenGL simples que desenha um quadrado em uma janela GLUT.
// Este código está baseado no GLRect.c, exemplo disponível no livro
// "OpenGL SuperBible", 2nd Edition, de Richard S. e Wright Jr.
#include <GL/glut.h>
#include <stdio.h>
// Função callback chamada para fazer o desenho

int x1 = 0;
int Y1 = 0;
int x2 = 150;
int y2 = 150;

void Desenha(void)
{
    int y1 = Y1;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    // glBegin(GL_QUADS);
    //     glVertex2i(x2, y2);
    //     glVertex2i(x1, y2);
    //     glVertex2i(x1, y1);
    //     glVertex2i(x2, y1);
    // glEnd();

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glTranslated(50, 50, 0);
    glutSolidTeapot(8);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Executa os comandos OpenGL
    glFlush();
}

// Inicializa parâmetros de rendering
void Inicializa(void)
{
    // Define a cor de fundo da janela de visualização como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Evita a divisao por zero

    if (h == 0)
        h = 1;
    // Especifica as dimensões da Viewport
    glViewport(0, 0, w, h);
    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Estabelece a janela de seleção (left, right, bottom, top)
    int l = x1;
    int r = x2;
    int b = 0;
    int up = y2;

    if (w <= h)
        gluOrtho2D(0.0f, 250.0f, 0.0f, 250.0f * h / w);
    else
        gluOrtho2D(0.0f, 250.0f * w / h, 0.0f, 250.0f);c=
}
// Programa Principal
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(400, 350);
    glutInitWindowPosition(10, 10);

    glutCreateWindow("Teste");

    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);

    Inicializa();

    glutMainLoop();
}