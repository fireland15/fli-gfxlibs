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

	void Program::QueryForAttributeVariables() {
		GLint numActiveAttribs = 0;

		glGetProgramInterfaceiv(m_obj, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numActiveAttribs);

		std::vector<GLchar> nameData(256);
		std::vector<GLenum> props;
		props.push_back(GL_NAME_LENGTH);
		props.push_back(GL_TYPE);
		props.push_back(GL_ARRAY_SIZE);
		std::vector<GLint> values(props.size());

		for (GLint i = 0; i < numActiveAttribs; i++) {
			glGetProgramResourceiv(m_obj, GL_PROGRAM_INPUT, i, (GLsizei)props.size(), &props[0], (GLsizei)values.size(), 0, &values[0]);

			nameData.resize(values[0]);
			glGetProgramResourceName(m_obj, GL_PROGRAM_INPUT, i, (GLsizei)nameData.size(), 0, &nameData[0]);
			std::string name((char*)&nameData[0], nameData.size() - 1);

			AttributeVariable var(AttributeLocation(i), name, (AttributeVariable::AttribType)values[1]);
			m_attributeVariables.push_back(var);
		}
	}

	void Program::QueryForUniformVariables() {
		GLint numActiveUniforms = 0;

		glGetProgramInterfaceiv(m_obj, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numActiveUniforms);

		std::vector<GLchar> nameData(256);
		std::vector<GLenum> props;
		props.push_back(GL_NAME_LENGTH);
		props.push_back(GL_TYPE);
		props.push_back(GL_ARRAY_SIZE);
		std::vector<GLint> values(props.size());

		for (GLint i = 0; i < numActiveUniforms; i++) {
			glGetProgramResourceiv(m_obj, GL_UNIFORM, i, (GLsizei)props.size(), &props[0], (GLsizei)values.size(), 0, &values[0]);

			nameData.resize(values[0]);
			glGetProgramResourceName(m_obj, GL_UNIFORM, i, (GLsizei)nameData.size(), 0, &nameData[0]);
			std::string name((char*)&nameData[0], nameData.size() - 1);

			UniformVariable var(UniformLocation(i), name, (UniformVariable::UniformType)values[1]);
			m_uniformVariables.push_back(var);
		}
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

		QueryForAttributeVariables();
		QueryForUniformVariables();

		return true;
	}

	bool Program::HasErrors() {
		return m_hasErrors;
	}

	std::string Program::GetErrors() {
		return m_errors;
	}

	const AttributeVariable& Program::GetAttributeVariable(std::string name) {
		for (const AttributeVariable& var : m_attributeVariables) {
			if (var.Name().compare(name) == 0) {
				return var;
			}
		}

		throw std::exception("Could not find an attribute variable with name");
	}

	const std::vector<AttributeVariable>& Program::AttributeVariables() {
		return m_attributeVariables;
	}

}