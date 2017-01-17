#include "vertex_array.hpp"

namespace opengl {

	VertexArray::VertexArray(GLuint obj) 
		: m_vao(obj) {

	}

	VertexArray::VertexArray()
		: m_vao(0) {
	}

	GLuint VertexArray::Obj() {
		return m_vao;
	}

	void VertexArray::Obj(GLuint obj) {
		m_vao = obj;
	}

}