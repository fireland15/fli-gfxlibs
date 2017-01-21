#include "attribute_location.hpp"

namespace opengl {

	AttributeLocation::AttributeLocation(GLint location) 
		: m_value(location) { }

	AttributeLocation::AttributeLocation() 
		: m_value(-1) { }

	GLint AttributeLocation::Value() const {
		return m_value;
	}

}