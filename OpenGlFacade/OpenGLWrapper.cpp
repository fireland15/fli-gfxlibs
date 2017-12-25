#include "OpenGLWrapper.hpp"

#include "IOpenGL.hpp"
#include "TransposeEnum.hpp"

#include <glm\gtc\type_ptr.hpp>

OpenGL::OpenGLWrapper::OpenGLWrapper(IOpenGL& gl) : _gl(gl) { }

OpenGL::IOpenGL & OpenGL::OpenGLWrapper::Raw() {
	return _gl;
}

std::unique_ptr<OpenGL::Handle> OpenGL::OpenGLWrapper::GenBuffer() {
	unsigned int h;
	_gl.GenBuffers(1, &h);
	return std::unique_ptr<OpenGL::Handle>(new Handle(OpenGL::ObjectType::Buffer, h));
}

void OpenGL::OpenGLWrapper::DeleteBuffer(std::unique_ptr<OpenGL::Handle> h) {
	unsigned int hh = h->Value();
	_gl.DeleteBuffers(1, &hh);
}

void OpenGL::OpenGLWrapper::BindBuffer(OpenGL::BufferTarget target, const OpenGL::Handle & h) {
	_gl.BindBuffer(static_cast<unsigned int>(target), h.Value());
}

void OpenGL::OpenGLWrapper::BufferData(OpenGL::BufferTarget target, const std::vector<unsigned char>& data, OpenGL::BufferUsage usage) {
	_gl.BufferData(static_cast<unsigned int>(target), data.size(), data.data(), static_cast<unsigned int>(usage));
}

void OpenGL::OpenGLWrapper::NamedBufferData(const OpenGL::Handle & h, const std::vector<unsigned char> & data, BufferUsage usage) {
	_gl.NamedBufferData(h.Value(), data.size(), data.data(), static_cast<unsigned int>(usage));
}

void OpenGL::OpenGLWrapper::ClearColor(const glm::vec4 & color) {
	_gl.ClearColor(color.r, color.g, color.b, color.a);
}

void OpenGL::OpenGLWrapper::Clear(std::vector<OpenGL::Buffers> buffers) {
	unsigned int b = static_cast<unsigned int>(buffers.front());
	for (auto buf : buffers)
		b |= static_cast<unsigned int>(buf);
	_gl.Clear(b);
}

OpenGL::Error OpenGL::OpenGLWrapper::GetError() {
	return static_cast<OpenGL::Error>(_gl.GetError());
}

int OpenGL::OpenGLWrapper::GetInteger(OpenGL::StateVariable variable) {
	int v = 0;
	_gl.GetIntegerv(static_cast<unsigned int>(variable), &v);
	return v;
}

std::unique_ptr<OpenGL::Handle> OpenGL::OpenGLWrapper::CreateProgram() {
	return std::unique_ptr<OpenGL::Handle>(new OpenGL::Handle(OpenGL::ObjectType::Program, _gl.CreateProgram()));
}

void OpenGL::OpenGLWrapper::DeleteProgram(std::unique_ptr<OpenGL::Handle> h) {
	_gl.DeleteProgram(h->Value());
}

void OpenGL::OpenGLWrapper::AttachShader(const OpenGL::Handle & program, const OpenGL::Handle & shader) {
	_gl.AttachShader(program.Value(), shader.Value());
}

void OpenGL::OpenGLWrapper::DetachShader(const OpenGL::Handle & program, const OpenGL::Handle & shader) {
	_gl.DetachShader(program.Value(), shader.Value());
}

void OpenGL::OpenGLWrapper::UseProgram(const OpenGL::Handle & h) {
	_gl.UseProgram(h.Value());
}

void OpenGL::OpenGLWrapper::LinkProgram(const OpenGL::Handle & h) {
	_gl.LinkProgram(h.Value());
}

int OpenGL::OpenGLWrapper::GetProgram(const OpenGL::Handle & h, OpenGL::ProgramParameters pname) {
	int params;
	_gl.GetProgramiv(
		h.Value(), 
		static_cast<unsigned int>(pname), 
		static_cast<int*>(&params));
	return params;
}

