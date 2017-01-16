#pragma once

#include <string>

#include <gl\glew.h>
#include <gl\GL.h>

namespace gfx {
	namespace render {

		class VertexAttribute {
		private:
			GLuint m_attributeIndex;
			GLuint m_program;
			std::string m_attributeName;

		public:
			VertexAttribute() = default;
			VertexAttribute(GLuint attributeIndex, GLuint program, std::string attributeName)
				: m_attributeIndex(attributeIndex)
				, m_program(program) 
				, m_attributeName(attributeName) { }

			VertexAttribute(const VertexAttribute& other) = default;
			VertexAttribute(VertexAttribute&& other) = delete;
			VertexAttribute& operator=(const VertexAttribute& other) = delete;
			VertexAttribute& operator=(VertexAttribute&& other) = delete;
			~VertexAttribute() = default;

			GLuint Index() {
				return m_attributeIndex;
			}

			GLuint Program() {
				return m_program;
			}

			std::string Name() {
				return m_attributeName;
			}
			
			void Enable() {
				glEnableVertexAttribArray(m_attributeIndex);
			}

			void Disable() {
				glDisableVertexAttribArray(m_attributeIndex);
			}
		};

	}
}