#pragma once

#define GLEW_STATIC

#include <string>
#include <sstream>

#include <gl\glew.h>
#include <gl\GLU.h>

#define OpenGlCheckErrors() gfx::render::OpenGlError::CheckErrors(__FILE__, __LINE__)

namespace gfx {
	namespace render {
		
		class OpenGlError {
		private:
			const GLubyte* m_pError;

			OpenGlError(const GLubyte* error);

		public:
			bool IsError();

			bool IsOk();

			std::string ToString();

			static OpenGlError CheckErrors(char* file, int line);
		};

	}
}