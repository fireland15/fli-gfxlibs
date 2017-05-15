#pragma once

#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLEXT.h>

namespace OpenGL {

	enum class ProgramParameters : unsigned int {
		DeleteStatus = GL_DELETE_STATUS,
		LinkStatus = GL_LINK_STATUS,
		ValidateStatus = GL_VALIDATE_STATUS,
		InfoLogLength = GL_INFO_LOG_LENGTH,
		AttachedShaders = GL_ATTACHED_SHADERS,
		ActiveAttributes = GL_ACTIVE_ATTRIBUTES,
		ActiveAttributeMaxLength = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
		ActiveUniforms = GL_ACTIVE_UNIFORMS,
		ActiveUniformMaxLength = GL_ACTIVE_UNIFORM_MAX_LENGTH
	};

}