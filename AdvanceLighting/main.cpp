#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Headers/Shader.hpp"
#include "Headers/Camera.hpp"
#include "Headers/Texture.hpp"
#include "Headers/Model.hpp"

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

    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_PROGRAM_POINT_SIZE);

    auto glslShader = Shader("../Shaders/ModelVertexShader.glsl", "../Shaders/ModelFragmentShader.glsl");
    auto glslTex = Texture("../Resources/tex.tga" , false);
    auto camera = Camera(glm::vec3(0.0f, 0.0f, 1.0f));
    auto cube = Model("../Resources/cube.txt");
    auto projection = glm::perspective(glm::radians(90.0f),(float)width / height, 0.1f, 100.0f);
    auto view = camera.GetViewMatrix();
    auto model = scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.3f, 0.3f));

    unsigned int uboBlock;
    glGenBuffers(1, &uboBlock);
    glBindBuffer(GL_UNIFORM_BUFFER, uboBlock);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, nullptr, GL_STATIC_DRAW); // 分配152字节的内存
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    const auto vpIndex = glGetUniformBlockIndex(glslShader.ID, "VP");
    glUniformBlockBinding(glslShader.ID, vpIndex, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboBlock);

    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &projection);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &view);

    while (!glfwWindowShouldClose(pWindow)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glslShader.use();
        glslTex.Use();
        model = glm::rotate(model , radians(1.0f) , vec3(0.0f , 1.0f , 0.0f));
        glslShader.setMat4("model", model);
        cube.Use();
        //glDrawArrays(GL_TRIANGLES , 0 , 36);
        glDrawElements(GL_TRIANGLES , cube.IndexCount() , GL_UNSIGNED_INT , 0);

        glfwSwapBuffers(pWindow);
    }


    return 0;
}

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}