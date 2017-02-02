#include "opengl.hpp"

namespace opengl {

	namespace gl {

		OpenGlError GetErrors() {
			return OpenGlError((OpenGlError::Error)glGetError());
		}

		void ClearColor(glm::vec4 color) {
			glClearColor(color.r, color.g, color.b, color.a);
		}

		void Clear(GLbitfield buffers) {
			glClear(buffers);
		}

	}

}