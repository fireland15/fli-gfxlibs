#include "vertex_array.hpp"

namespace opengl {

	VertexArray::VertexArray(GLuint obj) 
		: m_vao(obj)
		, m_isBound(false) {

	}

	VertexArray::VertexArray()
		: m_vao(0)
		, m_isBound(false) {
	}

	GLuint VertexArray::Obj() {
		return m_vao;
	}

	void VertexArray::Obj(GLuint obj) {
		m_vao = obj;
	}

	void VertexArray::EnableVertexAttribute(const AttributeVariable& attrib) {
		glEnableVertexAttribArray(attrib.Location().Value());
	}

	void VertexArray::SetVertexAttributePointer(const AttributeVariable& attrib, const Buffer::DataDescriptor& desc) {
		const AttributeLocation& loc = attrib.Location();
		glVertexAttribPointer(loc.Value(), desc.AttributeSize, desc.Type, desc.Normalize, desc.Stride, desc.Offset);
	}

	void VertexArray::Bind() {
		if (!m_isBound) {
			glBindVertexArray(m_vao);
			m_isBound = true;
		}
	}

	void VertexArray::Unbind() {
		if (m_isBound) {
			glBindVertexArray(0);
			m_isBound = false;
		}
	}

	bool VertexArray::IsBound() {
		return m_isBound;
	}

}