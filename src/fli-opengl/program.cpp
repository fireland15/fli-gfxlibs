#include "program.hpp"

namespace opengl {

	/*************************************************************
	* Constructors
	**************************************************************/

	Program::Program()
		: m_obj(0)
		, m_hasErrors(false)
		, m_errors("No errors") { 
		m_obj = glCreateProgram();
	}

	Program::Program(Program&& other) {
		m_obj = other.m_obj;
		m_hasErrors = other.m_hasErrors;
		m_errors = other.m_errors;
		m_attributeVariables.swap(other.m_attributeVariables);
		m_uniformVariables.swap(other.m_uniformVariables);

		other.m_obj = 0;
		other.m_hasErrors = false;
		other.m_errors = "";
		other.m_attributeVariables.clear();
		other.m_uniformVariables.clear();
	}

	Program& Program::operator=(Program&& other) {
		if (this != &other) {
			if (m_obj != 0) {
				// TODO: May need to do something about attached shaders?
				glDeleteProgram(m_obj);
			}

			// Copy from other
			m_obj = other.m_obj;
			m_hasErrors = other.m_hasErrors;
			m_errors = other.m_errors;
			m_attributeVariables.swap(other.m_attributeVariables);
			m_uniformVariables.swap(other.m_uniformVariables);

			// Reset other to defaults
			other.m_obj = 0;
			other.m_hasErrors = false;
			other.m_errors = "";
			other.m_attributeVariables.clear();
			other.m_uniformVariables.clear();
		}
		return *this;
	}

	/*************************************************************
	* Destructor
	**************************************************************/

	Program::~Program() {
		if (m_obj != 0) {
			glDeleteProgram(m_obj);
		}
	}

	/*************************************************************
	* OpenGL Program Methods
	**************************************************************/

	void Program::Attach(up_Shader shader) {
		glAttachShader(m_obj, shader->m_obj);
		m_attachedShaders.push_back(std::move(shader));
	}