std::string OpenGL::OpenGLWrapper::GetProgramInfoLog(const OpenGL::Handle & h, int maxLength) {
	std::vector<char> log(maxLength);
	auto p = &(maxLength);
	_gl.GetProgramInfoLog(static_cast<unsigned int>(h.Value()), maxLength, p, log.data());

	return std::string(log.data(), log.size());
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, OpenGL::ShaderVariableLocation loc, float v) {
	_gl.ProgramUniform1f(
		h.Value(), 
		static_cast<int>(loc.Value()), 
		v);
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, ShaderVariableLocation loc, const glm::vec2 & v) {
	_gl.ProgramUniform2f(
		h.Value(), 
		static_cast<int>(loc.Value()), 
		v[0], v[1]);
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, ShaderVariableLocation loc, const glm::vec3 & v) {
	_gl.ProgramUniform3f(
		h.Value(), 
		static_cast<int>(loc.Value()), 
		v[0], v[1], v[2]);
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, ShaderVariableLocation loc, const glm::vec4 & v) {
	_gl.ProgramUniform4f(
		h.Value(), 
		static_cast<int>(loc.Value()), 
		v[0], 
		v[1], 
		v[2], 
		v[3]);
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, OpenGL::ShaderVariableLocation loc, int v) {
	_gl.ProgramUniform1i(
		h.Value(), 
		static_cast<GLint>(loc.Value()), 
		v);
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, ShaderVariableLocation loc, const glm::ivec2 & v) {
	_gl.ProgramUniform2i(
		h.Value(), 
		static_cast<int>(loc.Value()), 
		v[0], v[1]);
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, ShaderVariableLocation loc, const glm::ivec3 & v) {
	_gl.ProgramUniform3i(
		h.Value(), 
		static_cast<int>(loc.Value()), 
		v[0], v[1], v[2]);
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, ShaderVariableLocation loc, const glm::ivec4 & v) {
	_gl.ProgramUniform4i(
		h.Value(), 
		static_cast<int>(loc.Value()), 
		v[0], v[1], v[2], v[3]);
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, OpenGL::ShaderVariableLocation loc, unsigned int v) {
	_gl.ProgramUniform1ui(
		h.Value(), 
		static_cast<int>(loc.Value()), 
		v);
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, ShaderVariableLocation loc, const glm::uvec2 & v) {
	_gl.ProgramUniform2ui(
		h.Value(), 
		static_cast<int>(loc.Value()),
		v[0], v[1]);
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, ShaderVariableLocation loc, const glm::uvec3 & v) {
	_gl.ProgramUniform3ui(
		h.Value(), 
		static_cast<int>(loc.Value()), 
		v[0], v[1], v[2]);
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, ShaderVariableLocation loc, const glm::uvec4 & v) {
	_gl.ProgramUniform4ui(
		h.Value(), 
		static_cast<GLint>(loc.Value()), 
		v[0], v[1], v[2], v[3]);
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, OpenGL::ShaderVariableLocation loc, const std::vector<float> & v) {
	_gl.ProgramUniform1fv(
		h.Value(),
		static_cast<int>(loc.Value()),
		static_cast<int>(v.size()),
		v.data());
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, OpenGL::ShaderVariableLocation loc, const std::vector<glm::vec2> & v) {
	_gl.ProgramUniform2fv(
		h.Value(),
		static_cast<int>(loc.Value()),
		static_cast<int>(v.size()),
		glm::value_ptr(v.front()));
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, OpenGL::ShaderVariableLocation loc, const std::vector<glm::vec3> & v) {
	_gl.ProgramUniform3fv(
		h.Value(),
		static_cast<int>(loc.Value()),
		static_cast<int>(v.size()),
		glm::value_ptr(v.front()));
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, OpenGL::ShaderVariableLocation loc, const std::vector<glm::vec4> & v) {
	_gl.ProgramUniform4fv(
		h.Value(),
		static_cast<int>(loc.Value()),
		static_cast<int>(v.size()),
		glm::value_ptr(v.front()));
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, OpenGL::ShaderVariableLocation loc, const std::vector<int> & v) {
	_gl.ProgramUniform1iv(
		h.Value(),
		static_cast<int>(loc.Value()),
		static_cast<int>(v.size()),
		v.data());
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, OpenGL::ShaderVariableLocation loc, const std::vector<glm::ivec2> & v) {
	_gl.ProgramUniform2iv(
		h.Value(),
		static_cast<int>(loc.Value()),
		static_cast<int>(v.size()),
		glm::value_ptr(v.front()));
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, OpenGL::ShaderVariableLocation loc, const std::vector<glm::ivec3> & v) {
	_gl.ProgramUniform3iv(
		h.Value(),
		static_cast<int>(loc.Value()),
		static_cast<int>(v.size()),
		glm::value_ptr(v.front()));
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, OpenGL::ShaderVariableLocation loc, const std::vector<glm::ivec4> & v) {
	_gl.ProgramUniform4iv(
		h.Value(),
		static_cast<int>(loc.Value()),
		static_cast<int>(v.size()),
		glm::value_ptr(v.front()));
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, OpenGL::ShaderVariableLocation loc, const std::vector<unsigned int> & v) {
	_gl.ProgramUniform1uiv(
		h.Value(),
		static_cast<int>(loc.Value()),
		static_cast<int>(v.size()),
		v.data());
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, OpenGL::ShaderVariableLocation loc, const std::vector<glm::uvec2> & v) {
	_gl.ProgramUniform2uiv(
		h.Value(),
		static_cast<int>(loc.Value()),
		static_cast<int>(v.size()),
		glm::value_ptr(v.front()));
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, OpenGL::ShaderVariableLocation loc, const std::vector<glm::uvec3> & v) {
	_gl.ProgramUniform3uiv(
		h.Value(),
		static_cast<int>(loc.Value()),
		static_cast<int>(v.size()),
		glm::value_ptr(v.front()));
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, OpenGL::ShaderVariableLocation loc, const std::vector<glm::uvec4> & v) {
	_gl.ProgramUniform4uiv(
		h.Value(),
		static_cast<int>(loc.Value()),
		static_cast<int>(v.size()),
		glm::value_ptr(v.front()));
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, OpenGL::ShaderVariableLocation loc, const std::vector<glm::mat2> & v) {
	_gl.ProgramUniformMatrix2fv(
		h.Value(),
		static_cast<int>(loc.Value()),
		static_cast<int>(v.size()),
		static_cast<unsigned char>(OpenGL::Transpose::No),
		glm::value_ptr(v.front()));
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, OpenGL::ShaderVariableLocation loc, const std::vector<glm::mat3> & v) {
	_gl.ProgramUniformMatrix3fv(
		h.Value(),
		static_cast<int>(loc.Value()),
		static_cast<int>(v.size()),
		static_cast<unsigned char>(OpenGL::Transpose::No),
		glm::value_ptr(v.front()));
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, OpenGL::ShaderVariableLocation loc, const std::vector<glm::mat4> & v) {
	_gl.ProgramUniformMatrix4fv(
		h.Value(),
		static_cast<int>(loc.Value()),
		static_cast<int>(v.size()),
		static_cast<unsigned char>(OpenGL::Transpose::No),
		glm::value_ptr(v.front()));
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, OpenGL::ShaderVariableLocation loc, const std::vector<glm::mat2x3> & v) {
	_gl.ProgramUniformMatrix2x3fv(
		h.Value(),
		static_cast<int>(loc.Value()),
		static_cast<int>(v.size()),
		static_cast<unsigned char>(OpenGL::Transpose::No),
		glm::value_ptr(v.front()));
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, OpenGL::ShaderVariableLocation loc, const std::vector<glm::mat3x2> & v) {
	_gl.ProgramUniformMatrix3x2fv(
		h.Value(),
		static_cast<int>(loc.Value()),
		static_cast<int>(v.size()),
		static_cast<unsigned char>(OpenGL::Transpose::No),
		glm::value_ptr(v.front()));
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, OpenGL::ShaderVariableLocation loc, const std::vector<glm::mat2x4> & v) {
	_gl.ProgramUniformMatrix2x4fv(
		h.Value(),
		static_cast<int>(loc.Value()),
		static_cast<int>(v.size()),
		static_cast<unsigned char>(OpenGL::Transpose::No),
		glm::value_ptr(v.front()));
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, OpenGL::ShaderVariableLocation loc, const std::vector<glm::mat4x2> & v) {
	_gl.ProgramUniformMatrix4x2fv(
		h.Value(),
		static_cast<int>(loc.Value()),
		static_cast<int>(v.size()),
		static_cast<unsigned char>(OpenGL::Transpose::No),
		glm::value_ptr(v.front()));
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, OpenGL::ShaderVariableLocation loc, const std::vector<glm::mat3x4> & v) {
	_gl.ProgramUniformMatrix3x4fv(
		h.Value(),
		static_cast<int>(loc.Value()),
		static_cast<int>(v.size()),
		static_cast<unsigned char>(OpenGL::Transpose::No),
		glm::value_ptr(v.front()));
}

