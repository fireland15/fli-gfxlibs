#pragma once

#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLEXT.h>

namespace OpenGL {

	enum class Success : unsigned int {
		Yes = GL_TRUE,
		No = GL_FALSE
	};

}