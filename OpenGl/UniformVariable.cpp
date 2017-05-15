#include "UniformVariable.hpp"

OpenGL::UniformVariable::UniformVariable(int location, std::string name, UniformType type)
	: _location(location), _name(name), _type(type) {
}

OpenGL::UniformType OpenGL::UniformVariable::Type() const {
	return _type;
}

int OpenGL::UniformVariable::Location() const {
	return _location;
}

std::string OpenGL::UniformVariable::Name() const {
	return _name;
}

bool OpenGL::UniformVariable::operator<(const OpenGL::UniformVariable other) const {
	return _name.compare(other._name) < 0;
}