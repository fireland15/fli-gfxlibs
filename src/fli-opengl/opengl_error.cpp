#include "opengl_error.hpp"

namespace opengl {

	OpenGlError::OpenGlError(Error error)
		: m_error(error) { }

	bool OpenGlError::IsError() {
		return m_error != Error::NoError;
	}

	std::string OpenGlError::ToString() {
		switch (m_error) {
		case Error::NoError:
			return "No Error";
			break;
		case Error::InvalidEnum:
			return "Invalid enum";
			break;
		case Error::InvalidValue:
			return "Invalid value";
			break;
		case Error::InvalidOperation:
			return "Invalid operation";
			break;
		case Error::StackOverflow:
			return "Stack overflow";
			break;
		case Error::StackUnderflow:
			return "Stack underflow";
			break;
		case Error::OutOfMemory:
			return "Out of memory";
			break;
		case Error::Unknown:
			return "Unknown";
			break;
		default:
			return "Unknown";
			break;
		}
	}

}