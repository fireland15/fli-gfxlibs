#include <gtest.h>
#include <gmock.h>

#include <Program.hpp>

#include "MockOpenGL.hpp"
#include "MockShader.hpp"

#include <AttributeVariable.hpp>
#include <UniformVariable.hpp>
#include <Handle.hpp>
#include <IShader.hpp>
#include <UniformNotFoundException.hpp>
#include <InvalidUniformAssignmentException.hpp>
#include <OpenGLWrapper.hpp>

using ::testing::_;
using ::testing::ReturnRef;
namespace {

	TEST(ProgramTest, UseCallsglUseProgram) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, UseProgram(1)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::AttributeVariable> avl;
		avl.emplace_back(0, "bob", OpenGL::AttributeType::Float);

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(1, "uncle", OpenGL::UniformType::Float);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), avl, uvl);

		p.Use();
	}

	TEST(ProgramTest, AttributeVariableReturnsVariable) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::AttributeVariable> avl;
		avl.emplace_back(0, "bob", OpenGL::AttributeType::Float);

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(1, "uncle", OpenGL::UniformType::Float);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), avl, uvl);

		auto & var = p.AttributeVariable(std::string("bob"));

		EXPECT_EQ(0, var.Location());
		EXPECT_EQ("bob", var.Name());
		EXPECT_EQ(OpenGL::AttributeType::Float, var.Type());
	}

	TEST(ProgramTest, UniformVariableReturnsVariable) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::AttributeVariable> avl;
		avl.emplace_back(0, "bob", OpenGL::AttributeType::Float);

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(1, "uncle", OpenGL::UniformType::Float);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), avl, uvl);

		auto & var = p.UniformVariable(std::string("uncle"));

		EXPECT_EQ(1, var.Location());
		EXPECT_EQ("uncle", var.Name());
		EXPECT_EQ(OpenGL::UniformType::Float, var.Type());
	}

	TEST(ProgramTest, SetUniformFloat_CallsProgramUniform1f) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniform1f(1, 0, 1.0f)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Float);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], (float)1.0f);
	}

	TEST(ProgramTest, SetUniformFloat_DoesNotCallProgramUniformWhenUniformNotFound) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Float);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Float), (float)1.0f), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformFloat_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Float);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Mat3d), (float)1.0f), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformVec2_CallsProgramUniform2f) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniform2f(_, _, _, _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec2f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], glm::vec2(1.0f, 1.0f));
	}

	TEST(ProgramTest, SetUniformVec2_DoesNotCallProgramUniformWhenUniformNotFound) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec2f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Vec2f), glm::vec2(1.0f, 1.0f)), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformVec2_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec2f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Mat3d), glm::vec2(1.0f, 1.0f)), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformVec3_CallsProgramUniform3f) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniform3f(_, _, _, _, _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec3f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], glm::vec3(1.0f, 1.0f, 1.0f));
	}

	TEST(ProgramTest, SetUniformVec3_DoesNotCallProgramUniformWhenUniformNotFound) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec3f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Vec3f), glm::vec3(1.0f, 1.0f, 1.0f)), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformVec3_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec3f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Mat3d), glm::vec3(1.0f, 1.0f, 1.0f)), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformVec4_CallsProgramUniform4f) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniform4f(_, _, _, _, _, _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec4f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], glm::vec4());
	}

	TEST(ProgramTest, SetUniformVec4_DoesNotCallProgramUniformWhenUniformNotFound) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec4f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Vec4f), glm::vec4()), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformVec4_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec4f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Mat3d), glm::vec4()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformInt_CallsProgramUniform1i) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniform1i(_, _, _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Int);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], 4);
	}

	TEST(ProgramTest, SetUniformInt_DoesNotCallProgramUniformWhenUniformNotFound) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Int);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Int), 4), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformInt_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Int);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Mat3d), 4), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformVec2i_CallsProgramUniform2i) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniform2i(_, _, _, _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec2i);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], glm::ivec2());
	}

	TEST(ProgramTest, SetUniformVec2i_DoesNotCallProgramUniformWhenUniformNotFound) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec2i);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Vec2i), glm::ivec2()), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformVec2i_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec2i);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Mat3d), glm::ivec2()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformVec3i_CallsProgramUniform3i) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniform3i(_, _, _, _, _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec3i);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], glm::ivec3());
	}

	TEST(ProgramTest, SetUniformVec3i_DoesNotCallProgramUniformWhenUniformNotFound) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec3i);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Vec3i), glm::ivec3()), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformVec3i_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec3i);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Mat3d), glm::ivec3()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformVec4i_CallsProgramUniform4i) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniform4i(_, _, _, _, _, _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec4i);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], glm::ivec4());
	}

	TEST(ProgramTest, SetUniformVec4i_DoesNotCallProgramUniformWhenUniformNotFound) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec4i);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Vec4i), glm::ivec4()), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformVec4i_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec4i);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Mat3d), glm::ivec4()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformUInt_CallsProgramUniform1ui) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniform1ui(_, _, _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::UnsignedInt);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], (unsigned int)1);
	}

	TEST(ProgramTest, SetUniformUInt_DoesNotCallProgramUniformWhenUniformNotFound) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::UnsignedInt);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::UnsignedInt), (unsigned int)1), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformUInt_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::UnsignedInt);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Mat3d), (unsigned int)1), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformVec2ui_CallsProgramUniform2ui) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniform2ui(_, _, _, _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec2u);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], glm::uvec2());
	}

	TEST(ProgramTest, SetUniformVec2ui_DoesNotCallProgramUniformWhenUniformNotFound) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec2u);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Vec2u), glm::uvec2()), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformVec2ui_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec2u);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Mat3d), glm::uvec2()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformVec3ui_CallsProgramUniform3ui) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniform3ui(_, _, _, _, _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec3u);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], glm::uvec3());
	}

	TEST(ProgramTest, SetUniformVec3ui_DoesNotCallProgramUniformWhenUniformNotFound) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec3u);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Vec3u), glm::uvec3()), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformVec3ui_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec3u);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Mat3d), glm::uvec3()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformVec4ui_CallsProgramUniform4ui) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniform4ui(_, _, _, _, _, _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec4u);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], glm::uvec4());
	}

	TEST(ProgramTest, SetUniformVec4ui_DoesNotCallProgramUniformWhenUniformNotFound) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec4u);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Vec4u), glm::uvec4()), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformVec4ui_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec4u);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Mat3d), glm::uvec4()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformFloatArray_CallsProgramUniform1fv) {
		std::vector<float> data;
		data.push_back(1.0f);
		data.push_back(1.0f);

		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniform1fv(_, _, data.size(), _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Float);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], data);
	}

	TEST(ProgramTest, SetUniformFloatArray_DoesNotCallProgramUniformWhenUniformNotFound) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Float);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Float), std::vector<float>()), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformFloatArray_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Float);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Mat3d), std::vector<float>()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformVec2Array_CallsProgramUniform2fv) {
		std::vector<glm::vec2> data;
		data.push_back(glm::vec2());
		data.push_back(glm::vec2());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniform2fv(_, _, data.size(), _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec2f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], data);
	}

	TEST(ProgramTest, SetUniformVec2Array_DoesNotCallProgramUniformWhenUniformNotFound) {
		std::vector<glm::vec2> data;
		data.push_back(glm::vec2());
		data.push_back(glm::vec2());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec2f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Vec2f), data), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformVec2Array_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec2f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Mat3d), std::vector<glm::vec2>()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformVec3Array_CallsProgramUniform3fv) {
		std::vector<glm::vec3> data;
		data.push_back(glm::vec3());
		data.push_back(glm::vec3());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniform3fv(_, _, data.size(), _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec3f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], data);
	}

	TEST(ProgramTest, SetUniformVec3Array_DoesNotCallProgramUniformWhenUniformNotFound) {
		std::vector<glm::vec3> data;
		data.push_back(glm::vec3());
		data.push_back(glm::vec3());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec3f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Vec3f), data), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformVec3Array_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec3f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Mat3d), std::vector<glm::vec3>()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformVec4Array_CallsProgramUniform4fv) {
		std::vector<glm::vec4> data;
		data.push_back(glm::vec4());
		data.push_back(glm::vec4());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniform4fv(_, _, data.size(), _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec4f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], data);
	}

	TEST(ProgramTest, SetUniformVec4Array_DoesNotCallProgramUniformWhenUniformNotFound) {
		std::vector<glm::vec4> data;
		data.push_back(glm::vec4());
		data.push_back(glm::vec4());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec4f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Vec4f), data), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformVec4Array_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec4f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Mat3d), std::vector<glm::vec4>()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformIntArray_CallsProgramUniform1iv) {
		std::vector<int> data;
		data.push_back(1);
		data.push_back(1);

		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniform1iv(_, _, data.size(), _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Int);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], data);
	}

	TEST(ProgramTest, SetUniformIntArray_DoesNotCallProgramUniformWhenUniformNotFound) {
		std::vector<int> data;
		data.push_back(1);
		data.push_back(1);

		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Int);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Int), data), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformIntArray_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Int);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Mat3d), std::vector<int>()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformVec2iArray_CallsProgramUniform2iv) {
		std::vector<glm::ivec2> data;
		data.push_back(glm::ivec2());
		data.push_back(glm::ivec2());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniform2iv(_, _, data.size(), _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec2i);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], data);
	}

	TEST(ProgramTest, SetUniformVec2iArray_DoesNotCallProgramUniformWhenUniformNotFound) {
		std::vector<glm::ivec2> data;
		data.push_back(glm::ivec2());
		data.push_back(glm::ivec2());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec2i);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Vec2i), data), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformVec2iArray_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec2i);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Mat3d), std::vector<glm::ivec2>()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformVec3iArray_CallsProgramUniform3iv) {
		std::vector<glm::ivec3> data;
		data.push_back(glm::ivec3());
		data.push_back(glm::ivec3());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniform3iv(_, _, data.size(), _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec3i);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], data);
	}

	TEST(ProgramTest, SetUniformVec3iArray_DoesNotCallProgramUniformWhenUniformNotFound) {
		std::vector<glm::ivec3> data;
		data.push_back(glm::ivec3());
		data.push_back(glm::ivec3());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec3i);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Vec3i), data), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformVec3iArray_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec3i);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Mat3d), std::vector<glm::ivec3>()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformVec4iArray_CallsProgramUniform4iv) {
		std::vector<glm::ivec4> data;
		data.push_back(glm::ivec4());
		data.push_back(glm::ivec4());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniform4iv(_, _, data.size(), _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec4i);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], data);
	}

	TEST(ProgramTest, SetUniformVec4iArray_DoesNotCallProgramUniformWhenUniformNotFound) {
		std::vector<glm::ivec4> data;
		data.push_back(glm::ivec4());
		data.push_back(glm::ivec4());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec4i);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Vec4i), data), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformVec4iArray_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec4i);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Mat3d), std::vector<glm::ivec4>()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformUIntArray_CallsProgramUniform1uiv) {
		std::vector<unsigned int> data;
		data.push_back(1);
		data.push_back(1);

		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniform1uiv(_, _, data.size(), _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::UnsignedInt);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], data);
	}

	TEST(ProgramTest, SetUniformUIntArray_DoesNotCallProgramUniformWhenUniformNotFound) {
		std::vector<unsigned int> data;
		data.push_back(1);
		data.push_back(1);

		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::UnsignedInt);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::UnsignedInt), data), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformUIntArray_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::UnsignedInt);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Mat3d), std::vector<unsigned int>()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformVec2uiArray_CallsProgramUniform2uiv) {
		std::vector<glm::uvec2> data;
		data.push_back(glm::uvec2());
		data.push_back(glm::uvec2());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniform2uiv(_, _, data.size(), _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec2u);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], data);
	}

	TEST(ProgramTest, SetUniformVec2uiArray_DoesNotCallProgramUniformWhenUniformNotFound) {
		std::vector<glm::uvec2> data;
		data.push_back(glm::uvec2());
		data.push_back(glm::uvec2());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec2u);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Vec2u), data), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformVec2uiArray_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec2u);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Mat3d), std::vector<glm::uvec2>()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformVec3uiArray_CallsProgramUniform3uiv) {
		std::vector<glm::uvec3> data;
		data.push_back(glm::uvec3());
		data.push_back(glm::uvec3());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniform3uiv(_, _, data.size(), _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec3u);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], data);
	}

	TEST(ProgramTest, SetUniformVec3uiArray_DoesNotCallProgramUniformWhenUniformNotFound) {
		std::vector<glm::uvec3> data;
		data.push_back(glm::uvec3());
		data.push_back(glm::uvec3());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec3u);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Vec3u), data), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformVec3uiArray_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec3u);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Mat3d), std::vector<glm::uvec3>()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformVec4uiArray_CallsProgramUniform4uiv) {
		std::vector<glm::uvec4> data;
		data.push_back(glm::uvec4());
		data.push_back(glm::uvec4());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniform4uiv(_, _, data.size(), _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec4u);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], data);
	}

	TEST(ProgramTest, SetUniformVec4uiArray_DoesNotCallProgramUniformWhenUniformNotFound) {
		std::vector<glm::uvec4> data;
		data.push_back(glm::uvec4());
		data.push_back(glm::uvec4());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec4u);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Vec4u), data), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformVec4uiArray_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Vec4u);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Mat3d), std::vector<glm::uvec4>()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformMat2Array_CallsProgramUniformMatrix2fv) {
		std::vector<glm::mat2> data;
		data.push_back(glm::mat2());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniformMatrix2fv(_, _, _, _, _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat2f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], data);
	}

	TEST(ProgramTest, SetUniformMat2Array_DoesNotCallProgramUniformWhenUniformNotFound) {
		std::vector<glm::mat2> data;
		data.push_back(glm::mat2());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat2f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Mat2f), data), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformMat2Array_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat2f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Float), std::vector<glm::mat2>()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformMat3Array_CallsProgramUniformMatrix3fv) {
		std::vector<glm::mat3> data;
		data.push_back(glm::mat3());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniformMatrix3fv(_, _, _, _, _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat3f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], data);
	}

	TEST(ProgramTest, SetUniformMat3Array_DoesNotCallProgramUniformWhenUniformNotFound) {
		std::vector<glm::mat3> data;
		data.push_back(glm::mat3());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat3f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Mat3f), data), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformMat3Array_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat3f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Float), std::vector<glm::mat3>()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformMat4Array_CallsProgramUniformMatrix4fv) {
		std::vector<glm::mat4> data;
		data.push_back(glm::mat4());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniformMatrix4fv(_, _, _, _, _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat4f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], data);
	}

	TEST(ProgramTest, SetUniformMat4Array_DoesNotCallProgramUniformWhenUniformNotFound) {
		std::vector<glm::mat4> data;
		data.push_back(glm::mat4());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat4f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Mat4f), data), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformMat4Array_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat4f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Float), std::vector<glm::mat4>()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformMat2x3Array_CallsProgramUniformMatrix2x3fv) {
		std::vector<glm::mat2x3> data;
		data.push_back(glm::mat2x3());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniformMatrix2x3fv(_, _, _, _, _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat2x3f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], data);
	}

	TEST(ProgramTest, SetUniformMat2x3Array_DoesNotCallProgramUniformWhenUniformNotFound) {
		std::vector<glm::mat2x3> data;
		data.push_back(glm::mat2x3());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat2x3f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Mat2x3f), data), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformMat2x3Array_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat2x3f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Float), std::vector<glm::mat2x3>()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformMat3x2Array_CallsProgramUniformMatrix3x2fv) {
		std::vector<glm::mat3x2> data;
		data.push_back(glm::mat3x2());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniformMatrix3x2fv(_, _, _, _, _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat3x2f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], data);
	}

	TEST(ProgramTest, SetUniformMat3x2Array_DoesNotCallProgramUniformWhenUniformNotFound) {
		std::vector<glm::mat3x2> data;
		data.push_back(glm::mat3x2());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat3x2f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Mat3x2f), data), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformMat3x2Array_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat3x2f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Float), std::vector<glm::mat3x2>()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformMat2x4Array_CallsProgramUniformMatrix2x4fv) {
		std::vector<glm::mat2x4> data;
		data.push_back(glm::mat2x4());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniformMatrix2x4fv(_, _, _, _, _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat2x4f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], data);
	}

	TEST(ProgramTest, SetUniformMat2x4Array_DoesNotCallProgramUniformWhenUniformNotFound) {
		std::vector<glm::mat2x4> data;
		data.push_back(glm::mat2x4());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat2x4f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Mat2x4f), data), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformMat2x4Array_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat2x4f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Float), std::vector<glm::mat2x4>()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformMat4x2Array_CallsProgramUniformMatrix4x2fv) {
		std::vector<glm::mat4x2> data;
		data.push_back(glm::mat4x2());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniformMatrix4x2fv(_, _, _, _, _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat4x2f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], data);
	}

	TEST(ProgramTest, SetUniformMat4x2Array_DoesNotCallProgramUniformWhenUniformNotFound) {
		std::vector<glm::mat4x2> data;
		data.push_back(glm::mat4x2());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat4x2f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Mat4x2f), data), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformMat4x2Array_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat4x2f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Float), std::vector<glm::mat4x2>()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformMat3x4Array_CallsProgramUniformMatrix3x4fv) {
		std::vector<glm::mat3x4> data;
		data.push_back(glm::mat3x4());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniformMatrix3x4fv(_, _, _, _, _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat3x4f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], data);
	}

	TEST(ProgramTest, SetUniformMat3x4Array_DoesNotCallProgramUniformWhenUniformNotFound) {
		std::vector<glm::mat3x4> data;
		data.push_back(glm::mat3x4());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat3x4f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Mat3x4f), data), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformMat3x4Array_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat3x4f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Float), std::vector<glm::mat3x4>()), OpenGL::InvalidUniformAssignmentException);
	}

	TEST(ProgramTest, SetUniformMat4x3Array_CallsProgramUniformMatrix4x3fv) {
		std::vector<glm::mat4x3> data;
		data.push_back(glm::mat4x3());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, ProgramUniformMatrix4x3fv(_, _, _, _, _)).Times(1);
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat4x3f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		p.SetUniform(uvl[0], data);
	}

	TEST(ProgramTest, SetUniformMat4x3Array_DoesNotCallProgramUniformWhenUniformNotFound) {
		std::vector<glm::mat4x3> data;
		data.push_back(glm::mat4x3());

		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat4x3f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "ben", OpenGL::UniformType::Mat4x3f), data), OpenGL::UniformNotFoundException);
	}

	TEST(ProgramTest, SetUniformMat4x3Array_ThrowsInvalidUniformAssignmentWhenTypeIsWrong) {
		MockOpenGL mgl;
		EXPECT_CALL(mgl, DeleteProgram(_));
		std::unique_ptr<OpenGL::Handle> h(new OpenGL::Handle(OpenGL::ObjectType::Program, 1));

		std::vector<OpenGL::UniformVariable> uvl;
		uvl.emplace_back(0, "uncle", OpenGL::UniformType::Mat4x3f);

		OpenGL::OpenGLWrapper wrap(mgl);
		OpenGL::Program p(wrap, std::move(h), std::vector<OpenGL::AttributeVariable>(), uvl);

		EXPECT_THROW(p.SetUniform(OpenGL::UniformVariable(1, "uncle", OpenGL::UniformType::Float), std::vector<glm::mat4x3>()), OpenGL::InvalidUniformAssignmentException);
	}
}