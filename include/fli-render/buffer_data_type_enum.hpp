#pragma once

#include <gl\glew.h>
#include <gl\GL.h>

namespace gfx {
	namespace render {

		enum eBufferDataType : GLenum {
			Byte			= GL_BYTE,
			UnsignedByte	= GL_UNSIGNED_BYTE,
			Short			= GL_SHORT,
			UnsignedShort	= GL_UNSIGNED_SHORT,
			Int				= GL_INT,
			UnsignedInt		= GL_UNSIGNED_INT,
			HalfFloat		= GL_HALF_FLOAT,
			Float			= GL_FLOAT,
			Double			= GL_DOUBLE,
			Fixed			= GL_FIXED
		};

	}
}