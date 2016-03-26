#pragma once

#include <exception>
#include <stdexcept>

class VulkanException : public std::runtime_error {
private:
	std::string m_what;
public:
	VulkanException(const std::string& message) : std::runtime_error(message) { m_what = message; }
	virtual const char* what() const throw() { return m_what.c_str(); }
};