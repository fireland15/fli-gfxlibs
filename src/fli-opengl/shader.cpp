#include "shader.hpp"

namespace opengl {

	Shader::Shader(GLuint obj) 
		: m_obj(obj)
		, m_errors("No errors")
		, m_hasErrors(false) { }

	GLuint Shader::Obj() {
		return m_obj;
	}

	void Shader::Obj(GLuint obj) {
		m_obj = obj;
	}

	void Shader::SetSource() {
		std::string src = m_source.Code();
		GLsizei count = 1;
		const GLchar* string = src.c_str();
		const GLint* length = (GLint*) src.length();

		glShaderSource(m_obj, count, &string, length);
	}

	Shader::Shader() 
		: m_obj(0)
		, m_errors("No errors")
		, m_hasErrors(false) { }

	void Shader::SetSource(ShaderSource source) {
		m_source = source;
		SetSource();
	}

	bool Shader::Compile() {
		glCompileShader(m_obj);

		GLint success = 0;
		glGetShaderiv(m_obj, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE) {
			GLint logLength = 0;
			glGetShaderiv(m_obj, GL_INFO_LOG_LENGTH, &logLength);

			std::vector<GLchar> errorLog(logLength);
			glGetShaderInfoLog(m_obj, logLength, &logLength, &errorLog[0]);

			m_errors = std::string(&errorLog[0], errorLog.size());

			m_hasErrors = true;
			return false;
		}

		m_hasErrors = false;
		return true;
	}

	bool Shader::HasErrors() {
		return m_hasErrors;
	}

	std::string Shader::GetErrors() {
		return m_errors;
	}

}