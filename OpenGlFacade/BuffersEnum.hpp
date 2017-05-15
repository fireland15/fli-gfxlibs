#pragma once

#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLEXT.h>

namespace OpenGL {

	enum class Buffers : GLenum {
		Color			= GL_COLOR_BUFFER_BIT,
		Depth			= GL_DEPTH_BUFFER_BIT,
		Accumulation	= GL_ACCUM_BUFFER_BIT,
		Stencil			= GL_STENCIL_BUFFER_BIT
	};

}