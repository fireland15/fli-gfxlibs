#include "attribute_variable.hpp"

namespace opengl {

	AttributeVariable::AttributeVariable(GLint location, std::string name, AttribType type)
		: m_location(location)
		, m_name(name)
		, m_type(type) { }

	AttributeVariable::AttributeVariable()
		: m_location(-1)
		, m_name("") { }

	std::string AttributeVariable::Name() const {
		return m_name;
	}

	AttributeVariable::AttribType AttributeVariable::Type() const {
		return m_type;
	}

	bool AttributeVariable::IsValid() {
		return m_location.Value() != -1;
	}

	const AttributeLocation& AttributeVariable::Location() const {
		return m_location;
	}

}