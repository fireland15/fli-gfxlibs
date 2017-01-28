#include "exceptions.hpp"

namespace opengl {

	shader_compilation_exception::shader_compilation_exception(std::string message)
		: m_message(message) { }

	const char* shader_compilation_exception::what() const noexcept {
		return m_message.c_str();
	}

	program_link_exception::program_link_exception(std::string message)
		: m_message(message) { }

	const char* program_link_exception::what() const noexcept {
		return m_message.c_str();
	}
}