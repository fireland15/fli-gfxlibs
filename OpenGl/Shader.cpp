#include "Shader.hpp"

#include "ShaderSource.hpp"
#include <OpenGLWrapper.hpp>

OpenGL::Shader::Shader(OpenGL::OpenGLWrapper& gl, std::unique_ptr<OpenGL::Handle> handle, OpenGL::ShaderType type)
	: _gl(gl), _handle(std::move(handle)), _type(type) { }

OpenGL::Shader::~Shader() {
	_gl.DeleteShader(std::move(_handle));
}

const OpenGL::Handle& OpenGL::Shader::Handle() {
	return *_handle;
}

const OpenGL::ShaderSource& OpenGL::Shader::Source() {
	throw std::exception("Not implemented");
}

OpenGL::ShaderType OpenGL::Shader::Type() {
	return _type;
}