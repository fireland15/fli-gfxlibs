#include "Handle.hpp"

OpenGL::Handle::Handle(ObjectType type, unsigned int h) : _type(type), _value(h) { }

bool OpenGL::Handle::operator==(const Handle& other) {
	if (_type != other._type) return false;

	return other._value == _value;
}

bool OpenGL::Handle::operator!=(const Handle & other) {
	return false;
}

OpenGL::ObjectType OpenGL::Handle::Type() const { return _type; }

unsigned int OpenGL::Handle::Value() const { return _value; }

OpenGL::Handle OpenGL::Handle::Default() {
	return Handle(ObjectType::VertexArray, 0);
}
