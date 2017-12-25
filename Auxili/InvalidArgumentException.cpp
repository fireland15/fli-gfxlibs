#pragma once
#include <sstream>
#include "InvalidArgumentException.hpp"

Auxili::InvalidArgumentException::InvalidArgumentException() { }

Auxili::InvalidArgumentException::InvalidArgumentException(std::string & name, std::string & message) {
	_name = name;
	_message = message;
}

const char * Auxili::InvalidArgumentException::what() const {
	std::stringstream ss;
	ss << "Invalid Argument\n";
	if (_name.length() != 0) {
		ss << "Argument: " << _name << "\n";
	}
	if (_message.length() != 0) {
		ss << "Message: " << _message << "\n";
	}

	return ss.str().c_str();
}