	void Program::DetachAndDeleteAllShaders() {
		m_attachedShaders.clear();
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

	const UniformVariable& Program::GetUniformVariable(std::string name) {
		for (const UniformVariable& var : m_uniformVariables) {
			if (var.Name().compare(name) == 0) {
				return var;
			}
		}

		throw std::exception("Could not find a uniform variable with name");
	}

	const std::vector<UniformVariable>& Program::UniformVariables() {
		return m_uniformVariables;
	}
	
	void Program::SetUniform(UniformVariable uniform, float value) {
		if (uniform.Type() == UniformVariable::UniformType::Float) {
			glProgramUniform1f(m_obj, uniform.Location().Value(), value);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, glm::vec2 value) {
		if (uniform.Type() == UniformVariable::UniformType::Vec2f) {
			glProgramUniform2f(m_obj, uniform.Location().Value(), value[0], value[1]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, glm::vec3 value) {
		if (uniform.Type() == UniformVariable::UniformType::Vec3f) {
			glProgramUniform3f(m_obj, uniform.Location().Value(), value[0], value[1], value[2]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, glm::vec4 value) {
		if (uniform.Type() == UniformVariable::UniformType::Vec4f) {
			glProgramUniform4f(m_obj, uniform.Location().Value(), value[0], value[1], value[2], value[3]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, int value) {
		if (uniform.Type() == UniformVariable::UniformType::Int) {
			glProgramUniform1i(m_obj, uniform.Location().Value(), value);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, glm::ivec2 value) {
		if (uniform.Type() == UniformVariable::UniformType::Vec2i) {
			glProgramUniform2i(m_obj, uniform.Location().Value(), value[0], value[1]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, glm::ivec3 value) {
		if (uniform.Type() == UniformVariable::UniformType::Vec3i) {
			glProgramUniform3i(m_obj, uniform.Location().Value(), value[0], value[1], value[2]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, glm::ivec4 value) {
		if (uniform.Type() == UniformVariable::UniformType::Vec4i) {
			glProgramUniform4i(m_obj, uniform.Location().Value(), value[0], value[1], value[2], value[3]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, unsigned int value) {
		if (uniform.Type() == UniformVariable::UniformType::UnsignedInt) {
			glProgramUniform1ui(m_obj, uniform.Location().Value(), value);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, glm::uvec2 value) {
		if (uniform.Type() == UniformVariable::UniformType::Vec2u) {
			glProgramUniform2ui(m_obj, uniform.Location().Value(), value[0], value[1]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, glm::uvec3 value) {
		if (uniform.Type() == UniformVariable::UniformType::Vec3u) {
			glProgramUniform3ui(m_obj, uniform.Location().Value(), value[0], value[1], value[2]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, glm::uvec4 value) {
		if (uniform.Type() == UniformVariable::UniformType::Vec4u) {
			glProgramUniform4ui(m_obj, uniform.Location().Value(), value[0], value[1], value[2], value[3]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, std::vector<float> values) {
		if (uniform.Type() == UniformVariable::UniformType::Float) {
			glProgramUniform1fv(m_obj, uniform.Location().Value(), (GLsizei)values.size(), &values[0]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, std::vector<glm::vec2> values) {
		if (uniform.Type() == UniformVariable::UniformType::Vec2f) {
			glProgramUniform2fv(m_obj, uniform.Location().Value(), (GLsizei)values.size(), &values[0][0]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, std::vector<glm::vec3> values) {
		if (uniform.Type() == UniformVariable::UniformType::Vec3f) {
			glProgramUniform3fv(m_obj, uniform.Location().Value(), (GLsizei)values.size(), &values[0][0]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, std::vector<glm::vec4> values) {
		if (uniform.Type() == UniformVariable::UniformType::Vec4f) {
			glProgramUniform4fv(m_obj, uniform.Location().Value(), (GLsizei)values.size(), &values[0][0]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, std::vector<int> values) {
		if (uniform.Type() == UniformVariable::UniformType::Int) {
			glProgramUniform1iv(m_obj, uniform.Location().Value(), (GLsizei)values.size(), &values[0]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, std::vector<glm::ivec2> values) {
		if (uniform.Type() == UniformVariable::UniformType::Vec2i) {
			glProgramUniform2iv(m_obj, uniform.Location().Value(), (GLsizei)values.size(), &values[0][0]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, std::vector<glm::ivec3> values) {
		if (uniform.Type() == UniformVariable::UniformType::Vec3i) {
			glProgramUniform3iv(m_obj, uniform.Location().Value(), (GLsizei)values.size(), &values[0][0]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, std::vector<glm::ivec4> values) {
		if (uniform.Type() == UniformVariable::UniformType::Vec4i) {
			glProgramUniform4iv(m_obj, uniform.Location().Value(), (GLsizei)values.size(), &values[0][0]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, std::vector<unsigned int> values) {
		if (uniform.Type() == UniformVariable::UniformType::UnsignedInt) {
			glProgramUniform1uiv(m_obj, uniform.Location().Value(), (GLsizei)values.size(), &values[0]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, std::vector<glm::uvec2> values) {
		if (uniform.Type() == UniformVariable::UniformType::Vec2u) {
			glProgramUniform2uiv(m_obj, uniform.Location().Value(), (GLsizei)values.size(), &values[0][0]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, std::vector<glm::uvec3> values) {
		if (uniform.Type() == UniformVariable::UniformType::Vec3u) {
			glProgramUniform3uiv(m_obj, uniform.Location().Value(), (GLsizei)values.size(), &values[0][0]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, std::vector<glm::uvec4> values) {
		if (uniform.Type() == UniformVariable::UniformType::Vec4u) {
			glProgramUniform4uiv(m_obj, uniform.Location().Value(), (GLsizei)values.size(), &values[0][0]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, std::vector<glm::mat2> values) {
		if (uniform.Type() == UniformVariable::UniformType::Mat2f) {
			glProgramUniformMatrix2fv(m_obj, uniform.Location().Value(), (GLsizei)values.size(), GL_FALSE, &values[0][0][0]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, std::vector<glm::mat3> values) {
		if (uniform.Type() == UniformVariable::UniformType::Mat3f) {
			glProgramUniformMatrix3fv(m_obj, uniform.Location().Value(), (GLsizei)values.size(), GL_FALSE, &values[0][0][0]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, std::vector<glm::mat4> values) {
		if (uniform.Type() == UniformVariable::UniformType::Mat4f) {
			glProgramUniformMatrix4fv(m_obj, uniform.Location().Value(), (GLsizei)values.size(), GL_FALSE, &values[0][0][0]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, std::vector<glm::mat2x3> values) {
		if (uniform.Type() == UniformVariable::UniformType::Mat2x3f) {
			glProgramUniformMatrix2x3fv(m_obj, uniform.Location().Value(), (GLsizei)values.size(), GL_FALSE, &values[0][0][0]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, std::vector<glm::mat3x2> values) {
		if (uniform.Type() == UniformVariable::UniformType::Mat3x2f) {
			glProgramUniformMatrix3x2fv(m_obj, uniform.Location().Value(), (GLsizei)values.size(), GL_FALSE, &values[0][0][0]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, std::vector<glm::mat2x4> values) {
		if (uniform.Type() == UniformVariable::UniformType::Mat2x4f) {
			glProgramUniformMatrix2x4fv(m_obj, uniform.Location().Value(), (GLsizei)values.size(), GL_FALSE, &values[0][0][0]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, std::vector<glm::mat4x2> values) {
		if (uniform.Type() == UniformVariable::UniformType::Mat4x2f) {
			glProgramUniformMatrix4x2fv(m_obj, uniform.Location().Value(), (GLsizei)values.size(), GL_FALSE, &values[0][0][0]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, std::vector<glm::mat3x4> values) {
		if (uniform.Type() == UniformVariable::UniformType::Mat3x4f) {
			glProgramUniformMatrix3x4fv(m_obj, uniform.Location().Value(), (GLsizei)values.size(), GL_FALSE, &values[0][0][0]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	void Program::SetUniform(UniformVariable uniform, std::vector<glm::mat4x3> values) {
		if (uniform.Type() == UniformVariable::UniformType::Mat4x3f) {
			glProgramUniformMatrix4x3fv(m_obj, uniform.Location().Value(), (GLsizei)values.size(), GL_FALSE, &values[0][0][0]);
		}
		else {
			throw std::exception("Uniform variable is not the correct type");
		}
	}

	/*************************************************************
	* Private Methods
	**************************************************************/

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

			GLint location = glGetProgramResourceLocation(m_obj, GL_PROGRAM_INPUT, name.c_str());

			AttributeVariable var(AttributeLocation(location), name, (AttributeVariable::AttribType)values[1]);
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

			GLint location = glGetProgramResourceLocation(m_obj, GL_UNIFORM, name.c_str());

			UniformVariable var(UniformLocation(location), name, (UniformVariable::UniformType)values[1]);
			m_uniformVariables.push_back(var);
		}
	}

}