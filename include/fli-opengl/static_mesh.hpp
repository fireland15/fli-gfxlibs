#pragma once

#include <vector>
#include <memory>

#include <glm\glm.hpp>

#include "vertex_array.hpp"
#include "buffer.hpp"
#include "uniform_variable.hpp"

namespace opengl {

	typedef std::unique_ptr<VertexArray> up_VertexArray;
	typedef std::unique_ptr<Buffer> up_Buffer;

	class StaticMesh {
	public:
		StaticMesh() = default;

		StaticMesh(unsigned int numVertices, up_VertexArray vertexArray, std::vector<up_Buffer> vertexBuffer);

		void Render();

	private:
		up_VertexArray m_vertexArray;

		std::vector<up_Buffer> m_vertexBuffers;

		unsigned int m_numVertices;
	};

}