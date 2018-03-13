#include <iostream>
#include <Windows.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Common/camera.hpp>
#include <Common/Shader.hpp>

#define WIDTH 1920
#define HEIGHT 1080

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main()
{
	//初始化glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //设置最大版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //设置最小版本
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //设置core-profile
	glfwWindowHint(GLFW_RESIZABLE, false); //设置不可改变大小
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//创建一个窗口
	const auto window = glfwCreateWindow(WIDTH, HEIGHT, "Advanced GLSL", nullptr, nullptr);

	//设置窗口环境
	glfwMakeContextCurrent(window);

	if (window == nullptr) {
		std::cout << "Faild to create glfw window" << std::endl;
		glfwTerminate();
	}

	//设置glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Faild to init glew" << std::endl;
		return -1;
	}

	//设置位置
	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetKeyCallback(window, KeyCallback);


	static const GLfloat vertices[] = {

			-1.0f,-1.0f,-1.0f,

			-1.0f,-1.0f, 1.0f,

			-1.0f, 1.0f, 1.0f,

			1.0f, 1.0f,-1.0f,

			-1.0f,-1.0f,-1.0f,

			-1.0f, 1.0f,-1.0f,

			1.0f,-1.0f, 1.0f,

			-1.0f,-1.0f,-1.0f,

			1.0f,-1.0f,-1.0f,

			1.0f, 1.0f,-1.0f,

			1.0f,-1.0f,-1.0f,

			-1.0f,-1.0f,-1.0f,

			-1.0f,-1.0f,-1.0f,

			-1.0f, 1.0f, 1.0f,

			-1.0f, 1.0f,-1.0f,

			1.0f,-1.0f, 1.0f,

			-1.0f,-1.0f, 1.0f,

			-1.0f,-1.0f,-1.0f,

			-1.0f, 1.0f, 1.0f,

			-1.0f,-1.0f, 1.0f,

			1.0f,-1.0f, 1.0f,

			1.0f, 1.0f, 1.0f,

			1.0f,-1.0f,-1.0f,

			1.0f, 1.0f,-1.0f,

			1.0f,-1.0f,-1.0f,

			1.0f, 1.0f, 1.0f,

			1.0f,-1.0f, 1.0f,

			1.0f, 1.0f, 1.0f,

			1.0f, 1.0f,-1.0f,

			-1.0f, 1.0f,-1.0f,

			1.0f, 1.0f, 1.0f,

			-1.0f, 1.0f,-1.0f,

			-1.0f, 1.0f, 1.0f,

			1.0f, 1.0f, 1.0f,

			-1.0f, 1.0f, 1.0f,

			1.0f,-1.0f, 1.0f

	};

	unsigned int vertexArrayObject, vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 3, static_cast<void*>(0));
	glEnableVertexAttribArray(0);

	unsigned int uboBlock;
	glGenBuffers(1, &uboBlock);
	glBindBuffer(GL_UNIFORM_BUFFER, uboBlock);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, nullptr, GL_STATIC_DRAW); // 分配152字节的内存
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glEnable(GL_PROGRAM_POINT_SIZE);
	Shader glslShader("glsl.vertexShader", "glsl.fragmentShader");

	//bind 0
	const auto vpIndex = glGetUniformBlockIndex(glslShader.ID, "VP");
	glUniformBlockBinding(glslShader.ID, vpIndex, 0);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboBlock);


	const auto projection = glm::perspective(glm::radians(90.0f), static_cast<float>(WIDTH) / static_cast<float>(HEIGHT), 0.1f, 100.0f);
	auto camera = Camera(glm::vec3(0.0f, 0.0f, 10.0f));
	const auto model1 = glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 5.0f, 0.0f));
	const auto model2 = glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, 5.0f, 0.0f));
	const auto model3 = glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, -5.0f, 0.0f));
	const auto model4 = glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, -5.0f, 0.0f));

	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &projection);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &camera.GetViewMatrix());

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.1f, 0.1f, 1.0f);

		glslShader.use();
		glslShader.setMat4("model", model1);
		glBindVertexArray(vertexArrayObject);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glslShader.use();
		glslShader.setMat4("model", model2);
		glBindVertexArray(vertexArrayObject);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glslShader.use();
		glslShader.setMat4("model", model3);
		glBindVertexArray(vertexArrayObject);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glslShader.use();

		glslShader.setMat4("model", model4);
		glBindVertexArray(vertexArrayObject);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glfwSwapBuffers(window);

	}

	return 0;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

}