#include "program.hpp"

namespace opengl {

	Program::Program(GLuint obj)
		: m_obj(obj)
		, m_hasErrors(false)
		, m_errors("No errors") { }

	Program::Program()
		: m_obj(0)
		, m_hasErrors(false)
		, m_errors("No errors") { }

	void Program::Attach(Shader& shader) {
		if (!shader.HasErrors()) {
			glAttachShader(m_obj, shader.Obj());
			m_attachedShaders.push_back(shader);
		}
	}

	bool Program::Link() {
		glLinkProgram(m_obj);

		GLint isLinked = 0;
		glGetProgramiv(m_obj, GL_LINK_STATUS, &isLinked);

		if (isLinked == GL_FALSE) {
			GLint logLength = 0;
			glGetProgramiv(m_obj, GL_INFO_LOG_LENGTH, &logLength);

			std::vector<GLchar> errorLog(logLength);
			glGetProgramInfoLog(m_obj, logLength, &logLength, &errorLog[0]);

			m_errors = std::string(&errorLog[0], errorLog.size());
			m_hasErrors = true;
			
			return false;
		}

		return true;
	}

	bool Program::HasErrors() {
		return m_hasErrors;
	}

	std::string Program::GetErrors() {
		return m_errors;
	}

}