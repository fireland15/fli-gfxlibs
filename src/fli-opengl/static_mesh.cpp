#include "static_mesh.hpp"

namespace opengl {

	StaticMesh::StaticMesh(unsigned int numVertices, VertexArray vertexArray, std::vector<Buffer> vertexBuffers) 
		: m_vertexArray(vertexArray)
		, m_vertexBuffers(vertexBuffers)
		, m_numVertices(numVertices) { }

	void StaticMesh::Render() {
		m_vertexArray.Bind();
		glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
		m_vertexArray.Unbind();
	}
}