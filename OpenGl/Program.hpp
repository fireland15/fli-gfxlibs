#pragma once

#include <memory>
#include <list>

#include "IProgram.hpp"

namespace OpenGL {

	class AttributeVariable;
	class UniformVariable;
	class Handle;
	class OpenGLWrapper;

	class Program : public IProgram {
	public:
		Program(OpenGLWrapper& gl, std::unique_ptr<Handle> h, std::vector<OpenGL::AttributeVariable> attributeVariables, std::vector<OpenGL::UniformVariable> uniformVariables);

		virtual ~Program();

		virtual void Use() override;

		virtual void StopUsing() override;

		virtual const OpenGL::AttributeVariable & AttributeVariable(std::string & name) override;

		virtual const std::vector<OpenGL::AttributeVariable>& AttributeVariables() override;

		virtual const OpenGL::UniformVariable & UniformVariable(std::string & name) override;

		virtual const std::vector<OpenGL::UniformVariable>& UniformVariables() override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, float v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, glm::vec2& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, glm::vec3& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, glm::vec4& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, int v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, glm::ivec2& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, glm::ivec3& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, glm::ivec4& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, unsigned int v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, glm::uvec2& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, glm::uvec3& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, glm::uvec4& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, std::vector<float>& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::vec2>& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::vec3>& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::vec4>& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, std::vector<int>& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::ivec2>& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::ivec3>& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::ivec4>& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, std::vector<unsigned int>& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::uvec2>& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::uvec3>& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::uvec4>& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::mat2>& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::mat3>& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::mat4>& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::mat2x3>& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::mat3x2>& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::mat2x4>& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::mat4x2>& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::mat3x4>& v) override;

		virtual void SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::mat4x3>& v) override;

	private:
		OpenGLWrapper& _gl;
		std::unique_ptr<Handle> _handle;
		std::list<IShader*> _attachedShaders;
		std::vector<OpenGL::AttributeVariable> _attributeVariables;
		std::vector<OpenGL::UniformVariable> _uniformVariables;

		void QueryForAttributeVariables();
		void QueryForUniformVariables();
		void VerifyUniform(const OpenGL::UniformVariable& uniform, OpenGL::UniformType type);
	};

}