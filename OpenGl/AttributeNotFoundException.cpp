#include "AttributeNotFoundException.hpp"

#include <sstream>

OpenGL::AttributeNotFoundException::AttributeNotFoundException()
	: _attributeName("unknown") {

}

OpenGL::AttributeNotFoundException::AttributeNotFoundException(const std::string & name)
	: _attributeName(name) {

}

std::string OpenGL::AttributeNotFoundException::Message() {
	std::stringstream ss;
	ss << "Attempted to set the uniform '" << _attributeName << "' when that uniform is not a part of the current program." << std::endl;
	return ss.str();
}
