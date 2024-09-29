#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define N (int) 1e5 //limite de pontos
#define SIZE 1000 // tamanho da janela e da viewport

enum colors{
    BLUE = 0, RED, GREEN
};

typedef struct point{
    int x, y;
    int cor;
} Point;


Point points[N]; //vetor com os pontos dos segmentos de reta
int at = 0; //ponto atual

//cores primarias (Blue, Red, Green)
int cor_atual = 0;
GLfloat cores[3][3] = {{0, 0, 1}, {1, 0, 0}, {0, 1, 0}};

int h = SIZE, w = SIZE; //dimensoes da janela
GLfloat left = 0, right = SIZE, bottom = 0, top = SIZE; //dimensoes da janela de visualização

//desenha um unico ponto (x,y) na tela
void draw_pixel(int x, int y){
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
}

// algoritmo de Bresenham para desenhar uma linha entre os pontos A e B
void draw_line(Point a, Point b) {
    //coordenadas do pixel atual que estamos
    int x = a.x, y = a.y;

    //variacao de X e de Y
    int dx = b.x - a.x;
    int dy = b.y - a.y;

    //vendo o sinal da derivada, para ver se a variação é crescente ou decrescente
    //ex: ponto A à esquerda do ponto B: a variação de X é negativa, portanto X deve variar de modo decrescente
    int stepX = (dx > 0) ? 1 : -1; 
    int stepY = (dy > 0) ? 1 : -1;  
    
    dx *= stepX; // deixa as variacoes sempre positivas, ja que temos a informacao de crescimento (step)
    dy *= stepY; // deixa as variacoes sempre positivas, ja que temos a informacao de crescimento (step) 
            
    //erro acumulado no desenho da reta, ja que desenhamos apenas em pontos inteiros
    //padrao adotado: a variacao em X aumenta o erro, e a variacao em Y reduz o erro, assim erro = 0 é o ideal
    //a ser buscado, ou seja, se o erro tiver muito grande, move no Y, se tiver muito pequeno, move em X
    int erro = dx - dy;

    //loop que sai do ponto A ate chegar no ponto B, variando X e Y
    while (x != b.x || y != b.y) {
        // if(x > SIZE || y > SIZE) break;  
        //desenha o pixel atual na tela
        draw_pixel(x, y);
        
        //multiplicacao por 2 para garantir maior precisao do erro, nao precisando usar double
        int erro2 = 2 * erro; 
        
        //se o erro estiver OK para o eixo Y, movemos no eixo X e incrementamos o erro para o eixo Y (ou seja, subtrai dy)
        if (erro2 > -dy) {
            erro -= dy; //movemos em X, entao o erro em Y aumentou (erro diminui)
            x += stepX;
        }
        
        //se o erro estiver OK para o eixo X, movemos no eixo Y e incrementaos o erro para o eixo X (ou seja, somamos dx)
        if (erro2 < dx) {
            erro += dx; //movemos em Y, entao o erro em X aumentou (erro aumenta)
            y += stepY;
        }   
    }
    
    draw_pixel(b.x, b.y); //desenha o ponto B (final)
    
}

//percorre os pontos 2 a 2 e desenha uma reta entre eles. Se sobrar algum ponto, desenha ele como um pixel em branco
void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    for(int i = 0; i < at; i ++){
        glColor3fv(cores[points[i].cor]);

        if(i & 1) draw_line(points[i-1], points[i]);
    }

    if(at & 1){
        glColor3f(1.0, 1.0, 1.0);
        draw_pixel(points[at-1].x, points[at-1].y);
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
//click esquerdo: adiciona um novo ponto. Se a quantidade de pontos for par, forma uma nova reta 
//click direito: remove, se houver, o ultimo ponto q não faz parte de alguma reta
void handle_mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        y = h - y;
        points[at].x = x;
        points[at].y = y;
        points[at].cor = cor_atual;

        at++;

        display();
    }

    else if(button != GLUT_LEFT_BUTTON){
        if(at % 2 == 0) return;
        at--;
        glColor3f(0.0, 0.0, 0.0);
        draw_pixel(points[at].x, points[at].y);
        glutSwapBuffers();  
    }
}

//função que trata teclas normais do teclado, alternando se a tecla está ativa ou desativa
//se a tecla for o espaço, a cor da exibição do poligono é alterada.
void handle_keys(unsigned char key, int a, int b){
    if(key == ' '){
        cor_atual = (cor_atual + 1) % 3;
    }
    if(key == 'z'){
        if(at){
            if(at%2 == 1){
                glColor3f(0.0, 0.0, 0.0);
                draw_pixel(points[at-1].x, points[at-1].y);
                glutSwapBuffers();  
            }
            at -= (at % 2 == 0 ? 2 : 1);
            display();
        }
    }
}

int main(int argc, char** argv){
    //Inicialização do OpenGL, da janela principal e da janela de visualização
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(w, h); 
    glutCreateWindow("Tracado Otimizado de Retas");
    initialize();

    //Funções a serem chamadas durante a execução do programa
    glutMouseFunc(handle_mouse);
    glutKeyboardFunc(handle_keys);


    //Inicio do programa
    glutMainLoop();
    return 0;
}