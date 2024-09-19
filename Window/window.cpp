#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

int main(){
    glfwInit(); //inicializa o opengl

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //define a maior versão do opengl para 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //define a menor versão do opengl para 3

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //libera mais features
    

    //criando a window com 800x600
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); //coloca as informações da window como principal context da thread
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    


    std::cout << "rodou\n";

    return 0;
}