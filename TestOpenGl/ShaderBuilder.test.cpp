#include <gtest.h>
#include <gmock.h>

#include <ShaderBuilder.hpp>
#include "MockOpenGL.hpp"
#include <OpenGLWrapper.hpp>
#include <ShaderCompilationException.hpp>
#include <SuccessEnum.hpp>

using ::testing::_;
using ::testing::Return;
using ::testing::SetArgPointee;

namespace {

	TEST(ShaderBuilderTests, CompileThrowsShaderCompilationExceptionWhenNoShaders) {
		MockOpenGL mockgl;

		OpenGL::OpenGLWrapper wrap(mockgl);
		OpenGL::ShaderBuilder builder(wrap);
		EXPECT_THROW(builder.Compile(), OpenGL::ShaderCompilationException);
	}

	TEST(ShaderBuilderTests, SuccessfulCompileCallsGlFunctions) {
		int success = 1;

		MockOpenGL mockgl;
		EXPECT_CALL(mockgl, CreateShader(_)).WillOnce(Return(1));
		EXPECT_CALL(mockgl, ShaderSource(_, _, _, _)).Times(1);
		EXPECT_CALL(mockgl, CompileShader(_)).Times(1);
		EXPECT_CALL(mockgl, GetShaderiv(_, _, _)).WillOnce(SetArgPointee<2>(success));

		OpenGL::ShaderSource source("here's some source code");

		OpenGL::OpenGLWrapper wrap(mockgl);
		OpenGL::ShaderBuilder builder(wrap);
		builder.NewShader().Type(OpenGL::ShaderType::Vertex).AddSource(source).Compile();
	}

	TEST(ShaderBuilderTests, FailedCompileCallsGlFunctions) {
		int success = (int)OpenGL::Success::No;
		int logLength = 5;
		char* err = "error";

		MockOpenGL mockgl;
		EXPECT_CALL(mockgl, CreateShader(_)).WillOnce(Return(1));
		EXPECT_CALL(mockgl, ShaderSource(_, _, _, _)).Times(1);
		EXPECT_CALL(mockgl, CompileShader(_)).Times(1);
		EXPECT_CALL(mockgl, GetShaderiv(_, _, _))
			.WillOnce(SetArgPointee<2>(success))
			.WillOnce(SetArgPointee<2>(logLength));
		EXPECT_CALL(mockgl, GetShaderInfoLog(_, _, _, _)).WillOnce(SetArgPointee<3>(err[0]));
		EXPECT_CALL(mockgl, DeleteShader(_)).Times(1);

		OpenGL::ShaderSource source("here's some source code");

		OpenGL::OpenGLWrapper wrap(mockgl);
		OpenGL::ShaderBuilder builder(wrap);
		EXPECT_THROW(builder.NewShader().Type(OpenGL::ShaderType::Vertex).AddSource(source).Compile(), OpenGL::ShaderCompilationException);
	}

}