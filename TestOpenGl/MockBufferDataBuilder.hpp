#pragma once

#include <gmock.h>
#include <vector>
#include <BufferDataFormatter.hpp>
#include <BufferDataPointer.hpp>
#include <BufferDataLayout.hpp>
#include <IBufferDataBuilder.hpp>

class MockBufferDataBuilder : public OpenGL::IBufferDataBuilder {
public:
	MOCK_METHOD4(Data, IBufferDataBuilder&(const void*, unsigned int, unsigned int, OpenGL::BufferDataPointer&));
	MOCK_METHOD4(InterleavedWith, IBufferDataBuilder&(const void*, unsigned int, unsigned int, OpenGL::BufferDataPointer&));
	MOCK_METHOD4(And, IBufferDataBuilder&(const void*, unsigned int, unsigned int, OpenGL::BufferDataPointer&));
	MOCK_METHOD1(BuildData, std::vector<byte>(OpenGL::BufferDataFormatter&));
	MOCK_METHOD0(Layout, OpenGL::BufferDataLayout());
};