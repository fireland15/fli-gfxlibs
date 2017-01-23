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

		void GetAttributeVariables();

	public:
		Program();

		void Attach(Shader& shader);

		void Detach(Shader& shader);

		void Use();

		bool Link();

		bool HasErrors();

		std::string GetErrors();

		const AttributeVariable& GetAttributeVariable(std::string name);

		const std::vector<AttributeVariable>& AttributeVariables();

		friend class GL;

	private:
		GLuint m_obj;

		bool m_hasErrors;

		std::string m_errors;

		std::vector<AttributeVariable> m_attributeVariables;
	};

}