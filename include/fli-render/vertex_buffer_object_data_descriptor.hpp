#pragma once

#include <gl\glew.h>
#include <gl\GL.h>

#include "buffer_data_type_enum.hpp"
#include "vertex_attribute_normalize_enum.hpp"
#include "vertex_attribute.hpp""

namespace gfx {
	namespace render {
		
		struct VertexBufferObjectDataDescriptor {
			VertexAttribute Attribute;
			GLint Size;
			eBufferDataType DataType;
			eNormalize ShouldNormalize;
			GLsizei Stride;
			GLvoid* Offset;
		};

	}
}