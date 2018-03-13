#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Common/Shader.hpp>
#include <Common/camera.hpp>

using namespace std;
using namespace glm;

/**
 * 键盘回调函数
 */
void KeyCallback(GLFWwindow* window, const int key, int scancode, const int action, int mode);


int width = 1920, height = 1080;


int main() {

	if (!glfwInit()) {
		std::cout << "GLFW::ERROR::GLFW_INIT_ERROR" << std::endl;
		glfwTerminate();
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	//OpenGL 版本最小
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);	//OpenGL 版本最大
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	const auto window = glfwCreateWindow(width, height, "Geometry Shader Window", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "GLFW::ERROR::GLFW_CREATE_WINDOW_ERROR" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW::ERROR::GLEW_INIT_ERROR" << std::endl;
		glfwTerminate();
	}

	GLfloat vertices[] = {
		0.0f , 0.0f , 0.0f
	};
	GLuint vertexBufferObject, vertexArraysObject;
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vertexArraysObject);
	glBindVertexArray(vertexArraysObject);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, static_cast<void*>(0));
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glEnable(GL_PROGRAM_POINT_SIZE);

	Shader shader("vertex.vertexShader", "fragment.fragmentShader" , "geometry.geometryShader");
	Camera camera(vec3(0.0f, 0.0f, 3.0f));

	const auto model = mat4(1.0f);
	const auto projection = perspective(radians(90.0f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glfwSetKeyCallback(window, KeyCallback);

		shader.use();
		shader.setMat4("projection", projection);
		shader.setMat4("view", camera.GetViewMatrix());
		shader.setMat4("model", model);
		glBindVertexArray(vertexArraysObject);
		glDrawArrays(GL_POINTS, 0, 3);
		glBindVertexArray(0);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}

void KeyCallback(GLFWwindow* window, const int key, int scancode, const int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

