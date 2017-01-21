#include "program.hpp"

namespace opengl {

	Program::Program(GLuint obj)
		: m_obj(obj)
		, m_hasErrors(false)
		, m_errors("No errors") { }

	GLuint Program::Obj() {
		return m_obj;
	}

	void Program::Obj(GLuint obj) {
		m_obj = obj;
	}

	Program::Program()
		: m_obj(0)
		, m_hasErrors(false)
		, m_errors("No errors") { }

	void Program::Attach(Shader& shader) {
		glAttachShader(m_obj, shader.Obj());
	}

	void Program::Detach(Shader& shader) {
		glDetachShader(m_obj, shader.Obj());
	}

	void Program::Use() {
		glUseProgram(m_obj);
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

	AttributeVariable Program::GetAttributeVariable(std::string name) {
		GLint location = glGetAttribLocation(m_obj, name.c_str());
		return AttributeVariable(location, name);
	}

}