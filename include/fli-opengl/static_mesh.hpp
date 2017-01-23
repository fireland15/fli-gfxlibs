#pragma once

#include "vertex_array.hpp"

namespace opengl {

	class StaticMesh {
	public:
		StaticMesh() = delete;
		StaticMesh(VertexArray& vertexArray);

	private:
		VertexArray& m_vertexArray;

	};

}