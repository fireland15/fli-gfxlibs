#pragma once

#include <gl\glew.h>
#include <gl\GL.h>

namespace gfx {
	namespace render {

		enum eNormalize : GLboolean {
			ShouldNormalize		= GL_TRUE,
			ShouldNotNormalize	= GL_FALSE
		};

	}
}