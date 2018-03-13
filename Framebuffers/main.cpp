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
#include <iostream>
#include "shader.hpp"

#define WIDTH 1024
#define HEIGHT 768

using namespace glm;

float FOV = 60.0f;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

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
    window = glfwCreateWindow(WIDTH, HEIGHT, "Frame buffer", NULL, NULL);
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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glViewport(0, 0, WIDTH, HEIGHT);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    float screenVertices[] = {

            -1.0f, 1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 0.0f,

            -1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f
    };

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


    GLuint screenVBO;
    glGenBuffers(1, &screenVBO);
    glBindBuffer(GL_ARRAY_BUFFER, screenVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(screenVertices), screenVertices, GL_STATIC_DRAW);
    GLuint screenVAO;
    glGenVertexArrays(1, &screenVAO);
    glBindVertexArray(screenVAO);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) (2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    GLuint cudeVAO;
    glGenVertexArrays(1, &cudeVAO);
    glBindVertexArray(cudeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    //创建帧缓冲并绑定
    GLuint FBO;
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    GLuint RBO;
    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

    if (glCheckFramebufferStatus(FBO) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "FRAME::BUFFER::ERROR" << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    GLuint cudeProgram = LoadShaders("../vertexShader.vs", "../fragmentShader.fs");
    GLuint lightProgram = LoadShaders("../lightVertexShader.vs", "../lightFragmentShader.fs");
    GLuint screenProgram = LoadShaders("../screenVertexShader.vs", "../screenFragmentShader.fs");

    glm::mat4 Projection = glm::perspective(glm::radians(FOV), 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 View = glm::lookAt(glm::vec3(4, 5, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 cudeModel = glm::mat4(1.0f) *
                          glm::scale(glm::mat4(1.0f), vec3(2.0f, 0.5f, 2.0f));
    glm::mat4 lightModel = glm::mat4(1.0f) *
                           glm::translate(glm::mat4(1.0f), vec3(0.0f, 1.0f, 0.0f)) *
                           glm::scale(glm::mat4(1.0f), vec3(0.1f, 0.1f, 0.1f));
    do {

        glBindFramebuffer(GL_FRAMEBUFFER, FBO);  //以下内容绘制在自定义的帧缓冲里

        glEnable(GL_DEPTH_TEST);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(cudeProgram);
        glUniformMatrix4fv(glGetUniformLocation(cudeProgram, "view"), 1, GL_FALSE, &View[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(cudeProgram, "model"), 1, GL_FALSE, &cudeModel[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(cudeProgram, "projection"), 1, GL_FALSE, &Projection[0][0]);
        glUniform3f(glGetUniformLocation(cudeProgram, "viewPos"), 4.0f, 5.0f, 3.0f);
        glUniform3f(glGetUniformLocation(cudeProgram, "lightPos"), 0.0f, 1.0f, 0.0f);
        glUniform3f(glGetUniformLocation(cudeProgram, "objectColor"), 1.0f, 0.5f, 0.31f);
        glUniform3f(glGetUniformLocation(cudeProgram, "lightColor"), 1.0f, 1.0f, 1.0f);
        glBindVertexArray(cudeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        glUseProgram(lightProgram);
        glUniformMatrix4fv(glGetUniformLocation(lightProgram, "projection"), 1, GL_FALSE, &Projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(lightProgram, "view"), 1, GL_FALSE, &View[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(lightProgram, "model"), 1, GL_FALSE, &lightModel[0][0]);
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        glBindFramebuffer(GL_FRAMEBUFFER, 0); //以下为默认窗口帧缓冲

        glDisable(GL_DEPTH_TEST);

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(screenProgram);
        glUniform1i(glGetUniformLocation(screenProgram, "screenTexture"), 0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glBindVertexArray(screenVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);


        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);

    glDeleteVertexArrays(1 , &cudeVAO);
    glDeleteVertexArrays(1 , &lightVAO);
    glDeleteVertexArrays(1 , &screenVAO);
    glDeleteBuffers(1 , &VBO);
    glDeleteBuffers(1 , &FBO);
    glDeleteBuffers(1 , &RBO);
    glDeleteBuffers(1 , &screenVBO);

    return 0;
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}