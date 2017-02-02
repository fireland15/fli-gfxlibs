#include "static_mesh.hpp"

namespace opengl {

	StaticMesh::StaticMesh(unsigned int numVertices, up_VertexArray vertexArray, std::vector<up_Buffer> vertexBuffers) 
		: m_vertexArray(std::move(vertexArray))
		, m_vertexBuffers(std::move(vertexBuffers))
		, m_numVertices(numVertices) { }

	void StaticMesh::Render() {
		m_vertexArray->Bind();
		glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
		m_vertexArray->Unbind();
	}
}