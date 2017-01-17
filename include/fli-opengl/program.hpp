#pragma once

#include <vector>
#include <string>

#include <GL\glew.h>
#include <GL\GL.h>

#include "shader.hpp"

namespace opengl {

	class Program {
	private:
		Program(GLuint obj);

	public:
		Program();

		void Attach(Shader& shader);

		bool Link();

		bool HasErrors();

		std::string GetErrors();

		friend class GL;

	private:
		GLuint m_obj;
		std::vector<Shader&> m_attachedShaders;
		bool m_hasErrors;
		std::string m_errors;
	};

}