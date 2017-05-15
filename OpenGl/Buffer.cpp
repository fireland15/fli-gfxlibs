#include "Buffer.hpp"

#include <OpenGLWrapper.hpp>
#include "Handle.hpp"
#include "IBufferDataUpdateStrategy.hpp"

OpenGL::Buffer::Buffer(OpenGL::OpenGLWrapper& gl, std::unique_ptr<OpenGL::Handle> handle, OpenGL::BufferUsage usage, OpenGL::BufferTarget target) 
	: IBuffer(), _gl(gl), _handle(std::move(handle)), _usage(usage), _target(target) {
	if (_handle == nullptr) throw std::exception();
}

inline OpenGL::Buffer::~Buffer() { 
	_gl.DeleteBuffer(std::move(_handle));
}

inline const OpenGL::Handle& OpenGL::Buffer::Handle() {
	return *_handle;
}

inline OpenGL::BufferTarget OpenGL::Buffer::Target() {
	return _target;
}

inline OpenGL::BufferUsage OpenGL::Buffer::Usage() {
	return _usage;
}

inline void OpenGL::Buffer::Bind() {
	_gl.BindBuffer(_target, *_handle);
}

inline void OpenGL::Buffer::Unbind() {
	_gl.BindBuffer(_target, OpenGL::Handle::Default());
}

inline void OpenGL::Buffer::Data(const std::vector<unsigned char>& data, const BufferDataLayout layout) {
	_layout = layout;
	_gl.BufferData(_target, data, _usage);
}

const OpenGL::BufferDataLayout & OpenGL::Buffer::Layout() {
	return _layout;
}

inline void OpenGL::Buffer::Update(const std::vector<unsigned char>& data, const OpenGL::BufferDataPointer& pointer, IBufferDataUpdateStrategy & updateStrategy) {
	Bind();
	if (!(_usage == BufferUsage::StaticDraw ||
		_usage == BufferUsage::StaticCopy ||
		_usage == BufferUsage::StaticRead))
		updateStrategy.Update(*this, data, pointer);
}
