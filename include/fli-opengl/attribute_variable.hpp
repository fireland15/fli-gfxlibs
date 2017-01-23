#pragma once

#include <string>

#include <glew\glew.h>
#include <GL\GL.h>

#include "attribute_location.hpp"

namespace opengl {

	class AttributeVariable {
	public:
		enum AttribType : GLenum {
			Float = GL_FLOAT,
			Vec2f = GL_FLOAT_VEC2,
			Vec3f = GL_FLOAT_VEC3,
			Vec4f = GL_FLOAT_VEC4,
			Mat2f = GL_FLOAT_MAT2,
			Mat3f = GL_FLOAT_MAT3,
			Mat4f = GL_FLOAT_MAT4,
			Mat2x3f = GL_FLOAT_MAT2x3,
			Mat2x4f = GL_FLOAT_MAT2x4,
			Mat3x2f = GL_FLOAT_MAT3x2,
			Mat3x4f = GL_FLOAT_MAT3x4,
			Mat4x2f = GL_FLOAT_MAT4x2,
			Mat4x3f = GL_FLOAT_MAT4x3,
			Int = GL_INT,
			Vec2i = GL_INT_VEC2,
			Vec3i = GL_INT_VEC3,
			Vec4i = GL_INT_VEC4,
			UnsignedInt = GL_UNSIGNED_INT,
			Vec2u = GL_UNSIGNED_INT_VEC2,
			Vec3u = GL_UNSIGNED_INT_VEC3,
			Vec4u = GL_UNSIGNED_INT_VEC4,
			Double = GL_DOUBLE,
			Vec2d = GL_DOUBLE_VEC2,
			Vec3d = GL_DOUBLE_VEC3,
			Vec4d = GL_DOUBLE_VEC4,
			Mat2d = GL_DOUBLE_MAT2,
			Mat3d = GL_DOUBLE_MAT3,
			Mat4d = GL_DOUBLE_MAT4,
			Mat2x3d = GL_DOUBLE_MAT2x3,
			Mat2x4d = GL_DOUBLE_MAT2x4,
			Mat3x2d = GL_DOUBLE_MAT3x2,
			Mat3x4d = GL_DOUBLE_MAT3x4,
			Mat4x2d = GL_DOUBLE_MAT4x2,
			Mat4x3d = GL_DOUBLE_MAT4x3
		};

		AttributeVariable(GLint location, std::string name, AttribType type);

		AttributeVariable();

		std::string Name() const;

		AttribType Type() const;

		bool IsValid();

		const AttributeLocation& Location() const;

	private:
		AttributeLocation m_location;

		std::string m_name;

		AttribType m_type;

		friend class Program;
	};

}