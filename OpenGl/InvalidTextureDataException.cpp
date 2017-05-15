#include "InvalidTextureDataException.hpp"

OpenGL::InvalidTextureDataException::InvalidTextureDataException() {
	_message = "There was an error assigning texture data";
}

OpenGL::InvalidTextureDataException::InvalidTextureDataException(std::string& message)
	: _message(message) { }

std::string OpenGL::InvalidTextureDataException::Message() {
	return _message;
}