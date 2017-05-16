#include "Window.hpp"

#include <glew\glew.h>
#include <GLFW\glfw3.h>
#include <OpenGlFacade\RealOpenGL.hpp>
#include <OpenGlFacade\OpenGLWrapper.hpp>
#include <OpenGl\OpenGlContext.hpp>

#include "WindowCreationException.hpp"

void WindowCloseFunction(GLFWwindow* window);

Fenestram::Window::Window(GLFWwindow* window) 
	: _glfwWindow(window) {
	if (window == nullptr)
		throw WindowCreationException();

	glfwSetWindowUserPointer(_glfwWindow, this);
	_shouldClose = false;
}

Fenestram::Window::~Window() {
	delete _glContext;
	delete _glWrapper;
	delete _gl;

	glfwDestroyWindow(_glfwWindow);
}

OpenGL::OpenGlContext& Fenestram::Window::GetContext() {
	glfwMakeContextCurrent(_glfwWindow);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::string error((const char*)glewGetErrorString(err));
		throw WindowCreationException(std::string("Unable to initialize GLEW"));
	}

	_gl = new OpenGL::RealOpenGL();
	_glWrapper = new OpenGL::OpenGLWrapper(*_gl);
	_glContext = new OpenGL::OpenGlContext(*_glWrapper);

	return *_glContext;
}

bool Fenestram::Window::ShouldClose() const {
	return _shouldClose;
}

void Fenestram::Window::ShouldClose(bool shouldClose) {
	_shouldClose = shouldClose;
}

void Fenestram::Window::SwapBuffers() {
	glfwSwapBuffers(_glfwWindow);
}

void WindowCloseFunction(GLFWwindow* window) {
	Fenestram::Window* This = static_cast<Fenestram::Window*>(glfwGetWindowUserPointer(window));
	This->ShouldClose(true);
}