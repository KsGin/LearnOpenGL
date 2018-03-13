// Include standard headers
#include <stdio.h>
#include <cstdlib>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

GLFWwindow *window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.hpp"

using namespace glm;

float FOV = 60.0f;


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


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
    window = glfwCreateWindow(1024, 768, "Tutorial 11 - Color", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr,
                "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.1f, 0.1f, 0.2f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);


    float vertices[] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
    };
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint cudeVAO;
    glGenVertexArrays(1, &cudeVAO);
    glBindVertexArray(cudeVAO);

    glVertexAttribPointer(
            0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            6 * sizeof(float),     // stride
            (void *) 0            // array buffer offset
    );
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            6 * sizeof(float),
            (void *) (3 * sizeof(float))
    );
    glEnableVertexAttribArray(1);


    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            6 * sizeof(float),
            (void *) 0);
    glEnableVertexAttribArray(0);

    GLuint cudeProgram = LoadShaders("../vertexShader.vs", "../fragmentShader.fs");
    GLuint lightProgram = LoadShaders("../lightVertexShader.vs", "../lightFragmentShader.fs");

    // Get a handle for our "MVP" uniform
    GLint lightProjectionID = glGetUniformLocation(lightProgram, "projection");
    GLint lightModelID = glGetUniformLocation(lightProgram, "model");
    GLint lightViewID = glGetUniformLocation(lightProgram, "view");
    GLint cudeProjectionID = glGetUniformLocation(cudeProgram,"projection");
    GLint cudeModelID = glGetUniformLocation(cudeProgram, "model");
    GLint cudeViewID = glGetUniformLocation(cudeProgram, "view");

    // Camera matrix
    glm::mat4 View = glm::lookAt(
            glm::vec3(4, 5, 3), // Camera is at (4,3,3), in World Space
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 cudeModel = glm::mat4(1.0f) *
                          glm::scale(glm::mat4(1.0f), vec3(0.6f, 0.7f, 1.7f));
    glm::mat4 lightModel = glm::mat4(1.0f) *
                           glm::translate(glm::mat4(1.0f), vec3(0.0f, 1.0f, 0.0f)) *
                           glm::scale(glm::mat4(1.0f), vec3(0.1f, 0.1f, 0.1f));

    float prex = 0.0f, prey = 1.0f, prez = 0.0f;
    do {

        glfwSetScrollCallback(window , scroll_callback);
        glm::mat4 Projection = glm::perspective(glm::radians(FOV), 4.0f / 3.0f, 0.1f, 100.0f);
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float x = static_cast<float>(cos(glfwGetTime()) / 2),
                y = 1.0f,
                z = static_cast<float>(sin(glfwGetTime()) / 2);
        glUseProgram(cudeProgram);
        cudeModel = cudeModel * glm::rotate(glm::mat4(1.0f),
                                            glm::radians(10.0f) / 100,
                                            glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(cudeViewID, 1, GL_FALSE, &View[0][0]);
        glUniformMatrix4fv(cudeModelID, 1, GL_FALSE, &cudeModel[0][0]);
        glUniformMatrix4fv(cudeProjectionID, 1, GL_FALSE, &Projection[0][0]);
        glUniform3f(glGetUniformLocation(cudeProgram, "viewPos"), 4.0f, 5.0f, 3.0f);
        glUniform3f(glGetUniformLocation(cudeProgram, "lightPos"), x, y, z);
        glUniform3f(glGetUniformLocation(cudeProgram, "objectColor"), 1.0f, 0.5f, 0.31f);
        glUniform3f(glGetUniformLocation(cudeProgram, "lightColor"), 1.0f, 1.0f, 1.0f);
        glBindVertexArray(cudeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);


        glUseProgram(lightProgram);
        lightModel = lightModel * glm::translate(glm::mat4(1.0f), vec3((x - prex) * 60, y - prey, (z - prez) * 60));
        glUniformMatrix4fv(lightProjectionID, 1, GL_FALSE, &Projection[0][0]);
        glUniformMatrix4fv(lightViewID, 1, GL_FALSE, &View[0][0]);
        glUniformMatrix4fv(lightModelID, 1, GL_FALSE, &lightModel[0][0]);
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        prex = x;
        prey = y;
        prez = z;

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);

    return 0;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if(FOV > 120.0 && yoffset > 0
       || FOV < 45.0 && yoffset < 0)
        return;
    FOV += yoffset;
}