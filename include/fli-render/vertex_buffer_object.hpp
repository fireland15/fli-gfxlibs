#pragma once

#include <gl\glew.h>
#include <gl\wglew.h>
#include <gl\GL.h>
#ifdef _DEBUG
#include <assert.h>
#endif

#include "vertex_buffer_object_target_enum.hpp"
#include "vertex_buffer_object_usage_enum.hpp"

namespace gfx {
	namespace render {

		class VertexBufferObject {
		private:
			GLuint m_vbo;
			eVertexBufferObjectTarget m_target;
			bool m_isBound;

		public:
			VertexBufferObject(eVertexBufferObjectTarget target)
				: m_vbo(0)
				, m_target(target)
				, m_isBound(false) {
				glGenBuffers(1, &m_vbo);
			}

			VertexBufferObject(const VertexBufferObject& other) = delete;

			VertexBufferObject(VertexBufferObject&& other) = delete;

			VertexBufferObject& operator=(const VertexBufferObject& other) = delete;

			VertexBufferObject& operator=(VertexBufferObject&& other) = delete;

			~VertexBufferObject() {
				glDeleteBuffers(1, &m_vbo);
				m_vbo = 0;
			}

			void Bind() {
				glBindBuffer(m_target, m_vbo);
				m_isBound = true;
			}

			void Unbind() {
				glBindBuffer(m_target, 0);
				m_isBound = false;
			}

			void Data(eVertexBufferObjectTarget target, GLsizeiptr size, void* data, eVertexBufferObjectUsage usage) {
				if (!m_isBound) Bind();
				glBufferData(target, size, data, usage);
			}

			bool IsBound() {
				return m_isBound;
			}
		};

	}
}