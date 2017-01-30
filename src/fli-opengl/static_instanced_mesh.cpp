#include "static_instanced_mesh.hpp"

namespace opengl {

	StaticInstancedMesh::StaticInstancedMesh(unsigned int numVertices, VertexArray vertexArray, std::vector<Buffer> vertexBuffers, std::vector<Buffer> instancedBuffers)
		: m_vertexArray(vertexArray)
		, m_vertexBuffers(vertexBuffers)
		, m_numVertices(numVertices)
		, m_instancedBuffers(instancedBuffers) { 
		for (Buffer& buffer : m_instancedBuffers) {
			if (buffer.Description().Usage != Buffer::Usages::DynamicDraw) {
				throw invalid_buffer_usage_exception("Instanced meshes require the instanced buffers to have a usage of DynamicDraw");
			}
		}
	}

	void StaticInstancedMesh::SetInstancedData(std::map<Buffer, std::pair<void*, unsigned int>> instanceData) {
		for (Buffer& buffer : m_instancedBuffers) {
			if (instanceData.count(buffer) > 0) {
				buffer.Bind();

				std::pair<void*, unsigned int> temp = instanceData[buffer];

				void* pData = temp.first;
				unsigned int size = temp.second;

				buffer.UpdateData(pData, size);

				buffer.Unbind();
			}
		}
	}

	void StaticInstancedMesh::Render(unsigned int numInstances) {

	}

}