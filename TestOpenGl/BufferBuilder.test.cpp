#include <gtest.h>

#include <BufferBuilder.hpp>
#include <Handle.hpp>

#include "MockOpenGL.hpp"
#include <OpenGLWrapper.hpp>
#include "MockBufferDataBuilder.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::SetArgPointee;

namespace {

	TEST(BufferBuilderTest, BuildCallsGlGenBuffers) {
		MockOpenGL mockgl;
		EXPECT_CALL(mockgl, GenBuffers(1, _)).Times(1);
		EXPECT_CALL(mockgl, DeleteBuffers(_, _));

		MockBufferDataBuilder mockDataBuilder;

		OpenGL::OpenGLWrapper wrap(mockgl);
		OpenGL::BufferBuilder b(wrap, mockDataBuilder);
		b.NewBuffer().Build();
	}

	TEST(BufferBuilderTest, NewBufferSetsOpenGLReferenceInBuffer) {
		unsigned int a[1]{ 1 };

		MockOpenGL mockgl;
		EXPECT_CALL(mockgl, GenBuffers(1, _))
			.WillOnce(SetArgPointee<1>(a[0]));
		EXPECT_CALL(mockgl, DeleteBuffers(_, _));

		MockBufferDataBuilder mockDataBuilder;

		OpenGL::OpenGLWrapper wrap(mockgl);
		OpenGL::BufferBuilder b(wrap, mockDataBuilder);
		auto res = b.NewBuffer().Build();

		EXPECT_EQ(res->Handle().Value(), a[0]);
	}

	TEST(BufferBuilderTest, UsedForSetsBuffersUsage) {
		MockOpenGL mockgl;
		EXPECT_CALL(mockgl, GenBuffers(1, _)).Times(1);
		EXPECT_CALL(mockgl, DeleteBuffers(_, _));
		MockBufferDataBuilder mockDataBuilder;

		OpenGL::OpenGLWrapper wrap(mockgl);
		OpenGL::BufferBuilder b(wrap, mockDataBuilder);
		auto res = b.NewBuffer()
			.UsedFor(OpenGL::BufferUsage::DynamicDraw)
			.Build();

		EXPECT_EQ(res->Usage(), OpenGL::BufferUsage::DynamicDraw);
	}

	TEST(BufferBuilderTest, TargetingSetsBufferTarget) {
		MockOpenGL mockgl;
		EXPECT_CALL(mockgl, GenBuffers(1, _)).Times(1);
		EXPECT_CALL(mockgl, DeleteBuffers(_, _));
		MockBufferDataBuilder mockDataBuilder;

		OpenGL::OpenGLWrapper wrap(mockgl);
		OpenGL::BufferBuilder b(wrap, mockDataBuilder);
		auto res = b.NewBuffer()
			.Targeting(OpenGL::BufferTarget::CopyWriteBuffer)
			.Build();

		EXPECT_EQ(res->Target(), OpenGL::BufferTarget::CopyWriteBuffer);
	}

	TEST(BufferBuilderTest, WithDataExecutesAction) {
		MockOpenGL mockgl;
		EXPECT_CALL(mockgl, GenBuffers(1, _)).Times(1);
		EXPECT_CALL(mockgl, DeleteBuffers(_, _));
		MockBufferDataBuilder mockDataBuilder;
		EXPECT_CALL(mockDataBuilder, BuildData(_))
			.WillOnce(Return(std::vector<unsigned char>()));
		EXPECT_CALL(mockDataBuilder, Layout())
			.WillOnce(Return(OpenGL::BufferDataLayout()));

		bool actionCalled = false;

		OpenGL::OpenGLWrapper wrap(mockgl);
		OpenGL::BufferBuilder b(wrap, mockDataBuilder);
		auto res = b.NewBuffer()
			.WithData([&actionCalled] (OpenGL::IBufferDataBuilder& bdb) { actionCalled = true; })
			.Build();

		EXPECT_TRUE(actionCalled);
	}

	TEST(BufferBuilderTest, WithDataCalledBufferDataBuilderBuild) {
		MockOpenGL mockgl;
		EXPECT_CALL(mockgl, GenBuffers(1, _)).Times(1);
		EXPECT_CALL(mockgl, DeleteBuffers(_, _));
		MockBufferDataBuilder mockDataBuilder;
		EXPECT_CALL(mockDataBuilder, BuildData(_))
			.WillOnce(Return(std::vector<unsigned char>()));
		EXPECT_CALL(mockDataBuilder, Layout())
			.WillOnce(Return(OpenGL::BufferDataLayout()));

		bool actionCalled = false;

		OpenGL::OpenGLWrapper wrap(mockgl);
		OpenGL::BufferBuilder b(wrap, mockDataBuilder);
		auto res = b.NewBuffer()
			.WithData([&actionCalled](OpenGL::IBufferDataBuilder& bdb) { /* DO NOTHING */ })
			.Build();
	}

	TEST(BufferBuilderTest, BuildWhenDataIsAddedCallsBindBuffer) {
		MockOpenGL mockgl;
		EXPECT_CALL(mockgl, GenBuffers(1, _)).Times(1);
		EXPECT_CALL(mockgl, DeleteBuffers(_, _));
		EXPECT_CALL(mockgl, BindBuffer(_, _));
		MockBufferDataBuilder mockDataBuilder;
		EXPECT_CALL(mockDataBuilder, BuildData(_))
			.WillOnce(Return(std::vector<unsigned char>(12, 'a')));
		EXPECT_CALL(mockDataBuilder, Layout())
			.WillOnce(Return(OpenGL::BufferDataLayout()));

		bool actionCalled = false;

		OpenGL::OpenGLWrapper wrap(mockgl);
		OpenGL::BufferBuilder b(wrap, mockDataBuilder);
		auto res = b.NewBuffer()
			.WithData([&actionCalled](OpenGL::IBufferDataBuilder& bdb) { /* DO NOTHING */ })
			.Build();
	}

}