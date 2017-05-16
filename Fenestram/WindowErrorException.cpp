#include "WindowErrorException.hpp"

Fenestram::WindowErrorException::WindowErrorException() {
	_message = std::string("There was an error with a window");
}

Fenestram::WindowErrorException::WindowErrorException(std::string & description)
	: _message(description) { }

std::string Fenestram::WindowErrorException::Message() {
	return _message;
}
