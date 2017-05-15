#include "VertexArray.hpp"

#include <OpenGLWrapper.hpp>
#include "AttributeVariable.hpp"
#include "IBuffer.hpp"

OpenGL::VertexArray::VertexArray(OpenGL::OpenGLWrapper& gl, std::unique_ptr<OpenGL::Handle> handle)
	: _gl(gl) { 
	if (handle->Type() != OpenGL::ObjectType::VertexArray)
		throw std::exception("Incorrect handle type");
	_handle = std::move(handle);
}

OpenGL::VertexArray::~VertexArray() {
	_gl.DeleteVertexArray(std::move(_handle));
}

void OpenGL::VertexArray::Bind() {
	_gl.BindVertexArray(*_handle);
}

void OpenGL::VertexArray::Unbind() {
	_gl.BindVertexArray(OpenGL::Handle::Default());
}

void OpenGL::VertexArray::EnableVertexAttribute(const AttributeVariable & var) {
	_gl.EnableVertexAttribArray(var.Location());
}

void OpenGL::VertexArray::DisableVertexAttribute(const AttributeVariable & var) {
	_gl.DisableVertexAttribArray(var.Location());
}

void OpenGL::VertexArray::SetVertexAttributePointer(const AttributeVariable & var, IBuffer & buffer, const BufferDataPointer & ptr) {
	buffer.Bind();
	_gl.VertexAttribPointer(var.Location(), ptr.Count(), ptr.Type(), OpenGL::Normalize::No, ptr.Stride(), ptr.Offset());
}

const OpenGL::Handle & OpenGL::VertexArray::Handle() {
	return *_handle;
}
