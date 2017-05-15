#pragma once

#include <Windows.h>
#include <GL/GL.h>
#include <GL/GLEXT.h>

namespace OpenGL {

	enum class Transpose : unsigned char {
		Yes = GL_TRUE,
		No = GL_FALSE
	};

}