#pragma once

#include <glew\glew.h>
#include <GL\GL.h>

namespace opengl {

	class AttributeLocation {
	private:
		AttributeLocation(GLint location);

	public:
		AttributeLocation();

		GLint Value() const;

		friend class AttributeVariable;

	private:
		GLint m_value;
	};

}