#pragma once

#include <gmock.h>

#include <IShader.hpp>
#include <ShaderTypeEnum.hpp>
#include <ShaderSource.hpp>

class MockShader : public OpenGL::IShader {
public:
	virtual ~MockShader() { }
	MOCK_METHOD0(Handle, const OpenGL::Handle&());
	MOCK_METHOD0(Source, const OpenGL::ShaderSource&());
	MOCK_METHOD0(Type, OpenGL::ShaderType());
};