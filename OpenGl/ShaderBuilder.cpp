#include "ShaderBuilder.hpp"

#include <vector>
#include <string>

#include <ShaderParameterEnum.hpp>
#include <SuccessEnum.hpp>

#include "ShaderCompilationException.hpp"
#include "Shader.hpp"

#include <OpenGLWrapper.hpp>

OpenGL::ShaderBuilder::ShaderBuilder(OpenGLWrapper & gl)
	: _gl(gl) { }

OpenGL::IShaderBuilder & OpenGL::ShaderBuilder::NewShader() {
	_sources.clear();
	_handle.reset();
	_type = ShaderType::Vertex;
	return *this;
}

OpenGL::IShaderBuilder & OpenGL::ShaderBuilder::Type(OpenGL::ShaderType type) {
	_type = type;
	return *this;
}

OpenGL::IShaderBuilder & OpenGL::ShaderBuilder::AddSource(OpenGL::ShaderSource source) {
	_sources.push_back(source);
	return *this;
}

OpenGL::IShaderBuilder & OpenGL::ShaderBuilder::Compile() {
	if (_sources.empty())
		throw OpenGL::ShaderCompilationException("No sources to compile");

	auto h = _gl.CreateShader(_type);

	for (auto & s : _sources) {
		_gl.ShaderSource(*h, s.Code());
	}

	_gl.CompileShader(*h);

	int success = _gl.GetShader(*h, OpenGL::ShaderParameter::CompileStatus);

	if (success == (int)OpenGL::Success::No) {
		int l = _gl.GetShader(*h, OpenGL::ShaderParameter::InfoLogLength);

		std::string err = _gl.GetShaderInfoLog(*h, l);

		_gl.DeleteShader(std::move(h));

		throw OpenGL::ShaderCompilationException(err);
	}

	_handle = std::move(h);

	return *this;
}

std::unique_ptr<OpenGL::IShader> OpenGL::ShaderBuilder::Build(){
	if (_handle->Value() != 0 && _handle->Type() == OpenGL::ObjectType::Shader)
		return std::unique_ptr<OpenGL::IShader>(new Shader(_gl, std::move(_handle), _type));
	else 
		return nullptr;
}