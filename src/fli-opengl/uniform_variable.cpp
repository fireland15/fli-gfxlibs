#include "uniform_variable.hpp"

namespace opengl {

	UniformVariable::UniformVariable()
		: m_location()
		, m_name("") { }

	UniformVariable::UniformVariable(UniformLocation location, std::string name, UniformVariable::UniformType type)
		: m_location(location)
		, m_name(name)
		, m_type(type) { }

	std::string UniformVariable::Name() const {
		return m_name;
	}

	UniformVariable::UniformType UniformVariable::Type() const {
		return m_type;
	}

	const UniformLocation& UniformVariable::Location() const {
		return m_location;
	}

	bool UniformVariable::IsValid() const {
		return m_location.Value() != -1;
	}

}