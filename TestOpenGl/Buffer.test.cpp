#include <gtest.h>
#include <gmock.h>

#include <Buffer.hpp>
#include <Handle.hpp>
#include <ObjectTypeEnum.hpp>
#include "MockBufferDataUpdateStrategy.hpp"
#include "MockOpenGL.hpp"
#include <OpenGLWrapper.hpp>
#include <BufferDataPointer.hpp>

using ::testing::_;
using ::testing::AtLeast;

namespace {

	TEST(BufferTest, BindCalls_glBindBuffer) {
		// Arrange
		MockOpenGL mockgl;
		EXPECT_CALL(mockgl, BindBuffer(_, _)).Times(1);
		EXPECT_CALL(mockgl, DeleteBuffers(_, _));
		// Todo: Add expectations for parameters
		OpenGL::OpenGLWrapper wrap(mockgl);
		std::unique_ptr<OpenGL::Handle> obj(new OpenGL::Handle(OpenGL::ObjectType::Buffer, 1));
		OpenGL::Buffer buf(wrap, std::move(obj));

		// Act
		buf.Bind();
	}

	TEST(BufferTest, UnbindCalls_glBindBuffer) {
		// Arrange
		MockOpenGL mockgl;
		EXPECT_CALL(mockgl, BindBuffer(_, _)).Times(1);
		EXPECT_CALL(mockgl, DeleteBuffers(_, _));
		// Todo: Add expectations for parameters
		OpenGL::OpenGLWrapper wrap(mockgl);
		std::unique_ptr<OpenGL::Handle> obj(new OpenGL::Handle(OpenGL::ObjectType::Buffer, 1));
		OpenGL::Buffer buf(wrap, std::move(obj));

		// Act
		buf.Unbind();
	}

	TEST(BufferTest, DataCalls_glBufferData) {
		// Arrange
		MockOpenGL mockgl;
		EXPECT_CALL(mockgl, BufferData(_, _, _, _)).Times(1);
		EXPECT_CALL(mockgl, DeleteBuffers(_, _));

		// Todo: Add expectations for parameters
		OpenGL::OpenGLWrapper wrap(mockgl);
		std::unique_ptr<OpenGL::Handle> obj(new OpenGL::Handle(OpenGL::ObjectType::Buffer, 1));
		OpenGL::Buffer buf(wrap, std::move(obj));

		// Act
		buf.Data(std::vector<unsigned char>(), OpenGL::BufferDataLayout());
	}

	TEST(BufferTest, UpdateCallsStrategyUpdateMethodWhenUsageIsNotStatic) {
		// Arrange
		MockBufferDataUpdateStrategy strat;
		EXPECT_CALL(strat, Update(_, _, _)).Times(1);

		// Arrange
		MockOpenGL mockgl;
		EXPECT_CALL(mockgl, DeleteBuffers(_, _));

		OpenGL::OpenGLWrapper wrap(mockgl);
		std::unique_ptr<OpenGL::Handle> obj(new OpenGL::Handle(OpenGL::ObjectType::Buffer, 1));
		OpenGL::Buffer buf(wrap, std::move(obj), OpenGL::BufferUsage::DynamicDraw, OpenGL::BufferTarget::ArrayBuffer);

		// Act
		buf.Update(std::vector<unsigned char>(), OpenGL::BufferDataPointer(1, OpenGL::DataType::Byte), strat);

		// Assert
	}

	TEST(BufferTest, Update_DoesNotCallStrategyUpdate_WhenUsageStaticDraw) {
		// Arrange
		MockBufferDataUpdateStrategy strat;
		EXPECT_CALL(strat, Update(_, _, _)).Times(0);

		// Arrange
		MockOpenGL mockgl;
		EXPECT_CALL(mockgl, DeleteBuffers(_, _));

		OpenGL::OpenGLWrapper wrap(mockgl);
		std::unique_ptr<OpenGL::Handle> obj(new OpenGL::Handle(OpenGL::ObjectType::Buffer, 1));
		OpenGL::Buffer buf(wrap, std::move(obj), OpenGL::BufferUsage::StaticDraw, OpenGL::BufferTarget::ArrayBuffer);

		// Act
		buf.Update(std::vector<unsigned char>(), OpenGL::BufferDataPointer(1, OpenGL::DataType::Byte), strat);

		// Assert
	}

	TEST(BufferTest, Update_DoesNotCallStrategyUpdate_WhenUsageStaticRead) {
		// Arrange
		MockBufferDataUpdateStrategy strat;
		EXPECT_CALL(strat, Update(_, _, _)).Times(0);

		// Arrange
		MockOpenGL mockgl;
		EXPECT_CALL(mockgl, DeleteBuffers(_, _));

		OpenGL::OpenGLWrapper wrap(mockgl);
		std::unique_ptr<OpenGL::Handle> obj(new OpenGL::Handle(OpenGL::ObjectType::Buffer, 1));
		OpenGL::Buffer buf(wrap, std::move(obj), OpenGL::BufferUsage::StaticRead, OpenGL::BufferTarget::ArrayBuffer);

		// Act
		buf.Update(std::vector<unsigned char>(), OpenGL::BufferDataPointer(1, OpenGL::DataType::Byte), strat);

		// Assert
	}

	TEST(BufferTest, Update_DoesNotCallStrategyUpdate_WhenUsageStaticCopy) {
		// Arrange
		MockBufferDataUpdateStrategy strat;
		EXPECT_CALL(strat, Update(_, _, _)).Times(0);

		// Arrange
		MockOpenGL mockgl;
		EXPECT_CALL(mockgl, DeleteBuffers(_, _));

		OpenGL::OpenGLWrapper wrap(mockgl);
		std::unique_ptr<OpenGL::Handle> obj(new OpenGL::Handle(OpenGL::ObjectType::Buffer, 1));
		OpenGL::Buffer buf(wrap, std::move(obj), OpenGL::BufferUsage::StaticCopy, OpenGL::BufferTarget::ArrayBuffer);

		// Act
		buf.Update(std::vector<unsigned char>(), OpenGL::BufferDataPointer(1, OpenGL::DataType::Byte), strat);

		// Assert
	}
}