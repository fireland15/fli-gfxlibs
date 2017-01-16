#pragma once

#include <vector>
#include <assert.h>

#include <gl\glew.h>
#include <gl\GL.h>

#include "vertex_buffer_object.hpp"
#include "vertex_buffer_object_descriptor.hpp"

namespace gfx {
	namespace render {

		class VertexArrayObject {
		private:
			GLuint m_vao;
			bool m_isBound;

		public:
			VertexArrayObject() {
				glGenVertexArrays(1, &(m_vao));
			}

			VertexArrayObject(const VertexArrayObject& other) = delete;

			VertexArrayObject(VertexArrayObject&& other) = delete;

			VertexArrayObject& operator=(const VertexArrayObject& other) = delete;

			VertexArrayObject& operator=(VertexArrayObject&& other) = delete;

			~VertexArrayObject() {
				glDeleteVertexArrays(1, &m_vao);
				m_vao = 0;
			}

			void Bind() {
				glBindVertexArray(m_vao);
				m_isBound = true;
			}

			void Unbind() {
				glBindVertexArray(0);
				m_isBound = false;
			}

			void AttachBuffer(VertexBufferObject& buffer, VertexBufferObjectDescriptor desc) {
				if (!m_isBound) Bind();
				buffer.Bind();
				for (auto dataDesc : desc.Descriptors()) {
					glEnableVertexAttribArray(dataDesc.Attribute.Index());
					glVertexAttribPointer(dataDesc.Attribute.Index(), dataDesc.Size, dataDesc.DataType, dataDesc.ShouldNormalize, dataDesc.Stride, dataDesc.Offset);
				}
				buffer.Unbind();
			}
		};

	}
}