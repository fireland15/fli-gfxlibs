#pragma once

#include <string>

#include <glew\glew.h>
#include <GL\GL.h>

namespace opengl {

	class OpenGlError {
	public:
		enum Error : GLenum {
			NoError				= GL_NO_ERROR,
			InvalidEnum			= GL_INVALID_ENUM,
			InvalidValue		= GL_INVALID_VALUE,
			InvalidOperation	= GL_INVALID_OPERATION,
			StackOverflow		= GL_STACK_OVERFLOW,
			StackUnderflow		= GL_STACK_UNDERFLOW,
			OutOfMemory			= GL_OUT_OF_MEMORY,
			Unknown
		};

		OpenGlError(Error error);

		bool IsError();

		std::string ToString();

	private:
		Error m_error;
	};

}