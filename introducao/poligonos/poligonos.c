// Quadrado.c - Isabel H. Manssour
// Um programa OpenGL simples que desenha um quadrado em uma janela GLUT.
// Este código está baseado no GLRect.c, exemplo disponível no livro
// "OpenGL SuperBible", 2nd Edition, de Richard S. e Wright Jr.
#include <GL/glut.h>
#include <stdio.h>
// Função callback chamada para fazer o desenho

int x1 = 50;
int Y1 = 50;
int x2 = 200;
int y2 = 200;

void Desenha(void)
{
    int y1 = Y1;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Limpa a janela de visualização com a cor de fundo especificada
    glClear(GL_COLOR_BUFFER_BIT);
    // Especifica que a cor corrente é vermelha
    // R G B
    // glColor3f(1.0f, 0.0f, 0.0f);
    // Desenha um quadrado preenchido com a cor corrente

    //TEM QUE PASSAR OS PONTOS SEGUINDO UMA ORDEM COERENTE. EX: SEMPRE HORARIO OU SEMPRE ANTI-HORARIO.
    glPointSize(10);
    glLineWidth(4);


    glBegin(GL_POINTS);

        glColor3f(0.0f, 0.0f, 1.0f); // B
        glVertex2i(x1, y2);
        
        glColor3f(0.0f, 1.0f, 0.0f); // G
        glVertex2i(x2, y1);
        

        glColor3f(0.5f, 0.5f, 0.5f); // GREY
        glVertex2i(x2, y2); 

        glColor3f(1.0f, 0.0f, 0.0f); // R
        glVertex2i(x1, y1);


    glEnd();

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


    if (w <= h)
        gluOrtho2D(0.0f, 250.0f, 0.0f, 250.0f * h / w);
    else
        gluOrtho2D(0.0f, 250.0f * w / h, 0.0f, 250.0f);
}
// Programa Principal
int main(int argc, char** argv)
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





// Para desenhar outras primitivas, basta trocar GL_POINTS, que exibe um ponto para cada chamada
// ao comando glVertex, por [1]:
// • GL_LINES: exibe uma linha a cada dois comandos glVertex;
// • GL_LINE_STRIP: exibe uma seqüência de linhas conectando os pontos definidos por
// glVertex;
// • GL_LINE_LOOP: exibe uma seqüência de linhas conectando os pontos definidos por
// glVertex e ao final liga o primeiro como último ponto;
// • GL_POLYGON: exibe um polígono convexo preenchido, definido por uma seqüência de
// chamadas a glVertex;
// • GL_TRIANGLES: exibe um triângulo preenchido a cada três pontos definidos por
// glVertex;
// • GL_TRIANGLE_STRIP: exibe uma seqüência de triângulos baseados no trio de vértices
// v0, v1, v2, depois, v2, v1, v3, depois, v2, v3, v4 e assim por diante;
// • GL_TRIANGLE_FAN: exibe uma seqüência de triângulos conectados baseados no trio de
// vértices v0, v1, v2, depois, v0, v2, v3, depois, v0, v3, v4 e assim por diante;
// • GL_QUADS: exibe um quadrado preenchido conectando cada quatro pontos definidos por
// glVertex;
// • GL_QUAD_STRIP: exibe uma seqüência de quadriláteros conectados a cada quatro
// vértices; primeiro v0, v1, v3, v2, depois, v2, v3, v5, v4, depois, v4, v5, v7, v6, e assim por
// diante.