#pragma once

#include <string>
#include <vector>

#include <glm\glm.hpp>

#include "IShader.hpp"
#include "AttributeVariable.hpp"
#include "UniformVariable.hpp"

namespace OpenGL {

	class IProgram {
	public:
		virtual ~IProgram() { }

		/// <summary>
		/// Makes this program the current program
		/// </summary>
		virtual void Use() = 0;

		/// <summary>
		/// Makes this program not the current program
		/// </summary>
		virtual void StopUsing() = 0;
	
		/// <summary>
		/// Gets an attribute variable by its name
		/// </summary>
		/// <param name="name">The name of the attribute</param>
		/// <returns>The attribute with the name</returns>
		/// <exception cref="AttributeNotFoundException"></exception>
		virtual const AttributeVariable& AttributeVariable(std::string& name) = 0;

		/// <summary>
		/// Gets the program's attribute variables
		/// </summary>
		/// <typeparam name="OpenGL::AttributeVariable"></typeparam>
		/// <returns>An array of the program's uniforms</returns>
		virtual const std::vector<OpenGL::AttributeVariable>& AttributeVariables() = 0;

		/// <summary>
		/// Gets a uniform by its name
		/// </summary>
		/// <param name="name">The name of the uniform</param>
		/// <returns>The uniform with the name</returns>
		/// <exception cref="UniformNotFoundException"></exception>
		virtual const UniformVariable& UniformVariable(std::string& name) = 0;

		/// <summary>
		/// Gets the programs uniform variables
		/// </summary>
		/// <typeparam name="OpenGL::UniformVariable"></typeparam>
		/// <returns>An array of the program's uniforms</returns>
		virtual const std::vector<OpenGL::UniformVariable>& UniformVariables() = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException">When the particular uniform cannot be found within this program</exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, float v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, glm::vec2& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, glm::vec3& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, glm::vec4& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, int v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, glm::ivec2& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, glm::ivec3& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, glm::ivec4& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, unsigned int v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, glm::uvec2& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, glm::uvec3& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, glm::uvec4& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, std::vector<float>& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, std::vector<glm::vec2>& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, std::vector<glm::vec3>& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, std::vector<glm::vec4>& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, std::vector<int>& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, std::vector<glm::ivec2>& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, std::vector<glm::ivec3>& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, std::vector<glm::ivec4>& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, std::vector<unsigned int>& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, std::vector<glm::uvec2>&v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, std::vector<glm::uvec3>&v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, std::vector<glm::uvec4>&v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, std::vector<glm::mat2>& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, std::vector<glm::mat3>& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, std::vector<glm::mat4>& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, std::vector<glm::mat2x3>& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, std::vector<glm::mat3x2>& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, std::vector<glm::mat2x4>& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, std::vector<glm::mat4x2>& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, std::vector<glm::mat3x4>& v) = 0;

		/// <summary>
		/// Sets the value of the uniform in the current program
		/// </summary>
		/// <param name="uniform">The uniform to send the data to</param>
		/// <param name="v">The data to pass to the uniform</param>
		/// <exception cref="UniformNotFoundException"></exception>
		/// <exception cref="InvalidUniformAssignmentException"></exception>
		virtual void SetUniform(const OpenGL::UniformVariable& uniform, std::vector<glm::mat4x3>& v) = 0;
	};

}