#include "BufferDataLayout.hpp"

#include "BufferDataPointer.hpp"

void OpenGL::BufferDataLayout::Add(std::reference_wrapper<OpenGL::BufferDataPointer> pointer) {
	_pointers.emplace_back(pointer);
}

unsigned int OpenGL::BufferDataLayout::Count() const {
	return _pointers.size();
}

const OpenGL::BufferDataPointer & OpenGL::BufferDataLayout::operator[](unsigned int index) {
	return _pointers[index];
}