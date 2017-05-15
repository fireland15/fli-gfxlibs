#pragma once

#include <gmock.h>

#include <IBufferDataUpdateStrategy.hpp>

class MockBufferDataUpdateStrategy : public OpenGL::IBufferDataUpdateStrategy {
public:
	virtual ~MockBufferDataUpdateStrategy() { }
	MOCK_METHOD3(Update, void(OpenGL::IBuffer&, const std::vector<unsigned char>&, const OpenGL::BufferDataPointer&));
};