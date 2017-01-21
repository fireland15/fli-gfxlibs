#pragma once

#include <string>

#include <glew\glew.h>
#include <GL\GL.h>

#include "attribute_location.hpp"

namespace opengl {

	class AttributeVariable {
	private:
		AttributeVariable(GLint location, std::string name);

	public:
		AttributeVariable();

		std::string Name();

		bool IsValid();

		const AttributeLocation& Location() const;

	private:
		AttributeLocation m_location;

		std::string m_name;

		friend class Program;
	};

}