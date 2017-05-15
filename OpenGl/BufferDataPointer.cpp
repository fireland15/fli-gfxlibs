#include "BufferDataPointer.hpp"

OpenGL::BufferDataPointer::BufferDataPointer(unsigned int count, OpenGL::DataType type)
	: _count(count), _type(type), _stride(0), _offset(0) { }

unsigned int OpenGL::BufferDataPointer::Count() const {
	return _count;
}

OpenGL::DataType OpenGL::BufferDataPointer::Type() const {
	return _type;
}

void OpenGL::BufferDataPointer::Offset(unsigned int offset) {
	_offset = offset;
}

unsigned int OpenGL::BufferDataPointer::Offset() const {
	return _offset;
}

void OpenGL::BufferDataPointer::Stride(unsigned int stride) {
	_stride = stride;
}

unsigned int OpenGL::BufferDataPointer::Stride() const {
	return _stride;
}
