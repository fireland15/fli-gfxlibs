#pragma once

namespace OpenGL {
	
	struct BufferDataDescriptor {
		BufferDataDescriptor(const void * data, unsigned int size, unsigned int count);
		const void* Data;
		unsigned int Size;
		unsigned int Count;
	};

}