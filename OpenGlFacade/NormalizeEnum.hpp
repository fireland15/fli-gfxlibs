#pragma once

#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLEXT.h>

namespace OpenGL {

	enum class Normalize : GLboolean {
		Yes = GL_TRUE,
		No	= GL_FALSE
	};

}