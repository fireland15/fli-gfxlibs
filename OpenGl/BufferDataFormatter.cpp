#include "BufferDataFormatter.hpp"
#include "BufferDataDescriptor.hpp"

typedef unsigned char byte;

void OpenGL::BufferDataFormatter::InterleaveSubData(std::vector<byte>& out, unsigned int startIndex, std::list<std::pair<OpenGL::BufferDataDescriptor, std::reference_wrapper<OpenGL::BufferDataPointer>>>& descriptors) {
	unsigned int groupStride = 0;
	for (auto & desc : descriptors)
		groupStride += desc.first.Size;

	unsigned int firstElementOffset = 0;
	for (auto & pair : descriptors) {
		pair.second.get().Offset(firstElementOffset + startIndex);
		if (groupStride == pair.first.Size)
			pair.second.get().Stride(0);
		else
			pair.second.get().Stride(groupStride);
		firstElementOffset += pair.first.Size;
	}

	for (unsigned int i = 0; i < descriptors.front().first.Count; i++) {
		unsigned int offset = 0;
		// foreach data array
		for (auto & pair : descriptors) {
			auto & desc = pair.first;
			// Where in the output array to put the data element
			unsigned int index = startIndex + (i * groupStride) + offset;
			// copy each byte in data element
			memcpy(&out[index], &reinterpret_cast<const byte*>(desc.Data)[i * desc.Size], desc.Size);

			offset += desc.Size;
		}
	}
}