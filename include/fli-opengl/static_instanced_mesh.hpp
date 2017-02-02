#pragma once

#include <vector>
#include <map>
#include <memory>

#include <glm\glm.hpp>

#include "vertex_array.hpp"
#include "buffer.hpp"
#include "attribute_variable.hpp"
#include "uniform_variable.hpp"
#include "exceptions.hpp"

namespace opengl {

	struct InstanceUpdateData {
		AttributeVariable Attribute;
		void* pData;
		// the size of pData in bytes
		unsigned int dataSize;
	};

	class StaticInstancedMesh {
	public:
		// Can throw invalid_buffer_usage_exception if any of the instanced buffers are not DynamicDraw
		StaticInstancedMesh(
			unsigned int numVertices,
			up_VertexArray vertexArray, 
			std::vector<up_Buffer> vertexBuffer, 
			std::map<AttributeVariable, up_Buffer, AttributeComparator> instancedBuffers);

		// Each buffer will need to copy  the void* array of size unsigned int. Only buffers that require updating get updated.
		void SetInstancedData(std::vector<InstanceUpdateData> instanceData);

		void Render(unsigned int numInstances);

	private:
		up_VertexArray m_vertexArray;

		std::vector<up_Buffer> m_vertexBuffers;

		std::map<AttributeVariable, up_Buffer, AttributeComparator> m_instancedBuffers;

		unsigned int m_numVertices;

	};

}