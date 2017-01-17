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

		GLuint Obj();

		void Obj(GLuint obj);

	public:
		Program();

		void Attach(Shader& shader);

		void Detach(Shader& shader);

		bool Link();

		bool HasErrors();

		std::string GetErrors();

		friend class GL;

	private:
		GLuint m_obj;
		bool m_hasErrors;
		std::string m_errors;
	};

}