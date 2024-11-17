#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define N (int) 1e5 //limite de circulos
#define SIZE 1000 // tamanho da janela e da viewport
#define PI acos(-1)

typedef char bool;
#define true 1
#define false 0

//cores disponiveis 
enum colors{
    BLUE = 0, RED, GREEN, WHITE
};

//estrutura que define um ponto, com suas coordenadas (X,Y) e sua cor
typedef struct point{
    int x, y;
    int cor;
} Point;

typedef struct circle{
    Point center;
    double rad;
    int cor;
    int filled;
} Circle;

Circle circles[N];
int at = 0; //ponto atual
double rad = 100;
double rad_change = 10;
bool filled = false;

//cores primarias (Blue, Red, Green) + White
int cor_atual = 0;
GLfloat cores[4][3] = {{0, 0, 1}, {1, 0, 0}, {0, 1, 0}, {1, 1, 1}};

int h = SIZE, w = SIZE; //dimensoes da janela
GLfloat left = -SIZE, right = SIZE, bottom = -SIZE, top = SIZE; //dimensoes da janela de visualização

//desenha um unico ponto (x,y) na tela
void draw_pixel(int x, int y){
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
}

//funcao que desenha os eixos de coordenadas, ou seja, as linhas Y = 0 e X = 0
void draw_eixos(){
    glColor3f(1.0, 1.0, 1.0);
    Point a = {left, 0};
    Point b = {right, 0};
    Point c = {0, bottom};
    Point d = {0, top};

    glBegin(GL_LINES);
        glVertex2i(left, 0);
        glVertex2i(right, 0);
        glVertex2i(0, bottom);
        glVertex2i(0, top);
    glEnd();

}

//desenha uma linha horizontal de (X1, Y) ate (X2, Y)
void draw_horizontal_line(int x1, int x2, int y) {
    // for (int x = x1; x <= x2; x++) {
    //     draw_pixel(x, y);
    // }
    glBegin(GL_LINES);
        glVertex2i(x1, y);
        glVertex2i(x2, y);
    glEnd();
}

//desenha os pontos da circunferencia por simetria e uma reta entre eles, assim o resultado final será um circulo preenchido.
void CirclePointsFilled(Circle c, int x, int y) {
    draw_horizontal_line(c.center.x - x, c.center.x + x, c.center.y + y); // Superior
    draw_horizontal_line(c.center.x - x, c.center.x + x, c.center.y - y); // Inferior
    draw_horizontal_line(c.center.x - y, c.center.x + y, c.center.y + x); // Lateral superior
    draw_horizontal_line(c.center.x - y, c.center.x + y, c.center.y - x); // Lateral inferior
}

//desenha os pontos da circunferencia por simetria e, se a circunferencia em questao for preenchida, chama a funcao CirclePointsFilled
void CirclePoints(Circle c, int x, int y) {
    if(c.filled){
        CirclePointsFilled(c, x, y);
        return;
    }
    draw_pixel(c.center.x + x, c.center.y + y);
    draw_pixel(c.center.x - x, c.center.y + y);
    draw_pixel(c.center.x + x, c.center.y - y);
    draw_pixel(c.center.x - x, c.center.y - y);
    draw_pixel(c.center.x + y, c.center.y + x);
    draw_pixel(c.center.x - y, c.center.y + x);
    draw_pixel(c.center.x + y, c.center.y - x);
    draw_pixel(c.center.x - y, c.center.y - x);
}

//desenha uma circunferencia utilizando a tecnica do ponto medio
void MidPointCircle(Circle c){
    int x, y;

    double d; //d = 0 : o ponto pertence a circunferencia, d < 0 : o ponto esta dentro da circunferencia, d > 0 : o ponto esta fora da circunferencia

    //para facilitar, consideramos o desenho estando na origem, depois realizamos a translação para o ponto desejado
    x = 0;
    y = c.rad;
    d = 5.0/4.0 - c.rad;

    glColor3fv(cores[c.cor]);
    CirclePoints(c, x,y);

    while(y >= x){
        //se o ponto estiver fora da circunferencia, escolher o ponto E 
        if(d < 0){
            d = d + 2 * x + 3;  
        }
        //se o ponto estiver dentro da circunferencia, escolher o ponto SE (se estiver exatamente na circunferencia, nao importa entre E ou SE)
        else{
            d = d + 2 * (x - y) + 5;
            y--;
        }
        x++;
        CirclePoints(c, x, y);
    }
}

//limpa a tela e desenha o que for preciso (eixos, circunferencias)
void display(){
    
    glClear(GL_COLOR_BUFFER_BIT);

    draw_eixos(); //desenha os eixos de coordenadas(X = 0 e Y = 0)

    for(int i = 0; i < at; i ++){
        MidPointCircle(circles[i]);
    }

    glutSwapBuffers(); //exibe as mudancas feitas na tela
}

//inicializa a cor de fundo e as dimensoes da janela de visualização
void initialize(void){
    glPointSize(2); //adotamos cada ponto como sendo de tamanho de 2 pixel para facilitar a visualizacao
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    gluOrtho2D(left, right, bottom, top);
}

//funcao que gerencia os eventos do mouse
//click esquerdo: desenha a circunferencia , click direito: muda o estado da proxima circunferencia para preenchida ou nao
void handle_mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        y = h - 2 * y;
        x = 2 * x - SIZE;
        circles[at].center.x = x;
        circles[at].center.y = y;
        circles[at].cor = cor_atual;
        circles[at].rad = rad;
        circles[at].filled = filled;

        at++;

        display();
    }

    else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        filled = !filled;
    }
}

//função que trata teclas normais do teclado
//se a tecla for o espaço, a cor da exibição da proxima circunferencia é alterada.
//se a tecla for 'z', remove a ultima circunferencia desenhada
//se a tecla for '+' ou '-', o raio da circunferencia a ser desenhada é aumentado/diminuido.
void handle_keys(unsigned char key, int a, int b){
    if(key == ' '){
        cor_atual = (cor_atual + 1) % 4;
    }
    if(key == 'z'){
        if(at){
            at--;
            display();
        }
    }
    if(key == '+'){
        if(rad < (right - left)/2 - 50) rad += rad_change;
    }
    if(key == '-'){
        if(rad > rad_change) rad -= rad_change;
    }
}

int main(int argc, char** argv){
    //Inicialização do OpenGL, da janela principal e da janela de visualização
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(w, h); 
    glutCreateWindow("Tracado de Circunferencia");
    initialize();

    //Funções a serem chamadas durante a execução do programa
    glutMouseFunc(handle_mouse);
    glutKeyboardFunc(handle_keys);

    display();

    //Inicio do programa
    glutMainLoop();
    return 0;
}
