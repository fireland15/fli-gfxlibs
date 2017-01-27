#pragma once

#include <vector>
#include <string>

#include <glew\glew.h>
#include <GL\GL.h>

#include <glm\glm.hpp>

#include "shader.hpp"
#include "attribute_variable.hpp"
#include "uniform_variable.hpp"

namespace opengl {

	class Program {
	private:
		Program(GLuint obj);

		GLuint Obj();

		void Obj(GLuint obj);

		void QueryForAttributeVariables();

		void QueryForUniformVariables();

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

		void SetUniform(UniformVariable uniform, float value);

		void SetUniform(UniformVariable uniform, glm::vec2 value);

		void SetUniform(UniformVariable uniform, glm::vec3 value);

		void SetUniform(UniformVariable uniform, glm::vec4 value);

		void SetUniform(UniformVariable uniform, int value);

		void SetUniform(UniformVariable uniform, glm::ivec2 value);

		void SetUniform(UniformVariable uniform, glm::ivec3 value);

		void SetUniform(UniformVariable uniform, glm::ivec4 value);

		void SetUniform(UniformVariable uniform, unsigned int value);

		void SetUniform(UniformVariable uniform, glm::uvec2 value);

		void SetUniform(UniformVariable uniform, glm::uvec3 value);

		void SetUniform(UniformVariable uniform, glm::uvec4 value);

		void SetUniform(UniformVariable uniform, std::vector<float> values);

		void SetUniform(UniformVariable uniform, std::vector<glm::vec2> values);

		void SetUniform(UniformVariable uniform, std::vector<glm::vec3> values);

		void SetUniform(UniformVariable uniform, std::vector<glm::vec4> values);

		void SetUniform(UniformVariable uniform, std::vector<int> values);

		void SetUniform(UniformVariable uniform, std::vector<glm::ivec2> values);

		void SetUniform(UniformVariable uniform, std::vector<glm::ivec3> values);

		void SetUniform(UniformVariable uniform, std::vector<glm::ivec4> values);

		void SetUniform(UniformVariable uniform, std::vector<unsigned int> values);

		void SetUniform(UniformVariable uniform, std::vector<glm::uvec2> values);

		void SetUniform(UniformVariable uniform, std::vector<glm::uvec3> values);

		void SetUniform(UniformVariable uniform, std::vector<glm::uvec4> values);

		void SetUniform(UniformVariable uniform, std::vector<glm::mat2> values);

		void SetUniform(UniformVariable uniform, std::vector<glm::mat3> values);

		void SetUniform(UniformVariable uniform, std::vector<glm::mat4> values);

		void SetUniform(UniformVariable uniform, std::vector<glm::mat2x3> values);

		void SetUniform(UniformVariable uniform, std::vector<glm::mat3x2> values);

		void SetUniform(UniformVariable uniform, std::vector<glm::mat2x4> values);

		void SetUniform(UniformVariable uniform, std::vector<glm::mat4x2> values);

		void SetUniform(UniformVariable uniform, std::vector<glm::mat3x4> values);

		void SetUniform(UniformVariable uniform, std::vector<glm::mat4x3> values);

		friend class GL;

	private:
		GLuint m_obj;

		bool m_hasErrors;

		std::string m_errors;

		std::vector<AttributeVariable> m_attributeVariables;

		std::vector<UniformVariable> m_uniformVariables;
	};

}