void OpenGL::OpenGLWrapper::ProgramUniform(const OpenGL::Handle & h, OpenGL::ShaderVariableLocation loc, const std::vector<glm::mat4x3> & v) {
	_gl.ProgramUniformMatrix4x3fv(
		h.Value(),
		static_cast<int>(loc.Value()),
		static_cast<int>(v.size()),
		static_cast<unsigned char>(OpenGL::Transpose::No),
		glm::value_ptr(v.front()));
}

int OpenGL::OpenGLWrapper::GetProgramInterface(const OpenGL::Handle & h, OpenGL::ProgramInterface i, OpenGL::ResourceProperty param) {
	int res;
	_gl.GetProgramInterfaceiv(
		h.Value(),
		static_cast<unsigned int>(i),
		static_cast<unsigned int>(param),
		static_cast<int*>(&res));
	return res;
}

std::vector<int> OpenGL::OpenGLWrapper::GetProgramResource(const OpenGL::Handle & h, OpenGL::ProgramInterface i, unsigned int index, std::vector<OpenGL::ResourceProperty> & props) {
	static_assert(std::is_same<unsigned int, std::underlying_type<OpenGL::ResourceProperty>::type>::value, "error");

	std::vector<int> res(props.size());
	int l;
	_gl.GetProgramResourceiv(
		h.Value(),
		static_cast<unsigned int>(i),
		index,
		static_cast<int>(props.size()),
		reinterpret_cast<unsigned int*>(props.data()),
		static_cast<int>(res.size()),
		static_cast<int*>(&l),
		static_cast<int*>(res.data()));
	return res;
}

