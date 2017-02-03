#include "vertex_array.hpp"

namespace opengl {

	/*************************************************************
	* Constructors
	**************************************************************/

	VertexArray::VertexArray()
		: m_obj(0)
		, m_isBound(false) {
		glGenVertexArrays(1, &m_obj);
	}

	VertexArray::VertexArray(VertexArray&& other) 
		: m_obj(0)
		, m_isBound(false) {
		// copy info from other
		m_obj = other.m_obj;
		m_isBound = other.m_isBound;

		// set other to default values
		other.m_obj = 0;
		other.m_isBound = false;
	}

	VertexArray& VertexArray::operator=(VertexArray&& other) {
		if (this != &other) {
			if (m_obj != 0) {
				glDeleteVertexArrays(1, &m_obj);
			}

			// copy info from other
			m_obj = other.m_obj;
			m_isBound = other.m_isBound;

			// set other to default values
			other.m_obj = 0;
			other.m_isBound = false;
		}
		return *this;
	}

	/*************************************************************
	* Destructor
	**************************************************************/

	VertexArray::~VertexArray() {
		if (m_obj != 0) {
			glDeleteVertexArrays(1, &m_obj);
		}
	}

	/*************************************************************
	* OpenGL Vertex Array Functions
	**************************************************************/

	void VertexArray::EnableVertexAttribute(const AttributeVariable& attrib) {
		glEnableVertexAttribArray(attrib.Location().Value());
	}

	void VertexArray::SetVertexAttributePointer(const AttributeVariable& attrib, const BufferDataDescriptor& desc) {
		const AttributeLocation& loc = attrib.Location();
		glVertexAttribPointer(loc.Value(), desc.AttributeSize, desc.Type, desc.Normalize, desc.Stride, desc.Offset);
	}

	void VertexArray::SetVertexAttributeDivisor(const AttributeVariable & attrib, unsigned int divisor) {
		glVertexAttribDivisor(attrib.Location().Value(), divisor);
	}

	void VertexArray::Bind() {
		if (!m_isBound) {
			glBindVertexArray(m_obj);
			m_isBound = true;
		}
	}

	void VertexArray::Unbind() {
		if (m_isBound) {
			glBindVertexArray(0);
			m_isBound = false;
		}
	}

	/*************************************************************
	* Getter Methods
	**************************************************************/

	bool VertexArray::IsBound() {
		return m_isBound;
	}

	bool VertexArray::IsValid() {
		return m_obj != 0;
	}

}