#pragma once

#include <vector>

namespace OpenGL {

	class BufferDataPointer;

	class BufferDataLayout {
	public:
		void Add(std::reference_wrapper<BufferDataPointer> pointer);
		unsigned int Count() const;
		const BufferDataPointer & operator[](unsigned int index);
	private:
		std::vector<std::reference_wrapper<BufferDataPointer>> _pointers;
	};
}