std::string OpenGL::OpenGLWrapper::GetProgramResourceName(const OpenGL::Handle & h, OpenGL::ProgramInterface i, unsigned int index, int nameLength) {
	std::vector<char> nameData(nameLength);
	_gl.GetProgramResourceName(
		h.Value(),
		static_cast<unsigned int>(i),
		index,
		static_cast<int>(nameData.size()),
		nullptr,
		nameData.data());
	return std::string(nameData.data(), nameData.size() - 1);
}

int OpenGL::OpenGLWrapper::GetProgramResourceLocation(const OpenGL::Handle & h, OpenGL::ProgramInterface i, const std::string & name) {
	return _gl.GetProgramResourceLocation(
		h.Value(),
		static_cast<unsigned int>(i),
		name.c_str());
}

void OpenGL::OpenGLWrapper::ShaderSource(const OpenGL::Handle & h, const std::string & source) {
	const char* c = source.c_str();
	int l = source.size();

	_gl.ShaderSource(h.Value(), 1, &c, &l);
}

std::unique_ptr<OpenGL::Handle> OpenGL::OpenGLWrapper::CreateShader(OpenGL::ShaderType type) {
	return std::unique_ptr<OpenGL::Handle>(new Handle(OpenGL::ObjectType::Shader, _gl.CreateShader(static_cast<unsigned int>(type))));
}

void OpenGL::OpenGLWrapper::DeleteShader(std::unique_ptr<OpenGL::Handle> h) {
	_gl.DeleteShader(h->Value());
}

void OpenGL::OpenGLWrapper::CompileShader(const OpenGL::Handle & h) {
	_gl.CompileShader(h.Value());
}

int OpenGL::OpenGLWrapper::GetShader(const OpenGL::Handle & h, OpenGL::ShaderParameter param) {
	int res;
	_gl.GetShaderiv(
		h.Value(),
		static_cast<unsigned int>(param),
		&res);
	return res;
}

std::string OpenGL::OpenGLWrapper::GetShaderInfoLog(const OpenGL::Handle & h, unsigned int maxLength) {
	std::vector<char> d(maxLength);
	_gl.GetShaderInfoLog(
		h.Value(),
		static_cast<int>(d.size()),
		nullptr,
		d.data());
	return std::string(d.data(), d.size());
}

void OpenGL::OpenGLWrapper::DrawArraysInstanced(OpenGL::PrimitiveType mode, int startingIndex, int count, int primCount) {
	_gl.DrawArraysInstanced(
		static_cast<unsigned int>(mode),
		startingIndex,
		count,
		primCount);
}

void OpenGL::OpenGLWrapper::DrawArrays(OpenGL::PrimitiveType mode, int startingIndex, int count) {
	_gl.DrawArrays(
		static_cast<unsigned int>(mode),
		startingIndex,
		count);
}

std::unique_ptr<OpenGL::Handle> OpenGL::OpenGLWrapper::GenVertexArray() {
	unsigned int h = 0;
	_gl.GenVertexArrays(1, &h);
	return std::unique_ptr<OpenGL::Handle>(new OpenGL::Handle(OpenGL::ObjectType::VertexArray, h));
}

void OpenGL::OpenGLWrapper::DeleteVertexArray(std::unique_ptr<OpenGL::Handle> h) {
	const unsigned int hh = h->Value();
	_gl.DeleteVertexArrays(1, &hh);
}

