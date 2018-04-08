#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Headers/Shader.hpp"
#include "Headers/Camera.hpp"

using namespace std;
using namespace glm;

const int width = 800, height = 500;


void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);


int main() {
    if (!glfwInit()) {
        cout << "Init GLFW failed" << endl;
        glfwTerminate();
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    GLFWwindow *pWindow = glfwCreateWindow(width, height, "Advance Lighting", nullptr, nullptr);
    if (!pWindow) {
        cout << "Create window failed" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(pWindow);


    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cout << "Failed to init GLEW" << endl;
        return -1;
    }

    glfwSetKeyCallback(pWindow, KeyCallback);

    static const GLfloat vertices[] = {
            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f
    };

    unsigned int vertexArrayObject, vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, static_cast<void *>(0));
    glEnableVertexAttribArray(0);

    unsigned int uboBlock;
    glGenBuffers(1, &uboBlock);
    glBindBuffer(GL_UNIFORM_BUFFER, uboBlock);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, nullptr, GL_STATIC_DRAW); // 分配152字节的内存
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glEnable(GL_PROGRAM_POINT_SIZE);
    Shader glslShader("../Shaders/ModelVertexShader.glsl", "../Shaders/ModelFragmentShader.glsl");
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 1.0f));

    //bind 0
    const auto vpIndex = glGetUniformBlockIndex(glslShader.ID, "VP");
    glUniformBlockBinding(glslShader.ID, vpIndex, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboBlock);

    auto projection = glm::perspective(glm::radians(90.0f),(float)width / height, 0.1f, 100.0f);
    auto view = camera.GetViewMatrix();
    auto model = scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));

    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &projection);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &view);

    while (!glfwWindowShouldClose(pWindow)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glslShader.use();
        model = glm::rotate(model , radians(1.0f) , vec3(0.0f , 1.0f , 0.0f));
        glslShader.setMat4("model", model);
        glBindVertexArray(vertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(pWindow);
    }


    return 0;
}

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

}