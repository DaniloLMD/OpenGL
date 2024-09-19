#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define PI acos(-1) //define a constante pi
#define N_VERTICES 4 //numeros de vertices

GLfloat left = -1.0, right = 1.0, bottom = -1.0, top = 1.0; //dimensoes da janela de visualização
int h = 800, w = 800; //dimensoes da janela

//vertices a serem desenhados (do jeito que ta forma um quadrado)
GLfloat vertices[N_VERTICES][2] = {{-0.25, 0.25}, {0.25, 0.25}, {0.25, -0.25}, {-0.25, -0.25}};

//cores primarias (Blue, Red, Green)
int cor_atual = 0;
GLfloat cores[3][3] = {{0, 0, 1}, {1, 0, 0}, {0, 1, 0}};

//função que recebe um angulo em graus e retorna o mesmo em radianos
double rad(double ang){
    return ang * PI / 180;
}

//função que recebe um conjunto de pontos e os tansladam (x,y)
void translate(GLfloat v[][2], int size, GLfloat x, GLfloat y){
    for(int i = 0; i < size; i++){
        v[i][0] += x;
        v[i][1] += y;
    }
}

//função que calcula o ponto central de um conjunto de pontos
void center(GLfloat c[2], GLfloat v[][2], int size){
    c[0] = c[1] = 0;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < 2; j++)
            c[j] += v[i][j]/size;
    }
}

//função que recebe um conjunto de pontos e os rotaciona em ang graus 
void rotate(GLfloat v[][2], int size, double ang){
    ang = rad(ang);
    GLfloat c[2] = {0, 0};
    center(c, v, size);

    for(int i = 0; i < size; i++){
        GLfloat x = v[i][0] - c[0];
        GLfloat y = v[i][1] - c[1];
        v[i][0] = x * cos(ang) - y * sin(ang) + c[0];
        v[i][1] = x * sin(ang) + y * cos(ang) + c[1];
    }
}

//funcao que desenha os vertices na tela, formando um poligono definido por eles
void draw(void){
    glClear(GL_COLOR_BUFFER_BIT);

    // glColor3f(0.0f, 0.0f, 1.0f); //define a cor a ser desenhada como azul
    glColor3fv(cores[cor_atual]);

    glBegin(GL_POLYGON);
        for(int i = 0; i < N_VERTICES; i++){
            glVertex2fv(vertices[i]);
        }
    glEnd();

    glutSwapBuffers();
}

//inicializa a cor de fundo e as dimensoes da janela de visualização
void initialize(void){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    gluOrtho2D(left, right, bottom, top);
}

//função que trata teclas especiais (sem representação ASCII)
//seta para esquerda/direita: rotaciona o conjunto de vértices em relação ao centro deles
int rotation_state = 0;
void handle_special_keys(int key, int x, int y){
    if(key == GLUT_KEY_RIGHT){
        rotation_state = -1;
    }
    else if(key == GLUT_KEY_LEFT){
        rotation_state = 1;
    }
    else{
        rotation_state = 0;
        return;
    }
}
//funcao que trata quando uma tecla especial não está mais sendo apertada, fazendo o poligono
//parar de ser rotacionado
void handle_special_up_keys(int key, int x, int y){
    rotation_state = 0;
}

//função que trata teclas normais do teclado, alternando se a tecla está ativa ou desativa
//se a tecla for o espaço, a cor da exibição do poligono é alterada.
char keys[256];
void handle_keys(unsigned char key, int a, int b){
    keys[key] = !keys[key];
    if(key == ' '){
        cor_atual = (cor_atual + 1) % 3;
    }
}

//função que trata quando as teclas normais do teclado param de ser pressionadas, servindo
//para parar a translação do poligono quando as teclas ASWD não estiverem mais ativas.
void handle_up_keys(unsigned char key, int a, int b){
    if(key < 'a' || key > 'z') return;
    keys[key] = !keys[key];
}

//função para tratar a translação do poligono
//teclas ADWS ativas: translada o conjunto de vértices
//essa funcao nao deixa o centro do poligono formado sair da tela
void handle_translation(){
    GLfloat x = 0.0, y = 0.0;
    GLfloat change = 0.06;
    if(keys['w']){
        y += change;
    }
    if(keys['s']){
        y -= change;
    }
    if(keys['a']){
        x -= change;
    }
    if(keys['d']){
        x += change;
    }

    GLfloat c[2];
    center(c, vertices, N_VERTICES); 

    if(x != 0.0 && (c[0] + x <= left || c[0] + x >= right)) x = 0;
    if(y != 0.0 && (c[1] + y <= bottom || c[1] + y >= top)) y = 0;

    translate(vertices, N_VERTICES, x, y);
}

//função para tratar a rotação do poligono
void handle_rotate(){
    double change = 2;
    double a = 0;

    a = change * (rotation_state);

    rotate(vertices, N_VERTICES, a);
}

//função para tratar a escala do poligono
void handle_scale(){
    GLfloat zoom = 1.1;
    int ok = 0;
    if(keys['-']){ 
        for(int i = 0; i < N_VERTICES; i++){
            for(int j = 0; j < 2; j++){
                vertices[i][j] /= zoom;
            }
        }
        keys['-'] = 0;
    }
    if(keys['+']){
        for(int i = 0; i < N_VERTICES; i++){
            for(int j = 0; j < 2; j++){
                vertices[i][j] *= zoom;
            }
        }

        keys['+'] = 0;
    }
}

//se o poligono saiu da tela, ele é transladado de volta para o centro.
void centralize(){
    GLfloat centro[2];
    center(centro, vertices, N_VERTICES);

    if((centro[0] < left || centro[0] > right) || (centro[1] < bottom || centro[1] > top)){
        translate(vertices, N_VERTICES, -centro[0], -centro[1]);
        draw();
    }
}

//função responsável por atualizar o polígono, chamando as funções de escala, translação e rotação
void animate(){
    handle_scale();
    handle_translation();
    handle_rotate();

    centralize();

    draw();
}

int main(int argc, char** argv){
    //Inicialização do OpenGL, da janela principal e da janela de visualização
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(w, h); 
    glutCreateWindow("Transformacoes Geometricas");
    initialize();

    //Funções a serem chamadas durante a execução do programa
    glutDisplayFunc(draw);
    glutIgnoreKeyRepeat(1);
    glutSpecialFunc(handle_special_keys);
    glutSpecialUpFunc(handle_special_up_keys);
    glutKeyboardFunc(handle_keys);
    glutKeyboardUpFunc(handle_up_keys);
    glutIdleFunc(animate);

    //Inicio do programa
    glutMainLoop();
    return 0;
}