void OpenGL::OpenGLWrapper::EnableVertexAttribArray(unsigned int index) {
	_gl.EnableVertexAttribArray(index);
}

void OpenGL::OpenGLWrapper::DisableVertexAttribArray(unsigned int index) {
	_gl.DisableVertexAttribArray(index);
}

void OpenGL::OpenGLWrapper::EnableVertexArrayAttrib(const OpenGL::Handle & h, unsigned int index) {
	_gl.EnableVertexArrayAttrib(
		h.Value(),
		index);
}

void OpenGL::OpenGLWrapper::DisableVertexArrayAttrib(const OpenGL::Handle & h, unsigned int index) {
	_gl.DisableVertexArrayAttrib(
		h.Value(),
		index);
}

void OpenGL::OpenGLWrapper::VertexAttribPointer(unsigned int index, int size, OpenGL::DataType type, OpenGL::Normalize normalize, int stride, int offset) {
	_gl.VertexAttribPointer(
		index,
		size,
		static_cast<unsigned int>(type),
		static_cast<unsigned char>(normalize),
		stride,
		static_cast<const GLvoid*>(static_cast<char*>(0) + offset));
}

void OpenGL::OpenGLWrapper::VertexAttribIPointer(unsigned int index, int size, OpenGL::DataType type, int stride, int offset) {
	_gl.VertexAttribIPointer(
		index,
		size,
		static_cast<unsigned int>(type),
		stride,
		static_cast<const GLvoid*>(static_cast<char*>(0) + offset));
}

void OpenGL::OpenGLWrapper::VertexAttribLPointer(unsigned int index, int size, OpenGL::DataType type, int stride, int offset) {
	_gl.VertexAttribLPointer(
		index,
		size,
		static_cast<unsigned int>(type),
		stride,
		static_cast<const GLvoid*>(static_cast<char*>(0) + offset));
}

void OpenGL::OpenGLWrapper::VertexAttribDivisor(unsigned int index, unsigned int divisor) {
	_gl.VertexAttribDivisor(
		index,
		divisor);
}

void OpenGL::OpenGLWrapper::BindVertexArray(const OpenGL::Handle & h) {
	_gl.BindVertexArray(h.Value());
}

void OpenGL::OpenGLWrapper::Viewport(const glm::uvec2 & pos, const glm::uvec2 & dim) {
	_gl.Viewport(pos.x, pos.y, dim.x, dim.y);
}

std::unique_ptr<OpenGL::Handle> OpenGL::OpenGLWrapper::GenTexture() {
	unsigned int h;
	_gl.GenTextures(1, &h);
	return std::unique_ptr<OpenGL::Handle>(new Handle(OpenGL::ObjectType::Texture, h));
}

void OpenGL::OpenGLWrapper::BindTexture(OpenGL::TextureTarget target, const Handle & h) {
	_gl.BindTexture(static_cast<unsigned int>(target), h.Value());
}

void OpenGL::OpenGLWrapper::TexImage2D(TextureTarget target, int level, TextureInternalFormat internalFormat, glm::ivec2 dim, TexturePixelType format, DataType type, const void * data) {
	_gl.TexImage2D(
		static_cast<unsigned int>(target),
		level,
		static_cast<unsigned int>(internalFormat),
		dim.x, dim.y,
		0,
		static_cast<unsigned int>(format),
		static_cast<unsigned int>(type),
		data
	);
}

void OpenGL::OpenGLWrapper::TexParameter(TextureTarget target, TextureParameter param, TextureParameterValue value) {
	_gl.TexParameteri(
		static_cast<unsigned int>(target),
		static_cast<unsigned int>(param),
		static_cast<int>(value));
}

void OpenGL::OpenGLWrapper::TexParameter(TextureTarget target, TextureParameter param, int value) {
	_gl.TexParameteri(
		static_cast<unsigned int>(target),
		static_cast<unsigned int>(param),
		value);
}

void OpenGL::OpenGLWrapper::GenerateMipmap(TextureTarget target) {
	_gl.GenerateMipmap(static_cast<unsigned int>(target));
}

void OpenGL::OpenGLWrapper::GenerateTextureMipmap(const Handle & h) {
	_gl.GenerateTextureMipmap(h.Value());
}

void OpenGL::OpenGLWrapper::ActiveTexture(unsigned int slot) {
	_gl.ActiveTexture(slot);
}

void OpenGL::OpenGLWrapper::Enable(Capabilities cap) {
	_gl.Enable(static_cast<unsigned int>(cap));
}

void OpenGL::OpenGLWrapper::Disable(Capabilities cap) {
	_gl.Disable(static_cast<unsigned int>(cap));
}

