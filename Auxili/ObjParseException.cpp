#include "ObjParseException.hpp"

Auxili::ObjParseException::ObjParseException(std::string & message)
	: _message(message) { }

std::string & Auxili::ObjParseException::Message() {
	return _message;
}
