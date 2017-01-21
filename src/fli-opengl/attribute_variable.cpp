#include "attribute_variable.hpp"

namespace opengl {

	AttributeVariable::AttributeVariable(GLint location, std::string name)
		: m_location(location)
		, m_name(name) { }

	AttributeVariable::AttributeVariable()
		: m_location(-1)
		, m_name("") { }

	std::string AttributeVariable::Name() {
		return m_name;
	}

	bool AttributeVariable::IsValid() {
		return m_location.Value() != -1;
	}

	const AttributeLocation& AttributeVariable::Location() const {
		return m_location;
	}

}