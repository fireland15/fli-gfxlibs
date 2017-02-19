#pragma once

#include <memory>
#include <map>
#include <vector>

#include "vertex_array.hpp"
#include "buffer.hpp"
#include "dynamic_buffer.hpp"
#include "attribute_variable.hpp"

namespace opengl {

	typedef std::unique_ptr<VertexArray> up_VertexArray;
	typedef std::unique_ptr<Buffer> up_Buffer;
	typedef std::unique_ptr<DynamicBuffer> up_DynamicBuffer;

	class DynamicMesh {
	public:
		struct UpdateData {
			AttributeVariable Attribute;
			void* pData;
			unsigned int DataSize;
		};

		DynamicMesh() = default;

		DynamicMesh(unsigned int numVertices, 
			up_VertexArray vertexArray, 
			std::vector<up_Buffer> vertexBuffers,
			std::map<AttributeVariable, up_DynamicBuffer, AttributeComparator> dynamicBuffers);

		void UpdateVertexData(std::vector<UpdateData> updateData);

		void Render();

	private:
		up_VertexArray m_vertexArray;

		std::vector<up_Buffer> m_vertexBuffers;

		unsigned int m_numVertices;
	};

}