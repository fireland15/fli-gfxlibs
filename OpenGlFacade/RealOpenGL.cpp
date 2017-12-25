#include "RealOpenGL.hpp"

#include <glew.h>
#include <gl/GL.h>

#include <exception>

void OpenGL::RealOpenGL::GenBuffers(int n, unsigned int * buffers) {
	glGenBuffers(n, buffers);
}

void OpenGL::RealOpenGL::CreateBuffers(int n, unsigned int * buffers) {
	glCreateBuffers(n, buffers);
}

void OpenGL::RealOpenGL::DeleteBuffers(int n, const unsigned int * buffers) {
	glDeleteBuffers(n, buffers);
}

void OpenGL::RealOpenGL::BindBuffer(unsigned int target, unsigned int buffer) {
	glBindBuffer(target, buffer);
}

void OpenGL::RealOpenGL::BufferData(unsigned int target, ptrdiff_t size, const void * data, unsigned int usage) {
	glBufferData(target, size, data, usage);
}

void OpenGL::RealOpenGL::NamedBufferData(unsigned int buffer, ptrdiff_t size, const void * data, unsigned int usage) {
	glNamedBufferData(buffer, size, data, usage);
}

void OpenGL::RealOpenGL::Clear(unsigned int mask) {
	glClear(mask);
}

unsigned int OpenGL::RealOpenGL::GetError() {
	return glGetError();
}

void OpenGL::RealOpenGL::GetIntegerv(unsigned int pname, int * params) {
	glGetIntegerv(pname, params);
}

unsigned int OpenGL::RealOpenGL::CreateProgram() {
	return glCreateProgram();
}

void OpenGL::RealOpenGL::DetachShader(unsigned int program, unsigned int shader) {
	glDetachShader(program, shader);
}

void OpenGL::RealOpenGL::DeleteProgram(unsigned int program) {
	glDeleteProgram(program);
}

void OpenGL::RealOpenGL::AttachShader(unsigned int program, unsigned int shader) {
	glAttachShader(program, shader);
}

void OpenGL::RealOpenGL::UseProgram(unsigned int program) {
	glUseProgram(program);
}

void OpenGL::RealOpenGL::LinkProgram(unsigned int program) {
	glLinkProgram(program);
}

void OpenGL::RealOpenGL::GetProgramiv(unsigned int program, unsigned int pname, int * params) {
	glGetProgramiv(program, pname, params);
}

void OpenGL::RealOpenGL::GetProgramInfoLog(unsigned int program, int maxLength, int * length, char * infoLog) {
	glGetProgramInfoLog(program, maxLength, length, infoLog);
}

void OpenGL::RealOpenGL::ProgramUniform1f(unsigned int program, int location, float v0) {
	glProgramUniform1f(program, location, v0);
}

void OpenGL::RealOpenGL::ProgramUniform2f(unsigned int program, int location, float v0, float v1) {
	glProgramUniform2f(program, location, v0, v1);
}

void OpenGL::RealOpenGL::ProgramUniform3f(unsigned int program, int location, float v0, float v1, float v2) {
	glProgramUniform3f(program, location, v0, v1, v2);
}

void OpenGL::RealOpenGL::ProgramUniform4f(unsigned int program, int location, float v0, float v1, float v2, float v3) {
	glProgramUniform4f(program, location, v0, v1, v2, v3);
}

void OpenGL::RealOpenGL::ProgramUniform1i(unsigned int program, int location, int v0) {
	glProgramUniform1i(program, location, v0);
}

void OpenGL::RealOpenGL::ProgramUniform2i(unsigned int program, int location, int v0, int v1) {
	glProgramUniform2i(program, location, v0, v1);
}

void OpenGL::RealOpenGL::ProgramUniform3i(unsigned int program, int location, int v0, int v1, int v2) {
	glProgramUniform3i(program, location, v0, v1, v2);
}

