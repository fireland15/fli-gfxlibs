#pragma once

#include <gmock.h>

#include <IOpenGL.hpp>

class MockOpenGL : public OpenGL::IOpenGL {
public:
	virtual ~MockOpenGL() { }
	MOCK_METHOD2(GenBuffers, void(int n, unsigned int* buffers));
	MOCK_METHOD2(CreateBuffers, void(int, unsigned int*));
	MOCK_METHOD2(DeleteBuffers, void(int n, const unsigned int* buffers));
	MOCK_METHOD2(BindBuffer, void(unsigned int, unsigned int));
	MOCK_METHOD4(BufferData, void(unsigned int, int _w64, const void*, unsigned int));
	MOCK_METHOD4(NamedBufferData, void(unsigned int, int _w64, const void*, unsigned int));
	MOCK_METHOD4(ClearColor, void(float, float, float, float));
	MOCK_METHOD1(Clear, void(unsigned int));
	MOCK_METHOD0(GetError, unsigned int());
	MOCK_METHOD2(GetIntegerv, void(unsigned int, int*));
	MOCK_METHOD0(CreateProgram, unsigned int());
	MOCK_METHOD1(DeleteProgram, void(unsigned int));
	MOCK_METHOD2(AttachShader, void(unsigned int, unsigned int));
	MOCK_METHOD2(DetachShader, void(unsigned int, unsigned int));
	MOCK_METHOD1(UseProgram, void(unsigned int));
	MOCK_METHOD1(LinkProgram, void(unsigned int));
	MOCK_METHOD3(GetProgramiv, void(unsigned int, unsigned int, int*));
	MOCK_METHOD4(GetProgramInfoLog, void(unsigned int, int, int*, char*));
	MOCK_METHOD3(ProgramUniform1f, void(unsigned int, int, float));
	MOCK_METHOD4(ProgramUniform2f, void(unsigned int, int, float, float));
	MOCK_METHOD5(ProgramUniform3f, void(unsigned int, int, float, float, float));
	MOCK_METHOD6(ProgramUniform4f, void(unsigned int, int, float, float, float, float));
	MOCK_METHOD3(ProgramUniform1i, void(unsigned int, int, int));
	MOCK_METHOD4(ProgramUniform2i, void(unsigned int, int, int, int));
	MOCK_METHOD5(ProgramUniform3i, void(unsigned int, int, int, int, int));
	MOCK_METHOD6(ProgramUniform4i, void(unsigned int, int, int, int, int, int));
	MOCK_METHOD3(ProgramUniform1ui, void(unsigned int, int, unsigned int));
	MOCK_METHOD4(ProgramUniform2ui, void(unsigned int, int, unsigned int, unsigned int));
	MOCK_METHOD5(ProgramUniform3ui, void(unsigned int, int, unsigned int, unsigned int, unsigned int));
	MOCK_METHOD6(ProgramUniform4ui, void(unsigned int, int, unsigned int, unsigned int, unsigned int, unsigned int));
	MOCK_METHOD4(ProgramUniform1fv, void(unsigned int, int, int, const float*));
	MOCK_METHOD4(ProgramUniform2fv, void(unsigned int, int, int, const float*));
	MOCK_METHOD4(ProgramUniform3fv, void(unsigned int, int, int, const float*));
	MOCK_METHOD4(ProgramUniform4fv, void(unsigned int, int, int, const float*));
	MOCK_METHOD4(ProgramUniform1iv, void(unsigned int, int, int, const int*));
	MOCK_METHOD4(ProgramUniform2iv, void(unsigned int, int, int, const int*));
	MOCK_METHOD4(ProgramUniform3iv, void(unsigned int, int, int, const int*));
	MOCK_METHOD4(ProgramUniform4iv, void(unsigned int, int, int, const int*));
	MOCK_METHOD4(ProgramUniform1uiv, void(unsigned int, int, int, const unsigned int*));
	MOCK_METHOD4(ProgramUniform2uiv, void(unsigned int, int, int, const unsigned int*));
	MOCK_METHOD4(ProgramUniform3uiv, void(unsigned int, int, int, const unsigned int*));
	MOCK_METHOD4(ProgramUniform4uiv, void(unsigned int, int, int, const unsigned int*));
	MOCK_METHOD5(ProgramUniformMatrix2fv, void(unsigned int, int, int, unsigned char, const float*));
	MOCK_METHOD5(ProgramUniformMatrix3fv, void(unsigned int, int, int, unsigned char, const float*));
	MOCK_METHOD5(ProgramUniformMatrix4fv, void(unsigned int, int, int, unsigned char, const float*));
	MOCK_METHOD5(ProgramUniformMatrix2x3fv, void(unsigned int, int, int, unsigned char, const float*));
	MOCK_METHOD5(ProgramUniformMatrix3x2fv, void(unsigned int, int, int, unsigned char, const float*));
	MOCK_METHOD5(ProgramUniformMatrix2x4fv, void(unsigned int, int, int, unsigned char, const float*));
	MOCK_METHOD5(ProgramUniformMatrix4x2fv, void(unsigned int, int, int, unsigned char, const float*));
	MOCK_METHOD5(ProgramUniformMatrix3x4fv, void(unsigned int, int, int, unsigned char, const float*));
	MOCK_METHOD5(ProgramUniformMatrix4x3fv, void(unsigned int, int, int, unsigned char, const float*));
	MOCK_METHOD4(GetProgramInterfaceiv, void(unsigned int, unsigned int, unsigned int, int*));
	MOCK_METHOD8(GetProgramResourceiv, void(unsigned int, unsigned int, unsigned int, int, const unsigned int*, int, int*, int*));
	MOCK_METHOD6(GetProgramResourceName, void(unsigned int, unsigned int, unsigned int, int, int*, char*));
	MOCK_METHOD3(GetProgramResourceLocation, int(unsigned int, unsigned int, const char*));
	MOCK_METHOD4(ShaderSource, void(unsigned int, int, const char**, const int*));
	MOCK_METHOD1(CreateShader, unsigned int(unsigned int));
	MOCK_METHOD1(DeleteShader, void(unsigned int));
	MOCK_METHOD1(CompileShader, void(unsigned int));
	MOCK_METHOD3(GetShaderiv, void(unsigned int, unsigned int, int*));
	MOCK_METHOD4(GetShaderInfoLog, void(unsigned int, int, int*, char*));
	MOCK_METHOD4(DrawArraysInstanced, void(unsigned int, int, int, int));
	MOCK_METHOD3(DrawArrays, void(unsigned int, int, int));
	MOCK_METHOD2(GenVertexArrays, void(int, unsigned int*));
	MOCK_METHOD2(DeleteVertexArrays, void(int, const unsigned int*));
	MOCK_METHOD1(EnableVertexAttribArray, void(unsigned int));
	MOCK_METHOD1(DisableVertexAttribArray, void(unsigned int));
	MOCK_METHOD2(EnableVertexArrayAttrib, void(unsigned int, unsigned int));
	MOCK_METHOD2(DisableVertexArrayAttrib, void(unsigned int, unsigned int));
	MOCK_METHOD6(VertexAttribPointer, void(unsigned int, int, unsigned int, unsigned char, int, const void*));
	MOCK_METHOD5(VertexAttribIPointer, void(unsigned int, int, unsigned int, int, const void*));
	MOCK_METHOD5(VertexAttribLPointer, void(unsigned int, int, unsigned int, int, const void*));
	MOCK_METHOD2(VertexAttribDivisor, void(unsigned int, unsigned int));
	MOCK_METHOD1(BindVertexArray, void(unsigned int));
	MOCK_METHOD4(Viewport, void(int, int, int, int));
	MOCK_METHOD0(VertexArrayBindVertexBuffer, void());
	MOCK_METHOD0(VertexArrayVertexAttribBinding, void());
	MOCK_METHOD0(VertexArrayVertexAttribDivisor, void());
	MOCK_METHOD2(GenTextures, void(int, unsigned int*));
	MOCK_METHOD2(BindTexture, void(unsigned int, unsigned int));
	MOCK_METHOD9(TexImage2D, void(unsigned int, int, int, int, int, int, unsigned int, unsigned int, const void*));
	MOCK_METHOD1(ActiveTexture, void(unsigned int));
	MOCK_METHOD3(TexParameteri, void(unsigned int, unsigned int, int));
	MOCK_METHOD1(GenerateMipmap, void(unsigned int));
	MOCK_METHOD1(GenerateTextureMipmap, void(unsigned int));
	MOCK_METHOD1(Enable, void(unsigned int));
	MOCK_METHOD1(Disable, void(unsigned int));
};