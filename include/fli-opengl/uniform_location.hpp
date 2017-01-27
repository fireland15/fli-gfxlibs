#pragma once

#include <glew/glew.h>
#include <gl\GL.h>

namespace opengl {
	
	class UniformLocation {
	public:
		UniformLocation(GLint location);

		UniformLocation();

		GLint Value() const;

	private:
		GLint m_value;
	};

}