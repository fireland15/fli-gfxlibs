#include "static_instanced_mesh.hpp"

namespace opengl {

	StaticInstancedMesh::StaticInstancedMesh(
		unsigned int numVertices, 
		up_VertexArray vertexArray, 
		std::vector<up_Buffer> vertexBuffers, 
		std::map<AttributeVariable, up_DynamicBuffer, AttributeComparator> instancedBuffers)
		: m_vertexArray(std::move(vertexArray))
		, m_vertexBuffers(std::move(vertexBuffers))
		, m_numVertices(numVertices)
		, m_instancedBuffers(std::move(instancedBuffers)) { 
		for (std::pair<const AttributeVariable, up_DynamicBuffer> & attribBufferPair : m_instancedBuffers) {
			if (attribBufferPair.second->Description().Usage != gl::BufferUsage::DynamicDraw) {
				throw invalid_buffer_usage_exception("Instanced meshes require the instanced buffers to have a usage of DynamicDraw");
			}
		}
	}

	void StaticInstancedMesh::SetInstancedData(std::vector<InstanceUpdateData> instanceData) {
		for (InstanceUpdateData attribDataPair : instanceData) {
			if (m_instancedBuffers.count(attribDataPair.Attribute) > 0) {
				DynamicBuffer& buffer = *(m_instancedBuffers[attribDataPair.Attribute]);
				buffer.Bind();
				buffer.UpdateData<DynamicBuffer::SimpleUpdatePolicy>(attribDataPair.pData, attribDataPair.dataSize);
				buffer.Unbind();
			}
		}
	}

	void StaticInstancedMesh::Render(unsigned int numInstances) {
		m_vertexArray->Bind();
		glDrawArraysInstanced(GL_TRIANGLES, 0, m_numVertices, numInstances);
		m_vertexArray->Unbind();
	}

}