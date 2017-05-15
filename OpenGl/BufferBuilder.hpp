#pragma once

#include <vector>

#include "IBufferBuilder.hpp"
#include "BufferDataLayout.hpp"

namespace OpenGL {

	class OpenGLWrapper;
	class Buffer;
	class Handle;
	class IBufferDataBuilder;

	class BufferBuilder : public IBufferBuilder {
	public:
		BufferBuilder(OpenGLWrapper& gl, IBufferDataBuilder& dataBuilder);
		virtual ~BufferBuilder();
		virtual IBufferBuilder & NewBuffer() override;
		virtual IBufferBuilder & UsedFor(BufferUsage usage) override;
		virtual IBufferBuilder & Targeting(BufferTarget target) override;
		virtual IBufferBuilder & WithData(std::function<void(IBufferDataBuilder&)> func) override;
		virtual std::unique_ptr<IBuffer> Build() override;

	private:
		OpenGLWrapper& _gl;
		IBufferDataBuilder& _dataBuilder;

		BufferUsage _usage;
		BufferTarget _target;
		std::vector<unsigned char> _data;
		BufferDataLayout _layout;
	};

}