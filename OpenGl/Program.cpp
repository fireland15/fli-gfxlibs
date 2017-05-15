#include "Program.hpp"

#include <algorithm>
#include <set>

#include "Handle.hpp"
#include "AttributeVariable.hpp"
#include "UniformVariable.hpp"
#include "UniformNotFoundException.hpp"
#include "InvalidUniformAssignmentException.hpp"

#include <OpenGLWrapper.hpp>
#include <ResourcePropertyEnum.hpp>
#include <ProgramInterfaceEnum.hpp>
#include <TransposeEnum.hpp>
#include <AttributeTypeEnum.hpp>
#include <UniformTypeEnum.hpp>

void CheckUniformType(const OpenGL::UniformVariable & uniform, OpenGL::UniformType type);

bool CheckUniformType(const OpenGL::UniformVariable & uniform, std::set<OpenGL::UniformType> & types);

bool CheckUniformName(const OpenGL::UniformVariable & uniform, std::vector<OpenGL::UniformVariable> & uniforms);

OpenGL::Program::Program(OpenGL::OpenGLWrapper& gl, std::unique_ptr<Handle> h, std::vector<OpenGL::AttributeVariable> attributeVariables, std::vector<OpenGL::UniformVariable> uniformVariables) : _gl(gl), _attributeVariables(attributeVariables), _uniformVariables(uniformVariables) {
	if (h->Type() != OpenGL::ObjectType::Program)
		throw std::exception("Handle for incorrect object passed to program");
	
	_handle = std::move(h);
}

OpenGL::Program::~Program() {
	_gl.DeleteProgram(std::move(_handle));
}

void OpenGL::Program::Use() {
	_gl.UseProgram(*_handle);
}

void OpenGL::Program::StopUsing() {
	_gl.UseProgram(OpenGL::Handle::Default());
}

const OpenGL::AttributeVariable & OpenGL::Program::AttributeVariable(std::string & name) {
	for (auto & var : _attributeVariables) {
		if (var.Name() == name)
			return var;
	}
	throw std::exception("unable to find attribute variable by name");
}

const std::vector<OpenGL::AttributeVariable>& OpenGL::Program::AttributeVariables() {
	return _attributeVariables;
}

const OpenGL::UniformVariable & OpenGL::Program::UniformVariable(std::string & name) {
	for (auto & u : _uniformVariables) {
		if (u.Name() == name)
			return u;
	}
	throw OpenGL::UniformNotFoundException(name);
}

const std::vector<OpenGL::UniformVariable>& OpenGL::Program::UniformVariables() {
	return _uniformVariables;
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, float v) {
	VerifyUniform(uniform, OpenGL::UniformType::Float);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, glm::vec2& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Vec2f);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, glm::vec3& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Vec3f);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, glm::vec4& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Vec4f);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, int v) {
	//VerifyUniform(uniform, OpenGL::UniformType::Int);

	if (!(CheckUniformName(uniform, _uniformVariables) && CheckUniformType(uniform, std::set<OpenGL::UniformType>{ OpenGL::UniformType::Int, OpenGL::UniformType::Sampler2D }))) {
		throw OpenGL::InvalidUniformAssignmentException(uniform.Name(), uniform.Type(), OpenGL::UniformType::Int);
	}

	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, glm::ivec2& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Vec2i);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, glm::ivec3& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Vec3i);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, glm::ivec4& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Vec4i);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, unsigned int v) {
	VerifyUniform(uniform, OpenGL::UniformType::UnsignedInt);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, glm::uvec2& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Vec2u);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, glm::uvec3& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Vec3u);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, glm::uvec4& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Vec4u);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, std::vector<float>& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Float);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::vec2>& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Vec2f);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::vec3>& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Vec3f);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::vec4>& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Vec4f);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, std::vector<int>& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Int);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::ivec2>& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Vec2i);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::ivec3>& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Vec3i);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::ivec4>& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Vec4i);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, std::vector<unsigned int>& v) {
	VerifyUniform(uniform, OpenGL::UniformType::UnsignedInt);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::uvec2>& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Vec2u);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::uvec3>& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Vec3u);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::uvec4>& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Vec4u);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::mat2>& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Mat2f);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::mat3>& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Mat3f);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::mat4>& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Mat4f);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::mat2x3>& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Mat2x3f);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::mat3x2>& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Mat3x2f);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::mat2x4>& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Mat2x4f);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::mat4x2>& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Mat4x2f);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::mat3x4>& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Mat3x4f);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

void OpenGL::Program::SetUniform(const OpenGL::UniformVariable & uniform, std::vector<glm::mat4x3>& v) {
	VerifyUniform(uniform, OpenGL::UniformType::Mat4x3f);
	_gl.ProgramUniform(*_handle, uniform.Location(), v);
}

inline void OpenGL::Program::VerifyUniform(const OpenGL::UniformVariable & uniform, OpenGL::UniformType type) {
	bool exists = CheckUniformName(uniform, _uniformVariables);

	if (!exists)
		throw OpenGL::UniformNotFoundException(uniform.Name());

	CheckUniformType(uniform, type);
}

inline void CheckUniformType(const OpenGL::UniformVariable & uniform, OpenGL::UniformType type) {
	if (uniform.Type() != type)
		throw OpenGL::InvalidUniformAssignmentException(uniform.Name(), uniform.Type(), type);
}

bool CheckUniformType(const OpenGL::UniformVariable & uniform, std::set<OpenGL::UniformType> & types) {
	return types.count(uniform.Type()) != 0;
}

bool CheckUniformName(const OpenGL::UniformVariable & uniform, std::vector<OpenGL::UniformVariable> & uniforms) {
	for (auto & u : uniforms) {
		if (u.Name() == uniform.Name())
			return true;
	}
	return false;
}