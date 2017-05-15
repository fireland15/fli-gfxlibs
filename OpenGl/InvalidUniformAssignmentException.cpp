#include "InvalidUniformAssignmentException.hpp"

#include <sstream>

#include "UniformTypeFormatter.hpp"

OpenGL::InvalidUniformAssignmentException::InvalidUniformAssignmentException() {

}

OpenGL::InvalidUniformAssignmentException::InvalidUniformAssignmentException(const std::string & name, OpenGL::UniformType uniformType, OpenGL::UniformType attemptedType)	
	: _name(name), _uniformType(uniformType), _attemptedType(attemptedType) {

}

std::string OpenGL::InvalidUniformAssignmentException::Message() {
	if (_name.empty()) {
		return "Invalid assignment to a uniform variable";
	}

	std::stringstream ss;
	ss << "Invalid assignment of a non-" << OpenGL::UniformTypeFormatter().ToString(_attemptedType) << " to the uniform '" << _name << "' of type " << OpenGL::UniformTypeFormatter().ToString(_uniformType) << std::endl;
	return ss.str();
}