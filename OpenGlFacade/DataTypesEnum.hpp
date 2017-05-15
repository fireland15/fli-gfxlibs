#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl\GLEXT.h>

namespace OpenGL {

	enum class DataType : unsigned int {
		Byte = GL_BYTE,
		UnsignedByte = GL_UNSIGNED_BYTE,
		Short = GL_SHORT,
		UnsignedShort = GL_UNSIGNED_SHORT,
		Int = GL_INT,
		UnsignedInt = GL_UNSIGNED_INT,
		HalfFloat = GL_HALF_FLOAT,
		Float = GL_FLOAT,
		Double = GL_DOUBLE,
		Fixed = GL_FIXED,
		Int2_10_10_10_Rev = GL_INT_2_10_10_10_REV,
		UnsignedInt2_10_10_10_Rev = GL_UNSIGNED_INT_2_10_10_10_REV,
		UnsignedInt_10f_11f_11f_Rev = GL_UNSIGNED_INT_10F_11F_11F_REV
	};

}