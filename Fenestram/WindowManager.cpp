#include "WindowManager.hpp"

#include <GLFW\glfw3.h>
#include <iostream>
#include "WindowErrorException.hpp"
#include "WindowCreationException.hpp"
#include "GlfwInitializationException.hpp"
#include "Window.hpp"

void glfwErrorCallback(int error, const char* description);

Fenestram::WindowManager::WindowManager() {
	glfwSetErrorCallback(glfwErrorCallback);
	if (!glfwInit()) {
		throw Fenestram::GlfwInitializationException();
	}
}

Fenestram::WindowManager::~WindowManager() {
	glfwTerminate();
}

std::unique_ptr<Fenestram::Window> Fenestram::WindowManager::GetNewWindow(glm::uvec2 windowDim, std::string windowTitle) {
	glfwWindowHint(GLFW_RED_BITS, 8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	GLFWwindow* window = glfwCreateWindow(windowDim.x, windowDim.y, windowTitle.c_str(), nullptr, nullptr);
	if (!window) {
		throw Fenestram::WindowCreationException();
	}

	Fenestram::Window* wnd = new Fenestram::Window(window);

	return std::unique_ptr<Fenestram::Window>(wnd);
}

void glfwErrorCallback(int error, const char* description) {
	throw Fenestram::WindowErrorException(std::string(description));
}