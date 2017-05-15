#include "BufferBuilder.hpp"

#include <OpenGLWrapper.hpp>
#include "Handle.hpp"
#include "Buffer.hpp"
#include "IBufferDataBuilder.hpp"
#include "BufferDataFormatter.hpp"
#include "ObjectTypeEnum.hpp"

OpenGL::BufferBuilder::BufferBuilder(OpenGLWrapper& gl, IBufferDataBuilder& dataBuilder)
	: _gl(gl), _dataBuilder(dataBuilder) {
	
}

OpenGL::BufferBuilder::~BufferBuilder() { }

OpenGL::IBufferBuilder & OpenGL::BufferBuilder::NewBuffer() {
	_usage = OpenGL::BufferUsage::StaticDraw;
	_target = OpenGL::BufferTarget::ArrayBuffer;

	if (!_data.empty())
		_data.clear();

	return *this;
}

OpenGL::IBufferBuilder & OpenGL::BufferBuilder::UsedFor(BufferUsage usage) {
	_usage = usage;

	return *this;
}

OpenGL::IBufferBuilder & OpenGL::BufferBuilder::Targeting(BufferTarget target) {
	_target = target;

	return *this;
}

OpenGL::IBufferBuilder & OpenGL::BufferBuilder::WithData(std::function<void(IBufferDataBuilder&)> func) {
	func(_dataBuilder);
	OpenGL::BufferDataFormatter formatter;
	_data = _dataBuilder.BuildData(formatter);
	_layout = _dataBuilder.Layout();

	return *this;
}

std::unique_ptr<OpenGL::IBuffer> OpenGL::BufferBuilder::Build() {
	auto obj = _gl.GenBuffer();

	auto buffer = std::unique_ptr<OpenGL::IBuffer>(new OpenGL::Buffer(_gl, std::move(obj), _usage, _target));

	if (!_data.empty()) {
		buffer->Bind();
		buffer->Data(_data, _layout);
		_data.clear();
	}

	return buffer;
}
