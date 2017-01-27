#include "uniform_location.hpp"

namespace opengl {

	UniformLocation::UniformLocation(GLint location)
		: m_value(location) { }

	UniformLocation::UniformLocation()
		: m_value(-1) { }

	GLint UniformLocation::Value() const {
		return m_value;
	}

}