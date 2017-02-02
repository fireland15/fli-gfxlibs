#include "shader.hpp"

namespace opengl {

	void Shader::SetSource() {
		std::string src = m_source.Code();
		GLsizei count = 1;
		const GLchar* string = src.c_str();
		const GLint length = (GLint) src.length();

		glShaderSource(m_obj, count, &string, &length);
	}

	/*************************************************************
	* Constructors
	**************************************************************/

	Shader::Shader(gl::ShaderType type)
		: m_obj(0)
		, m_type(type)
		, m_errors("No errors")
		, m_hasErrors(false) {
		m_obj = glCreateShader(m_type);
	}

	Shader::Shader(Shader&& other) {
		m_obj = other.m_obj;
		m_type = other.m_type;
		m_source = other.m_source;
		m_hasErrors = other.m_hasErrors;
		m_errors = other.m_errors;

		other.m_obj = 0;
		other.m_type;
		other.m_source = ShaderSource();
		other.m_hasErrors = false;
		other.m_errors = "";
	}

	Shader& Shader::operator=(Shader&& other) {
		if (this != &other) {
			if (m_obj != 0) {
				// Todo: May need to do some other checks before deleting.
				glDeleteShader(m_obj);
			}

			m_obj = other.m_obj;
			m_type = other.m_type;
			m_source = other.m_source;
			m_hasErrors = other.m_hasErrors;
			m_errors = other.m_errors;

			other.m_obj = 0;
			other.m_type;
			other.m_source = ShaderSource();
			other.m_hasErrors = false;
			other.m_errors = "";
		}
		return *this;
	}

	/*************************************************************
	* Destructor
	**************************************************************/

	Shader::~Shader() {
		if (m_obj != 0) {
			glDeleteShader(m_obj);
		}
	}

	/*************************************************************
	* OpenGL Shader Methods
	**************************************************************/

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