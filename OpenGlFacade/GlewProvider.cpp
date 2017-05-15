#include "GlewProvider.hpp"

#include <glew.h>
#include <GL\GL.h>

unsigned int OpenGL::GlewProvider::Init() {
	return glewInit();
}

unsigned int OpenGL::GlewProvider::Ok() {
	return GLEW_OK;
}
