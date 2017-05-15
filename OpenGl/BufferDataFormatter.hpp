#pragma once

#include <vector>
#include <list>

#include "BufferDataDescriptor.hpp"
#include "BufferDataPointer.hpp"

namespace OpenGL {

	class BufferDataFormatter {
	public:
		virtual void InterleaveSubData(std::vector<unsigned char>& out, unsigned int startIndex, std::list<std::pair<BufferDataDescriptor, std::reference_wrapper<BufferDataPointer>>>& descriptors);
	};

}