#include <gtest.h>
#include <gmock.h>

#include "MockOpenGL.hpp"
#include "MockBuffer.hpp"
#include <OpenGLWrapper.hpp>
#include <VertexArray.hpp>
#include <AttributeVariable.hpp>

using ::testing::_;

namespace {

	TEST(VertexArrayTest, DestructorCallsDeleteVertexArray) {
		MockOpenGL mockgl;
		EXPECT_CALL(mockgl, DeleteVertexArrays(_, _));
		OpenGL::OpenGLWrapper wrap(mockgl);
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::VertexArray, 1));

		OpenGL::VertexArray vao(wrap, std::move(h));
	}

	TEST(VertexArrayTest, BindCallsBindVertexArray) {
		MockOpenGL mockgl;
		EXPECT_CALL(mockgl, BindVertexArray(_));
		EXPECT_CALL(mockgl, DeleteVertexArrays(_, _));
		OpenGL::OpenGLWrapper wrap(mockgl);
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::VertexArray, 1));

		OpenGL::VertexArray vao(wrap, std::move(h));
		vao.Bind();
	}

	TEST(VertexArrayTest, UnBindCallsBindVertexArrayWithZero) {
		MockOpenGL mockgl;
		EXPECT_CALL(mockgl, BindVertexArray(0));
		EXPECT_CALL(mockgl, DeleteVertexArrays(_, _));
		OpenGL::OpenGLWrapper wrap(mockgl);
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::VertexArray, 1));

		OpenGL::VertexArray vao(wrap, std::move(h));
		vao.Unbind();
	}

	TEST(VertexArrayTest, EnableVertexAttributeCallsEnableVertexAttribArray) {
		MockOpenGL mockgl;
		EXPECT_CALL(mockgl, EnableVertexAttribArray(_));
		EXPECT_CALL(mockgl, DeleteVertexArrays(_, _));
		OpenGL::OpenGLWrapper wrap(mockgl);
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::VertexArray, 1));

		OpenGL::VertexArray vao(wrap, std::move(h));
		vao.EnableVertexAttribute(OpenGL::AttributeVariable(1, std::string(), OpenGL::AttributeType::Float));
	}

	TEST(VertexArrayTest, DisableVertexAttributeCallsDisableVertexAttribArray) {
		MockOpenGL mockgl;
		EXPECT_CALL(mockgl, DisableVertexAttribArray(_));
		EXPECT_CALL(mockgl, DeleteVertexArrays(_, _));
		OpenGL::OpenGLWrapper wrap(mockgl);
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::VertexArray, 1));

		OpenGL::VertexArray vao(wrap, std::move(h));
		vao.DisableVertexAttribute(OpenGL::AttributeVariable(1, std::string(), OpenGL::AttributeType::Float));
	}

	TEST(VertexArrayTest, SetVertexAttributePointerCallsVertexAttribPointer) {
		MockOpenGL mockgl;
		EXPECT_CALL(mockgl, VertexAttribPointer(_, _, _, _, _, _));
		EXPECT_CALL(mockgl, DeleteVertexArrays(_, _));
		OpenGL::OpenGLWrapper wrap(mockgl);
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::VertexArray, 1));
		MockBuffer buff;
		EXPECT_CALL(buff, Bind());

		OpenGL::VertexArray vao(wrap, std::move(h));
		vao.SetVertexAttributePointer(OpenGL::AttributeVariable(1, std::string(), OpenGL::AttributeType::Float), buff, OpenGL::BufferDataPointer(0, OpenGL::DataType::Float));
	}

}