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
		if (!m_isBound) {
			glBindBuffer(m_target, m_obj);
			m_isBound = true;
		}
	}

	void Buffer::Unbind() {
		if (m_isBound) {
			glBindBuffer(m_target, 0);
			m_isBound = false;
		}
	}

	void Buffer::SetData(const Descriptor& desc) {
		m_description = desc;
		glBufferData(desc.Target, desc.Size, desc.pData, desc.Usage);
	}

	bool Buffer::IsBound() {
		return m_isBound;
	}

	Buffer::Targets Buffer::Target() {
		return m_description.Target;
	}

	Buffer::Usages Buffer::Usage() {
		return m_description.Usage;
	}

	const Buffer::Descriptor& Buffer::Description() {
		return m_description;
	}

}