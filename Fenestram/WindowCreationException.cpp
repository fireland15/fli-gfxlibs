#include "WindowCreationException.hpp"

Fenestram::WindowCreationException::WindowCreationException() {
	_message = std::string("There was a problem creating a window");
}

Fenestram::WindowCreationException::WindowCreationException(std::string message) 
	: _message(message) {
}

std::string Fenestram::WindowCreationException::Message() {
	return _message;
}
