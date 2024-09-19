// Quadrado.c - Isabel H. Manssour
// Um programa OpenGL simples que desenha um quadrado em uma janela GLUT.
// Este código está baseado no GLRect.c, exemplo disponível no livro
// "OpenGL SuperBible", 2nd Edition, de Richard S. e Wright Jr.
#include <GL/glut.h>
#include <stdio.h>
// Função callback chamada para fazer o desenho

int x1 = 300;
int Y1 = 50;
int x2 = 200;
int y2 = 200;

void Desenha(void)
{
    // Copia o valor de Y1 para evitar conflitos com a variável global
    int y1 = Y1;

    //Vamos rotacionar em relação ao centro do retangulo,
    //portanto nós levamos o Centro dele para a origem, por isso a media.
    double mediaX = (x1+x2)/2;
    double mediaY = (y1+y2)/2;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();  // Reseta a matriz de modelagem
    glClear(GL_COLOR_BUFFER_BIT);  // Limpa o buffer de cor



    // glScalef(1, 1, 1);
    // Translada o retângulo de volta para a sua posição original
    glTranslatef(mediaX, mediaY, 0.0f);

    // Aplica a rotação de 45 graus em torno do eixo Z
    glRotatef(45, 0, 0, 1);

    // Translada o retângulo para o centro da origem (para facilitar a rotação)
    glTranslatef(-mediaX, -mediaY, 0.0f);

    // Começa a desenhar o retângulo
    glBegin(GL_QUADS);

    // Desenha o retângulo com as cores desejadas
    glColor3f(1.0f, 0.0f, 0.0f);  // Vermelho
    glVertex2i(x1, y1);

    glVertex2i(x1, y2);

    glColor3f(0.0f, 0.0f, 1.0f);  // Azul
    glVertex2i(x2, y2);

    glVertex2i(x2, y1);

    glEnd();  // Termina o desenho
    
    //desenhando o centro do retangulo para comparacao da rotacao
    glPointSize(15);    
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);  // branco
    glVertex2i(mediaX, mediaY);
    glEnd();  // Termina o desenho

    glFlush();  // Força a execução do OpenGL
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
    printf("w = %d\n", w);
    printf("h = %d\n\n  ", h);

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

    int coiso = 250;
    if (w <= h)
        gluOrtho2D(0.0f, coiso, 0.0f, coiso * h / w);
    else
        gluOrtho2D(0.0f, coiso * w / h, 0.0f, coiso);
}

// Programa Principal
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 350);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Faz o L");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    Inicializa();

    glutMainLoop();


}

/*

--- AS TRANSFORMACOES SAO JOGADAS NUMA PILHA, OU SEJA, 
        A PRIMEIRA É A ULTIMA A SER UTILIZADA E A ULTIMA É A PRIMEIRA ----

Funcoes de transformacoes geometricas no openGL:

A translação é feita através da função glTranslatef(Tx, Ty, Tz), que pode receber três números
float ou double (glTranslated) como parâmetro. Neste caso, a matriz atual é multiplicada por uma
matriz de translação baseada nos valores dados.

A rotação é feita através da função glRotatef(Ângulo, x, y, z), que pode receber quatro números
float ou double (glRotated) como parâmetro. Neste caso, a matriz atual é multiplicada por uma
matriz de rotação de "Ângulo" graus ao redor do eixo definido pelo vetor "x,y,z" no sentido anti-
horário.

A escala é feita através da função glScalef(Ex, Ey, Ez), que pode receber três números float ou
double (glScaled) como parâmetro. Neste caso, a matriz atual é multiplicada por uma matriz de
escala baseada nos valores dados.

*/