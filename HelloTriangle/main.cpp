#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#define GLFW_CONTEXT_VERSION 3
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void InitGLFW(){
    /*初始化GLFW*/
    glfwInit();
    glfwWindowHint(GLFW_SAMPLES , 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_CONTEXT_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_CONTEXT_VERSION);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}


GLuint getProgram() {

    GLchar const* vertexShaderSource =
            "#version 330 core\n"
                    "layout(location = 0) in vec3 position;\n"
                    "void main(){\n"
                    "   gl_Position = vec4(position.x,position.y,position.z,1.0);\n"
                    "}\n";


    GLchar const* fragmentShaderSource =
            "#version 330 core\n"
                    "out vec3 fragmentColor;\n"
                    "uniform vec3 color;\n"
                    "void main(){\n"
                    "   fragmentColor = color;\n"
                    "}\n";
    //创建缓冲器
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    //获得缓冲器对象
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glShaderSource(fragmentShader , 1 , &fragmentShaderSource , NULL);

    //编译缓冲器
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    //检查着色器

    GLint Result = GL_FALSE;
    GLint InfoLogLength;

    glGetShaderiv(vertexShader , GL_COMPILE_STATUS , &Result);
    glGetShaderiv(vertexShader , GL_INFO_LOG_LENGTH , &InfoLogLength);
    if(InfoLogLength > 0){
        std::vector<char> ShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(vertexShader, InfoLogLength, NULL, &ShaderErrorMessage[0]);
        printf("%s\n", &ShaderErrorMessage[0]);
    } else {
        printf("VertexShader complier successed\n");
    }

    glGetShaderiv(fragmentShader , GL_COMPILE_STATUS , &Result);
    glGetShaderiv(fragmentShader , GL_INFO_LOG_LENGTH , &InfoLogLength);
    if(InfoLogLength > 0){
        std::vector<char> ShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(fragmentShader, InfoLogLength, NULL, &ShaderErrorMessage[0]);
        printf("%s\n", &ShaderErrorMessage[0]);
    } else {
        printf("FragmentShader complier successed\n");
    }

    //连接程序
    GLuint program = glCreateProgram();
    glAttachShader(program , vertexShader);
    glAttachShader(program , fragmentShader);
    glLinkProgram(program);

    //
    glDetachShader(program , vertexShader);
    glDetachShader(program , fragmentShader);


    //检查program

    glGetProgramiv(program, GL_LINK_STATUS, &Result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    } else {
        printf("Link successed!\n");
    }

    //删除着色器
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}


glm::vec3 getRGB(){

    static int r = 0;
    static int g = 128;
    static int b = 255;
    static int dr = 1;
    static int dg = 1;
    static int db = 1;

    r += dr;
    g += dg;
    b += db;
    if (r > 255 || r < 0) dr = -dr;
    if (g > 255 || g < 0) dg = -dg;
    if (b > 255 || b < 0) db = -db;

    return glm::vec3(r , g , b);
}

int main() {

    InitGLFW();

    /*创建一个窗口对象*/
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Triangle", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (!window) {
        std::cout << "faild create glfw window" << std::endl;
        return -1;
    }

    /*设置GLEW*/
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "faild to init glew" << std::endl;
        return -2;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    GLuint program = getProgram();


    /*顶点坐标*/
    GLfloat vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f,
    };

    GLuint VBO;
    GLuint VAO;
    glGenVertexArrays(1 , &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer( 0 , 3 , GL_FLOAT , GL_FALSE , 0 , (void*)0);

    glEnableVertexAttribArray(0);
    glBindBuffer(1,VBO);
//    glBindVertexArray(0);
//    glDisableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.0f , 0.3f , 0.2f , 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::vec3 v = getRGB();
        int location = glGetUniformLocation(program , "color");
        glUseProgram(program);
        glUniform3f(location , v.r / 255.0f , v.g / 255.0f , v.b / 255.0f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES , 0 , 3);
        glBindVertexArray(0);


        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteProgram(program);
    glfwTerminate();
    return 0;
}

