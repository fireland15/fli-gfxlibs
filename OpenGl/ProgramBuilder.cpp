#include "ProgramBuilder.hpp"

#include <OpenGLWrapper.hpp>
#include "Handle.hpp"
#include "ProgramLinkException.hpp"
#include "Program.hpp"
#include <ProgramParametersEnum.hpp>
#include <ProgramInterfaceEnum.hpp>
#include <ResourcePropertyEnum.hpp>
#include <SuccessEnum.hpp>
#include <vector>

bool Link(OpenGL::OpenGLWrapper& gl, OpenGL::Handle& h);

void AttachShaders(OpenGL::OpenGLWrapper& gl, OpenGL::Handle& h, std::list<std::reference_wrapper<OpenGL::IShader>>& shaders);

void DetachShaders(OpenGL::OpenGLWrapper& gl, OpenGL::Handle& h, std::list<std::reference_wrapper<OpenGL::IShader>>& shaders);

std::string GetLinkErrors(OpenGL::OpenGLWrapper& gl, OpenGL::Handle& h);

std::vector<OpenGL::AttributeVariable> QueryForAttributeVariables(OpenGL::OpenGLWrapper& gl, OpenGL::Handle& h);

std::vector<OpenGL::UniformVariable> QueryForUniformVariables(OpenGL::OpenGLWrapper& gl, OpenGL::Handle& h);

OpenGL::ProgramBuilder::ProgramBuilder(OpenGL::OpenGLWrapper& gl)
	: _gl(gl) { }

OpenGL::ProgramBuilder::~ProgramBuilder() { }

OpenGL::IProgramBuilder& OpenGL::ProgramBuilder::NewProgram() {
	_shaders.clear();
	return *this;
}

OpenGL::IProgramBuilder& OpenGL::ProgramBuilder::Attach(IShader& shader) {
	_shaders.push_back(shader);
	return *this;
}

std::unique_ptr<OpenGL::IProgram> OpenGL::ProgramBuilder::Build() {
	if (_shaders.size() == 0)
		throw OpenGL::ProgramLinkException("No attached shaders to link");

	auto h = _gl.CreateProgram();

	AttachShaders(_gl, *h, _shaders);
	if (!Link(_gl, *h)) {
		std::string err = GetLinkErrors(_gl, *h);
		DetachShaders(_gl, *h, _shaders);
		_gl.DeleteProgram(std::move(h));
		throw OpenGL::ProgramLinkException(err);
	}

	DetachShaders(_gl, *h, _shaders);
	return std::unique_ptr<OpenGL::IProgram>(new OpenGL::Program(_gl, std::move(h), QueryForAttributeVariables(_gl, *h), QueryForUniformVariables(_gl, *h)));
}

bool Link(OpenGL::OpenGLWrapper& gl, OpenGL::Handle& h) {
	gl.LinkProgram(h);

	int linked = gl.GetProgram(h, OpenGL::ProgramParameters::LinkStatus);

	return linked == static_cast<int>(OpenGL::Success::Yes);
}

void AttachShaders(OpenGL::OpenGLWrapper& gl, OpenGL::Handle& h, std::list<std::reference_wrapper<OpenGL::IShader>>& shaders) {
	for (auto & shader : shaders) {
		gl.AttachShader(h, shader.get().Handle());
	}
}

void DetachShaders(OpenGL::OpenGLWrapper& gl, OpenGL::Handle& h, std::list<std::reference_wrapper<OpenGL::IShader>>& shaders) {
	for (auto & shader : shaders) {
		gl.DetachShader(h, shader.get().Handle());
	}
	shaders.clear();
}

std::string GetLinkErrors(OpenGL::OpenGLWrapper& gl, OpenGL::Handle& h) {
	int l = gl.GetProgram(h, OpenGL::ProgramParameters::InfoLogLength);

	return gl.GetProgramInfoLog(h, l);
}

std::vector<OpenGL::AttributeVariable> QueryForAttributeVariables(OpenGL::OpenGLWrapper& gl, OpenGL::Handle& h) {
	std::vector<OpenGL::AttributeVariable> attributeVariables;

	int numActiveAttribs = gl.GetProgramInterface(h, OpenGL::ProgramInterface::ProgramInput, OpenGL::ResourceProperty::ActiveResources);

	std::vector<char> nameData(256);
	std::vector<OpenGL::ResourceProperty> props;
	props.push_back(OpenGL::ResourceProperty::NameLength);
	props.push_back(OpenGL::ResourceProperty::Type);
	props.push_back(OpenGL::ResourceProperty::ArraySize);

	for (int i = 0; i < numActiveAttribs; i++) {
		auto values = gl.GetProgramResource(h, OpenGL::ProgramInterface::ProgramInput, i, props);
		
		std::string name = gl.GetProgramResourceName(h, OpenGL::ProgramInterface::ProgramInput, i, values[0]);

		int location = gl.GetProgramResourceLocation(h, OpenGL::ProgramInterface::ProgramInput, name);

		attributeVariables.emplace_back(location, name, static_cast<OpenGL::AttributeType>(values[1]));
	}

	return attributeVariables;
}

std::vector<OpenGL::UniformVariable> QueryForUniformVariables(OpenGL::OpenGLWrapper& gl, OpenGL::Handle& h) {
	std::vector<OpenGL::UniformVariable> uniformVariables;

	int numActiveUniforms = gl.GetProgramInterface(h, OpenGL::ProgramInterface::Uniform, OpenGL::ResourceProperty::ActiveResources);

	std::vector<char> nameData(256);
	std::vector<OpenGL::ResourceProperty> props;
	props.push_back(OpenGL::ResourceProperty::NameLength);
	props.push_back(OpenGL::ResourceProperty::Type);
	props.push_back(OpenGL::ResourceProperty::ArraySize);

	for (int i = 0; i < numActiveUniforms; i++) {
		auto values = gl.GetProgramResource(h, OpenGL::ProgramInterface::Uniform, i, props);
		
		std::string name = gl.GetProgramResourceName(h, OpenGL::ProgramInterface::Uniform, i, values[0]);

		GLint location = gl.GetProgramResourceLocation(h, OpenGL::ProgramInterface::Uniform, name);

		uniformVariables.emplace_back(location, name, static_cast<OpenGL::UniformType>(values[1]));
	}

	return uniformVariables;
}