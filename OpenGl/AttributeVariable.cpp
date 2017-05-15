#include "AttributeVariable.hpp"

OpenGL::AttributeVariable::AttributeVariable(int location, std::string name, AttributeType type)
	: _location(location), _name(name), _type(type) {

}

OpenGL::AttributeType OpenGL::AttributeVariable::Type() const {
	return _type;
}

std::string OpenGL::AttributeVariable::Name() const {
	return _name;
}

int OpenGL::AttributeVariable::Location() const {
	return _location;
}

bool OpenGL::AttributeVariable::operator<(const OpenGL::AttributeVariable & other) const {
	return _name.compare(other._name);
}