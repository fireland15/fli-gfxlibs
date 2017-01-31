#include "static_instanced_mesh.hpp"

namespace opengl {

	StaticInstancedMesh::StaticInstancedMesh(unsigned int numVertices, VertexArray vertexArray, std::vector<Buffer> vertexBuffers, std::map<AttributeVariable, Buffer> instancedBuffers)
		: m_vertexArray(vertexArray)
		, m_vertexBuffers(vertexBuffers)
		, m_numVertices(numVertices)
		, m_instancedBuffers(instancedBuffers) { 
		for (std::pair<AttributeVariable, Buffer> attribBufferPair : m_instancedBuffers) {
			if (attribBufferPair.second.Description().Usage != Buffer::Usages::DynamicDraw) {
				throw invalid_buffer_usage_exception("Instanced meshes require the instanced buffers to have a usage of DynamicDraw");
			}
		}
	}

	void StaticInstancedMesh::SetInstancedData(std::vector<InstanceUpdateData> instanceData) {
		for (InstanceUpdateData attribDataPair : instanceData) {
			if (m_instancedBuffers.count(attribDataPair.Attribute) > 0) {
				Buffer buffer = m_instancedBuffers[attribDataPair.Attribute];
				buffer.UpdateData(attribDataPair.pData, attribDataPair.dataSize);
			}
		}
	}

	void StaticInstancedMesh::Render(unsigned int numInstances) {
		m_vertexArray.Bind();
		glDrawArraysInstanced(GL_TRIANGLES, 0, m_numVertices, numInstances);
		m_vertexArray.Unbind();
	}

}