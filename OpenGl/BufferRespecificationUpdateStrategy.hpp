#pragma once

#include "IBufferDataUpdateStrategy.hpp"
#include <OpenGLWrapper.hpp>
#include "IBuffer.hpp"
#include "BufferDataLayout.hpp"
#include "BufferDataException.hpp"

namespace OpenGL {

	class BufferRespecificationUpdateStrategy : public IBufferDataUpdateStrategy {
	public:
		BufferRespecificationUpdateStrategy(OpenGLWrapper& gl);

		virtual ~BufferRespecificationUpdateStrategy();

		virtual void Update(IBuffer& buf, const std::vector<unsigned char>& data, const BufferDataPointer& pointer) override {
			if (buf.Layout().Count() != 1) {
				throw BufferDataException("Cannot update buffers storing multiple data sets");
			}
			
			RespecifyBuffer(buf.Target(), data, buf.Usage());
		}

	private:
		OpenGLWrapper& _gl;

		void RespecifyBuffer(BufferTarget target, const std::vector<unsigned char>& data, BufferUsage usage);
	};

}