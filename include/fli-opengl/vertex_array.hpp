#pragma once

#include <glew\glew.h>
#include <GL\GL.h>

#include "attribute_variable.hpp"
#include "buffer.hpp"

namespace opengl {

	class VertexArray {
	private:
		VertexArray(GLuint obj);

		GLuint Obj();

		void Obj(GLuint);

	public:
		VertexArray();

		void EnableVertexAttribute(const AttributeVariable& attrib);

		void SetVertexAttributePointer(const AttributeVariable& attrib, const Buffer::DataDescriptor& desc);

		// divisor is the number of instances that will be rendered before the attrib is updated.
		void SetVertexAttributeDivisor(const AttributeVariable& attrib, unsigned int divisor);

		void Bind();

		void Unbind();

		bool IsBound();

		friend class GL;

	private:
		bool m_isBound;

		GLuint m_vao;
	};

}