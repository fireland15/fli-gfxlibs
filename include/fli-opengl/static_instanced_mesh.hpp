#pragma once

#include <vector>
#include <map>

#include <glm\glm.hpp>

#include "vertex_array.hpp"
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
		StaticInstancedMesh() = default;

		// Can throw invalid_buffer_usage_exception if any of the instanced buffers are not DynamicDraw
		StaticInstancedMesh(
			unsigned int numVertices,
			VertexArray vertexArray, 
			std::vector<Buffer> vertexBuffer, 
			std::map<AttributeVariable, Buffer> instancedBuffers);

		// Each buffer will need to copy the void* array of size unsigned int. Only buffers that require updating get updated.
		void SetInstancedData(std::vector<InstanceUpdateData> instanceData);

		void Render(unsigned int numInstances);

	private:
		VertexArray m_vertexArray;

		std::vector<Buffer> m_vertexBuffers;

		std::map<AttributeVariable, Buffer> m_instancedBuffers;

		unsigned int m_numVertices;

	};

}