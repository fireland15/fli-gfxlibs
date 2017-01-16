#include "vertex_array.hpp"

namespace opengl {

	VertexArray::VertexArray() {
		glGenVertexArrays(1, &m_vao);
	}

}