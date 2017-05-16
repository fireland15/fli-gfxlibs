#include "GlfwInitializationException.hpp"

Fenestram::GlfwInitializationException::GlfwInitializationException() {
	_message = std::string("Failed to initialize GLFW");
}

std::string Fenestram::GlfwInitializationException::Message() {
	return _message;
}
