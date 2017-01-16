#pragma once

#include <vector>

#include "vertex_buffer_object_data_descriptor.hpp"

namespace gfx {
	namespace render {

		class VertexBufferObjectDescriptor {
		private:
			std::vector<VertexBufferObjectDataDescriptor> m_dataDescriptors;

		public:
			VertexBufferObjectDescriptor() = default;
			VertexBufferObjectDescriptor(const VertexBufferObjectDescriptor& other) = default;
			VertexBufferObjectDescriptor(VertexBufferObjectDescriptor&& other) = delete;
			VertexBufferObjectDescriptor& operator=(const VertexBufferObjectDescriptor& other) = delete;
			VertexBufferObjectDescriptor& operator=(VertexBufferObjectDescriptor&& other) = delete;
			~VertexBufferObjectDescriptor() = default;

			void AddData(const VertexBufferObjectDataDescriptor dataDesc) {
				m_dataDescriptors.push_back(dataDesc);
			}

			const std::vector<VertexBufferObjectDataDescriptor>& Descriptors() {
				return m_dataDescriptors;
			}
		};

	}
}