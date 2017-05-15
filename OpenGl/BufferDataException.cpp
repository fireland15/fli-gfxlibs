#include "BufferDataException.hpp"

OpenGL::BufferDataException::BufferDataException(std::string message) : _message(message) {

}

OpenGL::BufferDataException::~BufferDataException() {

}

std::string OpenGL::BufferDataException::Message() {
	return _message;
}
