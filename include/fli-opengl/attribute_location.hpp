#pragma once

#include <glew\glew.h>
#include <GL\GL.h>

namespace opengl {

	class AttributeLocation {
	public:
		AttributeLocation(GLint location);

		AttributeLocation();

		GLint Value() const;

	private:
		GLint m_value;
	};

}