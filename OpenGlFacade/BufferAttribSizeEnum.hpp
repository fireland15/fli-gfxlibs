#pragma once

#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLEXT.h>

namespace OpenGL {

	enum class BufferAttribSize : GLint {
		One		= 1,
		Two		= 2,
		Three	= 3,
		Four	= 4
	};

}