#pragma once

#include <vector>
#include <memory>

#include "IBuffer.hpp"
#include "Handle.hpp"
#include "BufferDataLayout.hpp"

namespace OpenGL {

	class OpenGLWrapper;
	class IBufferDataUpdateStrategy;

	class Buffer : public IBuffer {
	public:
		Buffer(OpenGLWrapper& gl, std::unique_ptr<OpenGL::Handle> ref, BufferUsage usage = BufferUsage::StaticDraw, BufferTarget target = BufferTarget::ArrayBuffer);

		virtual ~Buffer();
		virtual const OpenGL::Handle& Handle() override;
		virtual BufferTarget Target() override;
		virtual BufferUsage Usage() override;
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void Data(const std::vector<unsigned char>& data, const BufferDataLayout layout) override;
		virtual const BufferDataLayout & Layout() override;
		virtual void Update(const std::vector<unsigned char>& data, const BufferDataPointer& pointer, IBufferDataUpdateStrategy & updateStrategy) override;

	private:
		OpenGLWrapper& _gl;
		std::unique_ptr<OpenGL::Handle> _handle;
		BufferTarget _target;
		BufferUsage _usage;
		bool _bound;
		BufferDataLayout _layout;
	};

}