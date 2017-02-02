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

	struct invalid_buffer_usage_exception : public std::exception {
		invalid_buffer_usage_exception(std::string message);

		const char* what() const noexcept;

	private:
		std::string m_message;
	};

	struct objection_creation_exception : public std::exception {
		objection_creation_exception(std::string message);

		const char* what() const noexcept;

	private:
		std::string m_message;
	};
}