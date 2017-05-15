#pragma once

#include <vector>

namespace OpenGL {

	class IBuffer;
	class BufferDataPointer;

	class IBufferDataUpdateStrategy {
	public:
		virtual ~IBufferDataUpdateStrategy() { }

		/// <summary>
		/// Updates the data contained in the buffer
		/// </summary>
		/// <param name="buffer">The buffer whose data is to be updated</param>
		/// <param name="data">The data to place within the buffer</param>
		virtual void Update(IBuffer& buffer, const std::vector<unsigned char>& data, const BufferDataPointer& pointer) = 0;
	};

}