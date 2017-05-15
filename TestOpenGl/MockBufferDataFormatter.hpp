#pragma once

#include <gmock.h>

#include <vector>
#include <list>

#include <BufferDataFormatter.hpp>
#include <BufferDataDescriptor.hpp>

class MockBufferDataFormatter : public OpenGL::BufferDataFormatter {
public:
	virtual ~MockBufferDataFormatter() { }
	MOCK_METHOD3(InterleaveSubData, void(std::vector<unsigned char>& out, unsigned int startIndex, std::list<std::pair<OpenGL::BufferDataDescriptor, std::reference_wrapper<OpenGL::BufferDataPointer>>>& descriptors));
};