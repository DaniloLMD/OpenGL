#include <GL/glut.h>
#include <stdio.h>
#define SIZE 1000

// Função para desenhar um pixel na tela
void setPixel(int x, int y) {
    glBegin(GL_POINTS); 
    glVertex2i(x, y); 
    glEnd();
    glFlush();  // Força o OpenGL a renderizar o pixel
}

// Algoritmo de Bresenham para desenhar uma linha entre (x1, y1) e (x2, y2)
void bresenhamLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int x = x1, y = y1;

    int stepX = (dx > 0) ? 1 : -1;
    int stepY = (dy > 0) ? 1 : -1;
    
    dx = abs(dx);
    dy = abs(dy);
    
    int err = dx - dy;
    
    while (x != x2 || y != y2) {
        setPixel(x, y);
        
        int err2 = 2 * err;
        
        if (err2 > -dy) {
            err -= dy;
            x += stepX;
        }
        
        if (err2 < dx) {
            err += dx;
            y += stepY;
        }
    }
    setPixel(x2, y2); // Desenha o último ponto
}

// Função de exibição chamada pelo GLUT
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Limpa a tela
    // Defina dois pontos (x1, y1) e (x2, y2)
    int x1 = 29, y1 = 944;
    int x2 = 182, y2 = 936;
    bresenhamLine(x1, y1, x2, y2); // Desenha a linha usando Bresenham
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Cor de fundo branco
    glColor3f(1.0, 1.0, 1.0);         // Cor da linha preta
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, SIZE, 0, SIZE);        // Define a área de visualização
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(SIZE, SIZE);
    glutCreateWindow("Linha usando Bresenham");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
