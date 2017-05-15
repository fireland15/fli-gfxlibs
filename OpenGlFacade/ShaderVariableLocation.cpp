#include "ShaderVariableLocation.hpp"

OpenGL::ShaderVariableLocation::ShaderVariableLocation(int location) 
	: _location(location) { }

int OpenGL::ShaderVariableLocation::Value() {
	return _location;
}
