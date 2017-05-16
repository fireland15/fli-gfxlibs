#include "Glfw.integration.hpp"

#include <glew\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>

void error_callback(int error, const char* description) {
	std::cout << "Error: " << description << std::endl;
}

void GlfwTest() {
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	if (!glewInit()) {
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(400, 400, "Glfw Test", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwWaitEvents();
	}

	glfwTerminate();
	exit(EXIT_SUCCESS);
}