void OpenGL::RealOpenGL::ProgramUniform4i(unsigned int program, int location, int v0, int v1, int v2, int v3) {
	glProgramUniform4i(program, location, v0, v1, v2, v3);
}

void OpenGL::RealOpenGL::ProgramUniform1ui(unsigned int program, int location, unsigned int v0) {
	glProgramUniform1ui(program, location, v0);
}

void OpenGL::RealOpenGL::ProgramUniform2ui(unsigned int program, int location, unsigned int v0, unsigned int v1) {
	glProgramUniform2ui(program, location, v0, v1);
}

void OpenGL::RealOpenGL::ProgramUniform3ui(unsigned int program, int location, unsigned int v0, unsigned int v1, unsigned int v2) {
	glProgramUniform3ui(program, location, v0, v1, v2);
}

void OpenGL::RealOpenGL::ProgramUniform4ui(unsigned int program, int location, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3) {
	glProgramUniform4ui(program, location, v0, v1, v2, v3);
}

void OpenGL::RealOpenGL::ProgramUniform1fv(unsigned int program, int location, int count, const float * value) {
	glProgramUniform1fv(program, location, count, value);
}

void OpenGL::RealOpenGL::ProgramUniform2fv(unsigned int program, int location, int count, const float * value) {
	glProgramUniform2fv(program, location, count, value);
}

void OpenGL::RealOpenGL::ProgramUniform3fv(unsigned int program, int location, int count, const float * value) {
	glProgramUniform3fv(program, location, count, value);
}

void OpenGL::RealOpenGL::ProgramUniform4fv(unsigned int program, int location, int count, const float * value) {
	glProgramUniform4fv(program, location, count, value);
}

void OpenGL::RealOpenGL::ProgramUniform1iv(unsigned int program, int location, int count, const int * value) {
	glProgramUniform1iv(program, location, count, value);
}

void OpenGL::RealOpenGL::ProgramUniform2iv(unsigned int program, int location, int count, const int * value) {
	glProgramUniform2iv(program, location, count, value);
}

void OpenGL::RealOpenGL::ProgramUniform3iv(unsigned int program, int location, int count, const int * value) {
	glProgramUniform3iv(program, location, count, value);
}

void OpenGL::RealOpenGL::ProgramUniform4iv(unsigned int program, int location, int count, const int * value) {
	glProgramUniform4iv(program, location, count, value);
}

void OpenGL::RealOpenGL::ProgramUniform1uiv(unsigned int program, int location, int count, const unsigned int * value) {
	glProgramUniform1uiv(program, location, count, value);
}

void OpenGL::RealOpenGL::ProgramUniform2uiv(unsigned int program, int location, int count, const unsigned int * value) {
	glProgramUniform2uiv(program, location, count, value);
}

void OpenGL::RealOpenGL::ProgramUniform3uiv(unsigned int program, int location, int count, const unsigned int * value) {
	glProgramUniform3uiv(program, location, count, value);
}

void OpenGL::RealOpenGL::ProgramUniform4uiv(unsigned int program, int location, int count, const unsigned int * value) {
	glProgramUniform4uiv(program, location, count, value);
}

void OpenGL::RealOpenGL::ProgramUniformMatrix2fv(unsigned int program, int location, int count, unsigned char transpose, const float * value) {
	glProgramUniformMatrix2fv(program, location, count, transpose, value);
}

void OpenGL::RealOpenGL::ProgramUniformMatrix3fv(unsigned int program, int location, int count, unsigned char transpose, const float * value) {
	glProgramUniformMatrix3fv(program, location, count, transpose, value);
}

void OpenGL::RealOpenGL::ProgramUniformMatrix4fv(unsigned int program, int location, int count, unsigned char transpose, const float * value) {
	glProgramUniformMatrix4fv(program, location, count, transpose, value);
}

void OpenGL::RealOpenGL::ProgramUniformMatrix2x3fv(unsigned int program, int location, int count, unsigned char transpose, const float * value) {
	glProgramUniformMatrix2x3fv(program, location, count, transpose, value);
}

