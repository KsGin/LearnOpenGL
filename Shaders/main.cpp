#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <fstream>
#include <vector>


#define GLFW_CONTEXT_VERSION 3
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


using std::string;
using std::ifstream;

void InitGLFW() {
    if (!glfwInit()) {
        std::cerr << "init glfw error" << std::endl;
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_CONTEXT_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_CONTEXT_VERSION);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

/**
 * 从文件中读入shader代码
 * @param filePath
 * @return
 */
char *GLCodeFromFile(const string &filePath) {
    string ret;
    ifstream ifs(filePath);
    char buf[100];
    while (ifs.getline(buf, 100)) {
        ret += buf;
        ret += '\n';
    }
    return const_cast<char *>(ret.c_str());
}

/**
 * 创建着色器程序
 * @param vertexFilePath 顶点着色器文件
 * @param fragmentFilePath 片段着色器文件
 * @return 着色器程序
 */
GLuint CreateProgram(const string &vertexFilePath, const string &fragmentFilePath) {
    //获取Shader代码
    const GLchar *vertexShaderCode = GLCodeFromFile(vertexFilePath);
    const GLchar *fragmentShaderCode = GLCodeFromFile(fragmentFilePath);

    //获得Shader对象
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    GLint result = GL_FALSE;
    GLint logLength;
    //检查vertex shader编译情况
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
    if (!result) {
        std::vector<char> errorMessage(static_cast<unsigned long>(logLength + 1));
        glGetShaderInfoLog(vertexShader, logLength, nullptr, &errorMessage[0]);
        printf("%s\n", &errorMessage[0]);
    } else {
        printf("vertex shader complier successed\n");
    }
    //检查fragment shader编译情况
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);
    if (!result) {
        std::vector<char> errorMessage(static_cast<unsigned long>(logLength + 1));
        glGetShaderInfoLog(fragmentShader, logLength, nullptr, &errorMessage[0]);
        printf("%s\n", &errorMessage[0]);
    } else {
        printf("fragment shader complier successed\n");
    }

    GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glDetachShader(program, vertexShader);
    glDetachShader(program, vertexShader);

    //检查program编译情况
    glGetProgramiv(program, GL_COMPILE_STATUS, &result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    if (!result) {
        std::vector<char> errorMessage(static_cast<unsigned long>(logLength + 1));
        glGetShaderInfoLog(program, logLength, nullptr, &errorMessage[0]);
        printf("%s\n", &errorMessage[0]);
    } else {
        printf("program link successed\n");
    }

    //删除着色器
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}


int main() {

    InitGLFW();
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shader Window", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    if (window == nullptr) {
        std::cerr << "create window error" << std::endl;
        glfwTerminate();
        return -1;
    }

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "init glew error" << std::endl;
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glViewport(100, 100, SCREEN_WIDTH, SCREEN_HEIGHT);

    GLfloat vertices[] = {
            // 位置              // 颜色
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // 左下
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // 顶部
    };


    GLuint vertexArrayObject, vertexBufferObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glGenBuffers(1, &vertexBufferObject);

    //bind
    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(1,vertexBufferObject);
//    glBindVertexArray(0);
//    glDisableVertexAttribArray(0);
//    glDisableVertexAttribArray(1);

    GLuint program = CreateProgram("../VertexShader.vs", "../FragmentShader.vs");
    glUseProgram(program);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        glBindVertexArray(vertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);


        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBufferObject);
    glfwTerminate();

    return 0;
}
