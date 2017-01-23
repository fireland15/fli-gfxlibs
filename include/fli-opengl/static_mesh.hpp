#pragma once

#include <vector>

#include <glm\glm.hpp>

namespace opengl {

	class StaticMesh {
	public:
		StaticMesh() = delete;
		StaticMesh(VertexArray& vertexArray);

	private:
		VertexArray& m_vertexArray;

	};

}