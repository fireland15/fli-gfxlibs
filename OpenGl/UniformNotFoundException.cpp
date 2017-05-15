#include "UniformNotFoundException.hpp"

#include <sstream>

OpenGL::UniformNotFoundException::UniformNotFoundException() 
	: _uniformName("unknown") {

}

OpenGL::UniformNotFoundException::UniformNotFoundException(const std::string & name) 
	: _uniformName(name) {

}

std::string OpenGL::UniformNotFoundException::Message() {
	std::stringstream ss;
	ss << "Attempted to set the uniform '" << _uniformName << "' when that uniform is not a part of the current program." << std::endl;
	return ss.str();
}
