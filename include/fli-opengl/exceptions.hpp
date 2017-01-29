#pragma once

#include <string>
#include <exception>

namespace opengl {
	struct shader_compilation_exception : public std::exception {
		shader_compilation_exception(std::string message);

		const char* what() const noexcept;

	private:
		std::string m_message;
	};

	struct program_link_exception : public std::exception {
		program_link_exception(std::string message);

		const char* what() const noexcept;

	private:
		std::string m_message;
	};
}