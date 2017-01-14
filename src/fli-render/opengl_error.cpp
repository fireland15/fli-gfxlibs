#include "opengl_error.hpp"

namespace gfx {
	namespace render {

		OpenGlError::OpenGlError(const GLubyte* error)
			: m_pError(error) {

		}

		bool OpenGlError::IsError() {
			return !IsOk();
		}

		bool OpenGlError::IsOk() {
			return m_pError == nullptr;
		}

		std::string OpenGlError::ToString() {
			std::stringstream ss;
			ss << m_pError;
			return ss.str();
		}

		OpenGlError OpenGlError::CheckErrors(char* file, int line) {
			const GLenum err = glGetError();
			if (err == GL_NO_ERROR) {
				return OpenGlError(nullptr);
			}
			else {
				const GLubyte* errstr = glewGetErrorString(err);
				return OpenGlError(errstr);
			}
		}

	}
}