#pragma once

#include <vector>
#include <string>

#include <glew\glew.h>
#include <GL\GL.h>

#include "shader.hpp"
#include "attribute_variable.hpp"

namespace opengl {

	class Program {
	private:
		Program(GLuint obj);

		GLuint Obj();

		void Obj(GLuint obj);

	public:
		Program();

		void Attach(Shader& shader);

		void Detach(Shader& shader);

		void Use();

		bool Link();

		bool HasErrors();

		std::string GetErrors();

		AttributeVariable GetAttributeVariable(std::string name);

		friend class GL;

	private:
		GLuint m_obj;
		bool m_hasErrors;
		std::string m_errors;
	};

}