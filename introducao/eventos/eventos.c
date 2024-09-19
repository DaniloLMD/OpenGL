// Interacao.c - Isabel H. Manssour
// Um programa OpenGL simples que desenha um quadrado em
// uma janela GLUT de acordo com interações do usuário.
// Este código está baseado nos exemplos disponíveis no livro
// "OpenGL SuperBible", 2nd Edition, de Richard S. e Wright Jr.
#include <GL/glut.h>
#include <stdio.h>

GLfloat xf, yf, win;
GLint view_w, view_h;
// Função callback chamada para fazer o desenho
void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    // Desenha um retângulo preenchido com a cor corrente
    glBegin(GL_POLYGON);

    glVertex2f(0.0f, 0.0f);
    glVertex2f(xf, 0.0f);
    glVertex2f(xf, yf);
    glVertex2f(0.0f, yf);

    glEnd();
    glFlush();
}
// Inicializa parâmetros de rendering
void Inicializa(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    xf = 50.0f;
    yf = 50.0f;
    win = 250.0f;
}
// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Especifica as dimensões da Viewport
    glViewport(0, 0, w, h);
    view_w = w;
    view_h = h;

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-win, win, -win, win);
    gluOrtho2D(0, 0, 0, 0);
}
// Função callback chamada para gerenciar eventos de teclado
void GerenciaTeclado(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'R':
    case 'r': // muda a cor corrente para vermelho
        glColor3f(1.0f, 0.0f, 0.0f);
        break;
    case 'G':
    case 'g': // muda a cor corrente para verde
        glColor3f(0.0f, 1.0f, 0.0f);
        break;
    case 'B':
    case 'b': // muda a cor corrente para azul
        glColor3f(0.0f, 0.0f, 1.0f);
        break;
    }
    glutPostRedisplay();
}
// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN)
        {
            // Troca o tamanho do retângulo, que vai do centro da
            // janela até a posição onde o usuário clicou com o mouse
            xf = ((2 * win * x) / view_w) - win;
            yf = (((2 * win) * (y - view_h)) / -view_h) - win;
        }
    glutPostRedisplay();
}
// Função callback chamada para gerenciar eventos do teclado
// para teclas especiais, tais como F1, PgDn e Home
void TeclasEspeciais(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        win -= 20;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(-win, win, -win, win);
    }
    if (key == GLUT_KEY_DOWN)
    {
        win += 20;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(-win, win, -win, win);
    }
    glutPostRedisplay();
}
// Programa Principal
int main(int argc, char** argv)
{   
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(350, 300);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Exemplo de Interacao");

    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);

    glutKeyboardFunc(GerenciaTeclado);
    glutMouseFunc(GerenciaMouse);
    glutSpecialFunc(TeclasEspeciais);
    
    Inicializa();
    glutMainLoop();
}

/*

• glutKeyboardFunc - Estabelece a função callback que é chamada pela GLUT cada vez
que uma tecla que gera código ASCII é pressionada (por exemplo: a, b, A, b, 1, 2). Além
do valor ASCII da tecla, a posição (x,y) do mouse quando a tecla foi pressionada também
é retornada. Parâmetros de entrada da função callback: (unsigned char key, int x, int y)

• glutSpecialFunc - Estabelece a função callback que é chamada pela GLUT cada vez que
uma tecla que gera código não-ASCII é pressionada, tais como Home, End, PgUp, PgDn,
F1 e F2. Além da constante que identifica a tecla, a posição corrente (x,y) do mouse
quando a tecla foi pressionada também é retornada. Parâmetros de entrada da função
callback: (unsigned char key, int x, int y). Os valores válidos para o primeiro parâmetro
são: GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4,
GLUT_KEY_F5, GLUT_KEY_F6, GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9,
GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, GLUT_KEY_LEFT,
GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_HOME,
GLUT_KEY_END, GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN,
GLUT_KEY_INSERT.

• glutMouseFunc - Estabelece a função callback que é chamada pela GLUT cada vez que
ocorre um evento de mouse. Parâmetros de entrada da função callback: (int button, int
state, int x, int y). Três valores são válidos para o parâmetro button:
GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON e GLUT_RIGHT_BUTTON. O
parâmetro state pode ser GLUT_UP ou GLUT_DOWN. Os parâmetros x e y indicam a
localização do mouse no momento que o evento ocorreu.

*/