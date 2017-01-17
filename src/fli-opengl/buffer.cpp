#include "buffer.hpp"

namespace opengl {

	Buffer::Buffer(GLuint obj, Targets target)
		: m_obj(obj)
		, m_target(target)
		, m_isBound(false) {
	}

	GLuint Buffer::Obj() {
		return m_obj;
	}

	void Buffer::Obj(GLuint obj) {
		m_obj = obj;
	}

	Buffer::Buffer()
		: m_obj(0) {
	}

	void Buffer::Bind() {
		glBindBuffer(m_target, m_obj);
		m_isBound = true;
	}

	void Buffer::Unbind() {
		glBindBuffer(m_target, 0);
		m_isBound = false;
	}

	void Buffer::Data(Targets target, GLsizeiptr size, void* data, Usage usage) {
		if (!m_isBound) Bind();
		glBufferData(target, size, data, usage);
	}

	bool Buffer::IsBound() {
		return m_isBound;
	}

}