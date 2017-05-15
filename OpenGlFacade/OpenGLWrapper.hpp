#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>

#include "Handle.hpp"
#include "BufferTargetEnum.hpp"
#include "BufferUsageEnum.hpp"
#include "BuffersEnum.hpp"
#include "ErrorEnum.hpp"
#include "StateVariableEnum.hpp"
#include "ProgramParametersEnum.hpp"
#include "ShaderVariableLocation.hpp"
#include "ShaderParameterEnum.hpp"
#include "ProgramInterfaceEnum.hpp"
#include "ResourcePropertyEnum.hpp"
#include "TextureTargetEnum.hpp"
#include "TextureInternalFormatEnum.hpp"
#include "TexturePixelTypeEnum.hpp"
#include "TextureParameterEnum.hpp"
#include "TextureParameterValueEnum.hpp"
#include "ShaderTypeEnum.hpp"
#include "PrimitiveTypes.hpp"
#include "DataTypesEnum.hpp"
#include "NormalizeEnum.hpp"

namespace OpenGL {

	class IOpenGL;

	class OpenGLWrapper {
	public:
		OpenGLWrapper(IOpenGL& gl);
		IOpenGL & Raw();
		std::unique_ptr<Handle> GenBuffer();
		void DeleteBuffer(std::unique_ptr<Handle> h);
		void BindBuffer(BufferTarget target, const Handle & h);
		void BufferData(BufferTarget target, const std::vector<unsigned char>& data, BufferUsage usage);
		void NamedBufferData(const Handle & h, const std::vector<unsigned char> & data, BufferUsage usage);
		void ClearColor(const glm::vec4 & color);
		void Clear(std::vector<Buffers> buffers);
		Error GetError();
		int GetInteger(StateVariable variable);
		std::unique_ptr<Handle> CreateProgram();
		void DeleteProgram(std::unique_ptr<Handle> h);
		void AttachShader(const Handle & program, const Handle & shader);
		void DetachShader(const Handle & program, const Handle & shader);
		void UseProgram(const Handle & h);
		void LinkProgram(const Handle & h);
		int GetProgram(const Handle & h, ProgramParameters pname);
		std::string GetProgramInfoLog(const Handle & h, int maxLength);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, float v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const glm::vec2 & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const glm::vec3 & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const glm::vec4 & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, int v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const glm::ivec2 & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const glm::ivec3 & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const glm::ivec4 & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, unsigned int v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const glm::uvec2 & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const glm::uvec3 & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const glm::uvec4 & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const std::vector<float> & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const std::vector<glm::vec2> & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const std::vector<glm::vec3> & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const std::vector<glm::vec4> & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const std::vector<int> & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const std::vector<glm::ivec2> & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const std::vector<glm::ivec3> & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const std::vector<glm::ivec4> & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const std::vector<unsigned int> & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const std::vector<glm::uvec2> & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const std::vector<glm::uvec3> & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const std::vector<glm::uvec4> & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const std::vector<glm::mat2> & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const std::vector<glm::mat3> & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const std::vector<glm::mat4> & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const std::vector<glm::mat2x3> & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const std::vector<glm::mat3x2> & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const std::vector<glm::mat2x4> & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const std::vector<glm::mat4x2> & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const std::vector<glm::mat3x4> & v);
		void ProgramUniform(const Handle & h, ShaderVariableLocation loc, const std::vector<glm::mat4x3> & v);
		int GetProgramInterface(const Handle & h, ProgramInterface i, ResourceProperty param);
		std::vector<int> GetProgramResource(const Handle & h, ProgramInterface i, unsigned int index, std::vector<ResourceProperty>& props);
		std::string GetProgramResourceName(const Handle & h, ProgramInterface i, unsigned int index, int nameLength);
		int GetProgramResourceLocation(const Handle & h, ProgramInterface i, const std::string & name);
		void ShaderSource(const Handle & h, const std::string & source);
		std::unique_ptr<Handle> CreateShader(ShaderType type);
		void DeleteShader(std::unique_ptr<Handle> h);
		void CompileShader(const Handle & h);
		int GetShader(const Handle & h, ShaderParameter param);
		std::string GetShaderInfoLog(const Handle & h, unsigned int maxLength = 256);
		void DrawArraysInstanced(PrimitiveType mode, int startingIndex, int count, int primCount);
		void DrawArrays(PrimitiveType mode, int startingIndex, int count);
		std::unique_ptr<Handle> GenVertexArray();
		void DeleteVertexArray(std::unique_ptr<Handle> h);
		void EnableVertexAttribArray(unsigned int index);
		void DisableVertexAttribArray(unsigned int index);
		void EnableVertexArrayAttrib(const Handle & h, unsigned int index);
		void DisableVertexArrayAttrib(const Handle & h, unsigned int index);
		void VertexAttribPointer(unsigned int index, int size, DataType type, Normalize normalize, int stride, int offset);
		void VertexAttribIPointer(unsigned int index, int size, DataType type, int stride, int offset);
		void VertexAttribLPointer(unsigned int index, int size, DataType type, int stride, int offset);
		void VertexAttribDivisor(unsigned int index, unsigned int divisor);
		void BindVertexArray(const Handle & h);
		void Viewport(const glm::uvec2 & pos, const glm::uvec2 & dim);
		std::unique_ptr<Handle> GenTexture();
		void BindTexture(TextureTarget target, const Handle & h);
		void TexImage2D(TextureTarget target, int level, TextureInternalFormat internalFormat, glm::ivec2 dim, TexturePixelType format, DataType type, const void* data);
		void TexParameter(TextureTarget target, TextureParameter param, TextureParameterValue value);
		void TexParameter(TextureTarget target, TextureParameter param, int value);
		void GenerateMipmap(TextureTarget target);
		void GenerateTextureMipmap(const Handle& h);
		void ActiveTexture(unsigned int slot);
	private:
		IOpenGL& _gl;
	};

}