void OpenGL::RealOpenGL::ProgramUniformMatrix3x2fv(unsigned int program, int location, int count, unsigned char transpose, const float * value) {
	glProgramUniformMatrix3x2fv(program, location, count, transpose, value);
}

void OpenGL::RealOpenGL::ProgramUniformMatrix2x4fv(unsigned int program, int location, int count, unsigned char transpose, const float * value) {
	glProgramUniformMatrix2x4fv(program, location, count, transpose, value);
}

void OpenGL::RealOpenGL::ProgramUniformMatrix4x2fv(unsigned int program, int location, int count, unsigned char transpose, const float * value) {
	glProgramUniformMatrix4x2fv(program, location, count, transpose, value);
}

void OpenGL::RealOpenGL::ProgramUniformMatrix3x4fv(unsigned int program, int location, int count, unsigned char transpose, const float * value) {
	glProgramUniformMatrix3x4fv(program, location, count, transpose, value);
}

void OpenGL::RealOpenGL::ProgramUniformMatrix4x3fv(unsigned int program, int location, int count, unsigned char transpose, const float * value) {
	glProgramUniformMatrix4x3fv(program, location, count, transpose, value);
}

void OpenGL::RealOpenGL::GetProgramInterfaceiv(unsigned int program, unsigned int programInterface, unsigned int pname, int * params) {
	glGetProgramInterfaceiv(program, programInterface, pname, params);
}

void OpenGL::RealOpenGL::GetProgramResourceiv(unsigned int program, unsigned int programInterface, unsigned int index, int propCount, const unsigned int * props, int bufSize, int * length, int * params) {
	glGetProgramResourceiv(program, programInterface, index, propCount, props, bufSize, length, params);
}

void OpenGL::RealOpenGL::GetProgramResourceName(unsigned int program, unsigned int programInterface, unsigned int index, int bufSize, int * length, char * name) {
	glGetProgramResourceName(program, programInterface, index, bufSize, length, name);
}

int OpenGL::RealOpenGL::GetProgramResourceLocation(unsigned int program, unsigned int programInterface, const char * name) {
	return glGetProgramResourceLocation(program, programInterface, name);
}

void OpenGL::RealOpenGL::ShaderSource(unsigned int shader, int count, const char ** string, const int * length) {
	glShaderSource(shader, count, string, length);
}

unsigned int OpenGL::RealOpenGL::CreateShader(unsigned int shaderType) {
	return glCreateShader(shaderType);
}

void OpenGL::RealOpenGL::DeleteShader(unsigned int shader) {
	glDeleteShader(shader);
}

void OpenGL::RealOpenGL::CompileShader(unsigned int shader) {
	glCompileShader(shader);
}

void OpenGL::RealOpenGL::GetShaderiv(unsigned int shader, unsigned int pname, int * params) {
	glGetShaderiv(shader, pname, params);
}

void OpenGL::RealOpenGL::GetShaderInfoLog(unsigned int shader, int maxLength, int * length, char * infoLog) {
	glGetShaderInfoLog(shader, maxLength, length, infoLog);
}

void OpenGL::RealOpenGL::DrawArraysInstanced(unsigned int mode, int first, int count, int primcount) {
	glDrawArraysInstanced(mode, first, count, primcount);
}

void OpenGL::RealOpenGL::DrawArrays(unsigned int mode, int first, int count) {
	glDrawArrays(mode, first, count);
}

void OpenGL::RealOpenGL::GenVertexArrays(int n, unsigned int * arrays) {
	glGenVertexArrays(n, arrays);
}

void OpenGL::RealOpenGL::DeleteVertexArrays(int n, const unsigned int * arrays) {
	glDeleteVertexArrays(n, arrays);
}

void OpenGL::RealOpenGL::EnableVertexAttribArray(unsigned int index) {
	glEnableVertexAttribArray(index);
}

