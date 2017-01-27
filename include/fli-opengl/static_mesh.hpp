#pragma once

#include <vector>

#include <glm\glm.hpp>

#include "vertex_array.hpp"
#include "uniform_variable.hpp"

namespace opengl {

	class StaticMesh {
	public:
		StaticMesh() = default;

		StaticMesh(unsigned int numVertices, VertexArray vertexArray, std::vector<Buffer> vertexBuffer);

		void Render();

	private:
		VertexArray m_vertexArray;

		std::vector<Buffer> m_vertexBuffers;

		unsigned int m_numVertices;

	};

}