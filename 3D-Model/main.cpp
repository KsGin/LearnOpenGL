// Include standard headers
#include <cstdio>

#define GLEW_STATIC
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

GLFWwindow *window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

// Include assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Model.h"

using namespace glm;

int WIDTH = 1024, HEIGHT = 768;
float FOV = 90.0f;


void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);


int main() {
    // Initialise GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(WIDTH, HEIGHT, "3D-MODEL", nullptr, nullptr);
    if (window == nullptr) {
        fprintf(stderr,
                "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //glViewport(0, 0, WIDTH, HEIGHT);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    glClearColor(0.2f,0.2f,0.2f,1.0f);

    Shader ourShader("../shader/model_loading.vs", "../shader/model_loading.fs");
    Model nanosuitModel("../obj/nanosuit.obj");

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));    // it's a bit too big for our scene, so scale it down

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSetScrollCallback(window, scroll_callback);

        ourShader.use();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(FOV), (float) WIDTH / (float) HEIGHT , 0.1f, 100.0f);
        glm::mat4 view = lookAt(
                vec3(0.0f, 0.0f, 3.0f),
                vec3(0.0f, 0.0f, 0.0f),
                vec3(0.0f, 1.0f, 0.0f)
        );
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // render the loaded model
        model = glm::rotate(model , radians(90.0f) / 60 , glm::vec3(0.0f,1.0f,0.0f));
        ourShader.setMat4("model", model);

        nanosuitModel.Darw(ourShader);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);

    return 0;
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    if ((FOV > 120.0 && yoffset > 0.0)
        || (FOV < 45.0 && yoffset < 0.0))
        return;
    FOV += yoffset;
}