void OpenGL::RealOpenGL::DisableVertexAttribArray(unsigned int index) {
	glDisableVertexAttribArray(index);
}

void OpenGL::RealOpenGL::EnableVertexArrayAttrib(unsigned int vaobj, unsigned int index) {
	glEnableVertexArrayAttrib(vaobj, index);
}

void OpenGL::RealOpenGL::DisableVertexArrayAttrib(unsigned int vaobj, unsigned int index) {
	glDisableVertexArrayAttrib(vaobj, index);
}

void OpenGL::RealOpenGL::VertexAttribPointer(unsigned int index, int size, unsigned int type, unsigned char normalized, int stride, const void * pointer) {
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void OpenGL::RealOpenGL::VertexAttribIPointer(unsigned int index, int size, unsigned int type, int stride, const void * pointer) {
	glVertexAttribIPointer(index, size, type, stride, pointer);
}

void OpenGL::RealOpenGL::VertexAttribLPointer(unsigned int index, int size, unsigned int type, int stride, const void * pointer) {
	glVertexAttribLPointer(index, size, type, stride, pointer);
}

void OpenGL::RealOpenGL::VertexAttribDivisor(unsigned int index, unsigned int divisor) {
	glVertexAttribDivisor(index, divisor);
}

void OpenGL::RealOpenGL::BindVertexArray(unsigned int array) {
	glBindVertexArray(array);
}

void OpenGL::RealOpenGL::ClearColor(float red, float green, float blue, float alpha) {
	glClearColor(red, green, blue, alpha);
}

void OpenGL::RealOpenGL::Viewport(int x, int y, int width, int height) {
	glViewport(x, y, width, height);
}

void OpenGL::RealOpenGL::VertexArrayBindVertexBuffer() {
	throw std::exception("Not Implemented");
}

void OpenGL::RealOpenGL::VertexArrayVertexAttribBinding() {
	throw std::exception("Not Implemented");
}

void OpenGL::RealOpenGL::VertexArrayVertexAttribDivisor() {
	throw std::exception("Not Implemented");
}

void OpenGL::RealOpenGL::GenTextures(int n, unsigned int * textures) {
	glGenTextures(n, textures);
}

void OpenGL::RealOpenGL::BindTexture(unsigned int target, unsigned int texture) {
	glBindTexture(target, texture);
}

void OpenGL::RealOpenGL::TexImage2D(unsigned int target, int level, int internalFormat, int width, int height, int border, unsigned int format, unsigned int type, const void * data) {
	glTexImage2D(
		static_cast<GLenum>(target),
		static_cast<GLint>(level),
		static_cast<GLint>(internalFormat),
		static_cast<GLsizei>(width),
		static_cast<GLsizei>(height),
		static_cast<GLint>(border),
		static_cast<GLenum>(format),
		static_cast<GLenum>(type),
		data
	);
}

void OpenGL::RealOpenGL::ActiveTexture(unsigned int texture) {
	glActiveTexture(static_cast<GLenum>(texture));
}

void OpenGL::RealOpenGL::GenerateMipmap(unsigned int target) {
	glGenerateMipmap(static_cast<GLenum>(target));
}

void OpenGL::RealOpenGL::GenerateTextureMipmap(unsigned int texture) {
	glGenerateTextureMipmap(static_cast<GLuint>(texture));
}

void OpenGL::RealOpenGL::Enable(unsigned int capability) {
	glEnable(static_cast<GLenum>(capability));
}

void OpenGL::RealOpenGL::Disable(unsigned int capability) {
	glDisable(static_cast<GLenum>(capability));
}

void OpenGL::RealOpenGL::TexParameteri(unsigned int target, unsigned int pname, int param) {
	glTexParameteri(
		static_cast<GLenum>(target),
		static_cast<GLenum>(pname),
		static_cast<GLint>(param)
	);
}