#include <gtest.h>
#include <gmock.h>

#include <ProgramBuilder.hpp>

#include "MockOpenGL.hpp"
#include "MockShader.hpp"
#include <OpenGLWrapper.hpp>
#include <ProgramLinkException.hpp>

using ::testing::_;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::SetArgPointee;

namespace {

	TEST(ProgramBuilderTests, AttachingShaderCausesBuildToCallglAttachShader) {
		MockOpenGL mockgl;
		EXPECT_CALL(mockgl, AttachShader(_, _)).Times(1);
		EXPECT_CALL(mockgl, CreateProgram()).Times(1);
		EXPECT_CALL(mockgl, LinkProgram(_)).Times(1);
		EXPECT_CALL(mockgl, GetProgramiv(_, _, _)).WillOnce(SetArgPointee<2>(1));
		EXPECT_CALL(mockgl, DetachShader(_, _)).Times(1);
		EXPECT_CALL(mockgl, GetProgramInterfaceiv(_, _, _, _)).WillRepeatedly(SetArgPointee<3>(0));

		EXPECT_CALL(mockgl, DeleteProgram(_));
		OpenGL::OpenGLWrapper wrap(mockgl);

		MockShader shader;
		EXPECT_CALL(shader, Handle()).WillRepeatedly(ReturnRef(OpenGL::Handle(OpenGL::ObjectType::Shader, 1)));

		OpenGL::ProgramBuilder b(wrap);
		b.Attach(shader).Build();
	}

	TEST(ProgramBuilderTests, NoShadersCausesBuildToThrow) {
		MockOpenGL mockgl;
		OpenGL::OpenGLWrapper wrap(mockgl);

		OpenGL::ProgramBuilder b(wrap);
		EXPECT_THROW(b.Build(), OpenGL::ProgramLinkException);
	}

	TEST(ProgramBuilderTests, FailedLinkingThrows) {
		char* err = "a";
		MockOpenGL mockgl;
		EXPECT_CALL(mockgl, AttachShader(_, _)).Times(1);
		EXPECT_CALL(mockgl, CreateProgram()).Times(1);
		EXPECT_CALL(mockgl, LinkProgram(_));
		EXPECT_CALL(mockgl, GetProgramiv(_, _, _))
			.WillOnce(SetArgPointee<2>(0))
			.WillOnce(SetArgPointee<2>(1));
		EXPECT_CALL(mockgl, GetProgramInfoLog(_, _, _, _)).WillOnce(SetArgPointee<3>(err[0]));
		EXPECT_CALL(mockgl, DetachShader(_, _)).Times(1);
		EXPECT_CALL(mockgl, DeleteProgram(_));
		OpenGL::OpenGLWrapper wrap(mockgl);

		MockShader shader;
		EXPECT_CALL(shader, Handle()).WillRepeatedly(ReturnRef(OpenGL::Handle(OpenGL::ObjectType::Shader, 1)));

		OpenGL::ProgramBuilder b(wrap);
		EXPECT_THROW(b.Attach(shader).Build(), OpenGL::ProgramLinkException);
	}

}