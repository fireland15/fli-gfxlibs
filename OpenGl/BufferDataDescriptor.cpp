#include "BufferDataDescriptor.hpp"

OpenGL::BufferDataDescriptor::BufferDataDescriptor(const void * data, unsigned int size, unsigned int count)
	: Data(data), Size(size), Count(count) { }