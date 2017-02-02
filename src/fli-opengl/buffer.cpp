#include "buffer.hpp"

namespace opengl {
	
	/*************************************************************
	* Constructors
	**************************************************************/

	Buffer::Buffer()
		: m_obj(0)
		, m_isBound(false) {
		glGenBuffers(1, &m_obj);
	}

	Buffer::Buffer(Buffer&& other)
		: m_obj(0)
		, m_isBound(false)
		, m_description() {
		// copy to new object
		m_obj = other.m_obj;
		m_isBound = other.m_isBound;
		m_description = other.m_description;

		// set current object to default values
		other.m_obj = 0;
		other.m_isBound = false;
		other.m_description = Descriptor();
	}

	Buffer& Buffer::operator=(Buffer&& other) {
		if (this != &other) {
			if (m_obj != 0) {
				glDeleteBuffers(1, &m_obj);
			}

			// copy to new object
			m_obj = other.m_obj;
			m_isBound = other.m_isBound;
			m_description = other.m_description;

			// set current object to default values
			other.m_obj = 0;
			other.m_isBound = false;
			other.m_description = Descriptor();
		}
		return *this;
	}

	/*************************************************************
	* Destructor
	**************************************************************/

	Buffer::~Buffer() {
		if (m_obj != 0) {
			glDeleteBuffers(1, &m_obj);
		}
	}

	/*************************************************************
	* OpenGL Buffer Functions
	**************************************************************/

	void Buffer::Bind() {
		if (!m_isBound) {
			glBindBuffer(m_description.Target, m_obj);
			m_isBound = true;
		}
	}

	void Buffer::Unbind() {
		if (m_isBound) {
			glBindBuffer(m_description.Target, 0);
			m_isBound = false;
		}
	}

	void Buffer::SetData(const Descriptor& desc) {
		m_description = desc;
		if (m_description.pData != nullptr) {
			glBufferData(desc.Target, desc.Size, desc.pData, desc.Usage);
		}
	}

	void Buffer::UpdateData(void* pData, unsigned int size) {
		if (pData == nullptr) {
			throw std::exception("nullptr");
		}

		if (size == 0) {
			throw std::exception("array cannot be empty");
		}

		glBufferData(m_description.Target, size, pData, m_description.Usage);
	}

	/*************************************************************
	* Getter Methods
	**************************************************************/

	bool Buffer::IsBound() {
		return m_isBound;
	}

	gl::BufferTarget Buffer::Target() {
		return m_description.Target;
	}

	gl::BufferUsage Buffer::Usage() {
		return m_description.Usage;
	}

	const Buffer::Descriptor& Buffer::Description() {
		return m_description;
	}

	bool Buffer::IsValid() {
		return m_obj != 0;
	}

}