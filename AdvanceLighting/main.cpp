#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;

const int width = 800, height = 500;


void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);


int main() {
    if (!glfwInit()){
        cout << "Init GLFW failed" << endl;
        glfwTerminate();
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT , GLFW_TRUE);

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

    glViewport(0, 0, width, height);
    glfwSetKeyCallback(pWindow, KeyCallback);

    while (!glfwWindowShouldClose(pWindow)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 1.0f, 1.0f);

        glfwSwapBuffers(pWindow);
    }


    return 0;
}

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

}