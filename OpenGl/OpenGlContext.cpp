#include <glew.h>
#include "OpenGlContext.hpp"

#include <OpenGLWrapper.hpp>

#include "BufferBuilder.hpp"
#include "BufferDataBuilder.hpp"
#include <StateVariableEnum.hpp>
#include "ShaderBuilder.hpp"
#include "ProgramBuilder.hpp"
#include "VertexArray.hpp"
#include "TextureBuilder.hpp"

#include "ITexture.hpp"

OpenGL::OpenGlContext::OpenGlContext(OpenGL::OpenGLWrapper& gl)
	: _opengl(gl) { 
	_contextVersionMajor = _opengl.GetInteger(OpenGL::StateVariable::MajorVersion);
	_contextVersionMinor = _opengl.GetInteger(OpenGL::StateVariable::MinorVersion);
}

OpenGL::OpenGlContext::~OpenGlContext() { }

std::unique_ptr<OpenGL::IBuffer> OpenGL::OpenGlContext::NewBuffer(std::function<void(OpenGL::IBufferBuilder&)> func) {
	OpenGL::BufferDataBuilder dataBuilder;
	OpenGL::BufferBuilder builder(_opengl, dataBuilder);

	func(builder);

	return builder.Build();
}

int OpenGL::OpenGlContext::MajorVersion() {
	return _contextVersionMajor;
}

int OpenGL::OpenGlContext::MinorVersion() {
	return _contextVersionMinor;
}

void OpenGL::OpenGlContext::ResizeViewport(unsigned int width, unsigned int height) {
	_opengl.Viewport(glm::uvec2(0, 0), glm::uvec2(width, height));
}

std::unique_ptr<OpenGL::IShader> OpenGL::OpenGlContext::NewShader(std::function<void(OpenGL::IShaderBuilder&)> func) {
	ShaderBuilder builder(_opengl);

	func(builder);

	return builder.Compile().Build();
}

std::unique_ptr<OpenGL::IProgram> OpenGL::OpenGlContext::NewProgram(std::function<void(OpenGL::IProgramBuilder&)> func) {
	ProgramBuilder builder(_opengl);

	func(builder);
		
	return builder.Build();
}

std::unique_ptr<OpenGL::IVertexArray> OpenGL::OpenGlContext::NewVertexArray() {
	return std::unique_ptr<IVertexArray>(new VertexArray(_opengl, std::move(_opengl.GenVertexArray())));
}

std::unique_ptr<OpenGL::ITexture> OpenGL::OpenGlContext::NewTexture(std::function<void(OpenGL::ITextureBuilder&)> func) {
	TextureBuilder builder(_opengl);

	func(builder);

	return builder.Build();
}