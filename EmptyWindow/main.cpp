
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void InitGlfw(){
    /*初始化glfw*/
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 3); //设置最大版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR , 3); //设置最小版本
    glfwWindowHint(GLFW_OPENGL_PROFILE , GLFW_OPENGL_CORE_PROFILE); //设置core-profile
    glfwWindowHint(GLFW_RESIZABLE , false); //设置不可改变大小
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT , GL_TRUE);
#endif
}


void DisPlayColor(){

    static int r = 0;
    static int g = 128;
    static int b = 255;
    static int dr = 1;
    static int dg = 1;
    static int db = 1;


    glClearColor(r / 255.0f  , g / 255.0f , b / 255.0f  , 1.0f);

    r += dr;
    g += dg;
    b += db;
    if (r > 255 || r < 0) dr = -dr;
    if (g > 255 || g < 0) dg = -dg;
    if (b > 255 || b < 0) db = -db;

    glClear(GL_COLOR_BUFFER_BIT);
}

void key_callback(GLFWwindow* window , int key , int scancode , int action , int mode){
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window , GL_TRUE);
    }
}

int main()
{

    InitGlfw();

    //创建一个窗口
    GLFWwindow *window = glfwCreateWindow(800 , 600 , "Empty Window" , NULL , NULL);

    //设置窗口环境
    glfwMakeContextCurrent(window);

    if(window == NULL){
        std::cout << "Faild to create glfw window" << std::endl;
        glfwTerminate();
    }

    //设置glew
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        std::cout << "Faild to init glew" << std::endl;
        return -1;
    }

    //设置位置
    glViewport(100 , 100 , 800 , 600);

    glfwSetKeyCallback(window , key_callback);

    while (!glfwWindowShouldClose(window)){

        glfwPollEvents();

        DisPlayColor();



        glfwSwapBuffers(window);
    }

    return 0;
}