// Include standard headers
#include <cstdio>
#include <cstdlib>

#define GLEW_STATIC
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
#include <iostream>

GLFWwindow *window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.hpp"
#include "Model.h"

#include <assimp/mesh.h>

using namespace glm;

float FOV = 90.0f;
int WIDTH = 1024, HEIGHT = 768;

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void resize_callback(GLFWwindow *window, int width, int height);


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
    window = glfwCreateWindow(WIDTH, HEIGHT, "FPS", nullptr, nullptr);
    if (window == nullptr) {
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
            0, // attribute. No particular reason for 0, but must match the layout in the shader.
            3, // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            6 * sizeof(float), // stride
            (void *) nullptr // array buffer offset
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
            (void *) nullptr);
    glEnableVertexAttribArray(0);

    Shader cudeShader("../shader/vertexShader.vs", "../shader/fragmentShader.fs");
    Shader lightShader("../shader/lightVertexShader.vs", "../shader/lightFragmentShader.fs");
    Shader nanosuitShader("../shader/model_loading.vs", "../shader/model_loading.fs");
    Model nanosuit("../obj/nanosuit.obj");


    vec3 cameraPos(0.0f, 5.0f, 20.0f);
    vec3 cameraFront(0.0f, 0.0f, -20.0f);
    vec3 cameraUp(0.0f, 1.0f, 0.0f);

    // Model matrix : an identity matrix (model will be at the origin)
    mat4 floorModel = mat4(1.0f) *
                      scale(mat4(1.0f), vec3(1000.0f, 0.2f, 1000.0f));

    mat4 lightModel = mat4(1.0f) *
                      translate(mat4(1.0f), vec3(0.0f, 100.0f, 0.0f)) *
                      scale(mat4(1.0f), vec3(0.2f, 0.2f, 0.2f));

    mat4 nanosuitModel = mat4(1.0f) *
                         translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f)) *
                         scale(mat4(1.0f), vec3(0.5f, 0.5f, 0.5f));

    mat4 wall1 = mat4(1.0f) *
                 translate(mat4(1.0f), vec3(-15.0f, 0.0f, 15.0f)) *
                 scale(mat4(1.0f), vec3(20.0f, 40.0f, 20.0f));

    mat4 wall2 = mat4(1.0f) *
                 translate(mat4(1.0f), vec3(15.0f, 0.0f, 15.0f)) *
                 scale(mat4(1.0f), vec3(20.0f, 40.0f, 20.0f));

    mat4 wall3 = mat4(1.0f) *
                 translate(mat4(1.0f), vec3(-15.0f, 0.0f, -15.0f)) *
                 scale(mat4(1.0f), vec3(20.0f, 40.0f, 20.0f));

    mat4 wall4 = mat4(1.0f) *
                 translate(mat4(1.0f), vec3(15.0f, 0.0f, -15.0f)) *
                 scale(mat4(1.0f), vec3(20.0f, 40.0f, 20.0f));

    double curPosX = 1024 / 2, curPosY = 768 / 2;
    double preX = curPosX, preY = curPosY;

    bool jumpState = false, jumpUp = true;
    double currentHeight = 0.0f;
    float speed = 0.1f;

    glfwSetCursorPos(window, WIDTH / 2, HEIGHT / 2);

    vec3 nanosuitPos = cameraPos;
    vec3 nanosuitFront = cameraFront;
    double pitch = 0.0, yaw = 0.0;

    do {


        glfwSetWindowSizeCallback(window, resize_callback);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            cameraPos += speed * vec3(cameraFront.x, 0.0f, cameraFront.z);
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            cameraPos += -speed * vec3(cameraFront.x, 0.0f, cameraFront.z);
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            cameraPos += -speed * cross(vec3(cameraFront.x, 0.0f, cameraFront.z), cameraUp);
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            cameraPos += speed * cross(vec3(cameraFront.x, 0.0f, cameraFront.z), cameraUp);
        }

        // jump
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            if (!jumpState) {
                jumpState = true;
                cameraPos += vec3(0.0f, 0.1f, 0.0f);
                currentHeight = 0.1f;
            }
        }

        if (jumpState) {
            if (currentHeight < 0.1f) {
                jumpState = false;
                jumpUp = true;
                currentHeight = 0.0;
            } else {
                if (currentHeight >= 2.0f) {
                    jumpUp = false;
                }
                if (jumpUp) {
                    currentHeight += 0.1f;
                    cameraPos += vec3(0.0f, 0.1f, 0.0f);
                } else {
                    currentHeight -= 0.1f;
                    cameraPos += vec3(0.0f, -0.1f, 0.0f);
                }
            }
        }


        glfwGetCursorPos(window, &curPosX, &curPosY);

        if (curPosX < 0 || curPosX > WIDTH || curPosY < 0 || curPosY > HEIGHT) {
            if (curPosX <= 0) curPosX = preX = WIDTH - 1;
            if (curPosX >= WIDTH) curPosX = preX = 1;
            if (curPosY <= 0) curPosY = preY = HEIGHT - 1;
            if (curPosY >= HEIGHT) curPosY = preY = 1;
            glfwSetCursorPos(window, curPosX, curPosY);
        }

        pitch += (preY - curPosY) * 0.5;
        yaw += (curPosX - preX) * 0.5;

        pitch = max(-89.0, min(89.0, pitch));

        cameraFront = normalize(vec3(cos(radians(pitch)) * cos(radians(yaw)), sin(radians(pitch)),
                                     cos(radians(pitch)) * sin(radians(yaw))));

        preX = curPosX;
        preY = curPosY;

        glfwSetScrollCallback(window, scroll_callback);


        mat4 View = lookAt(cameraPos, cameraFront + cameraPos, cameraUp);
        mat4 Projection = perspective(radians(FOV), (float) WIDTH / (float) HEIGHT, 0.1f, 100.0f);

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        nanosuitShader.use();
        nanosuitModel = nanosuitModel * rotate(mat4(1.0f) , radians(1.0f) , vec3(0.0f , 1.0f , 0.0f));
        nanosuitShader.setMat4("projection", Projection);
        nanosuitShader.setMat4("model", nanosuitModel);
        nanosuitShader.setMat4("view", View);
        nanosuit.Darw(nanosuitShader);

        nanosuitPos = cameraPos;
        nanosuitFront = cameraFront;

        cudeShader.use();
        cudeShader.setMat4("view", View);
        cudeShader.setMat4("projection", Projection);
        cudeShader.setVec3("viewPos", 4.0f, 5.0f, 3.0f);
        cudeShader.setVec3("lightPos", 0.0f, 10.0f, 0.0f);
        cudeShader.setVec3("objectColor", 0.3f, 0.3f, 0.3f);
        cudeShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

        cudeShader.setMat4("model", floorModel);
        glBindVertexArray(cudeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        cudeShader.setMat4("model", wall1);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        cudeShader.setMat4("model", wall2);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        cudeShader.setMat4("model", wall3);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        cudeShader.setMat4("model", wall4);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        lightShader.use();
        lightShader.setMat4("projection", Projection);
        lightShader.setMat4("view", View);
        lightShader.setMat4("model", lightModel);
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);

    return 0;
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    if (FOV > 120.0 && yoffset > 0.0
        || FOV < 45.0 && yoffset < 0.0)
        return;
    FOV += yoffset;
}

void resize_callback(GLFWwindow *window, int width, int height) {
    WIDTH = width;
    HEIGHT = height;
}