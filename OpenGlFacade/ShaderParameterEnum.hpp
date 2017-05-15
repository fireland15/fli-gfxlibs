#pragma once

#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLEXT.h>

namespace OpenGL {

	enum class ShaderParameter : unsigned int {
		ShaderType = GL_SHADER_TYPE,
		DeleteStatus = GL_DELETE_STATUS,
		CompileStatus = GL_COMPILE_STATUS,
		InfoLogLength = GL_INFO_LOG_LENGTH,
		ShaderSourceLength = GL_SHADER_SOURCE_LENGTH
	};

}