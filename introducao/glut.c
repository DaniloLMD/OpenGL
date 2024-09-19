// PrimeiroPrograma.c - Isabel H. Manssour
// Um programa OpenGL simples que abre uma janela GLUT
// Este código está baseado no Simple.c, exemplo disponível no livro
// "OpenGL SuperBible", 2nd Edition, de Richard S. e Wright Jr.
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função callback chamada para fazer o desenho
void Desenha()
{   
    // printf("oi!\n");
    // Limpa a janela de visualização com a cor de fundo especificada
    glClear(GL_COLOR_BUFFER_BIT);

    float r = (rand() % 10) / 10.0;
    float g = (rand() % 10) / 10.0;
    float b = (rand() % 10) / 10.0;

    // printf("r = %.1f\n", r);
    // printf("g = %.1f\n", g);
    // printf("b = %.1f\n", b);
    glClearColor(r, g, b, 1.0f);
    

    // Executa os comandos OpenGL
    glFlush();
}

void teste(unsigned char a, int b, int c){
    Desenha();
    printf("%c",a);
    if(a == 13) printf("\n");
    fflush(stdout);
}

// Inicializa parâmetros de rendering
void Inicializa(void)
{
    // Define a cor de fundo da janela de visualização como preta
}
// Programa Principal
int main(int argc, char** argv)
{
    srand(time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Primeiro Programa");
    glutDisplayFunc(Desenha);
    Inicializa();
    glutKeyboardFunc(teste);
    glutMainLoop();

    return 0;
}