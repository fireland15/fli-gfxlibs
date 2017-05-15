#pragma once

#include <gmock.h>
#include <IBuffer.hpp>
#include <Handle.hpp>
#include <BufferDataLayout.hpp>
#include <vector>
#include <IBufferDataUpdateStrategy.hpp>

class MockBuffer : public OpenGL::IBuffer {
public:
	virtual ~MockBuffer() { }
	MOCK_METHOD0(Handle, const OpenGL::Handle&());
	MOCK_METHOD0(Target, OpenGL::BufferTarget());
	MOCK_METHOD0(Usage, OpenGL::BufferUsage());
	MOCK_METHOD0(Bind, void());
	MOCK_METHOD0(Unbind, void());
	MOCK_METHOD2(Data, void(const std::vector<unsigned char>&, const OpenGL::BufferDataLayout));
	MOCK_METHOD0(Layout, const OpenGL::BufferDataLayout&());
	MOCK_METHOD3(Update, void(const std::vector<unsigned char>&, const OpenGL::BufferDataPointer&, OpenGL::IBufferDataUpdateStrategy&));
};