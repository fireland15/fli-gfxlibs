#include "InvalidFileTypeException.hpp"

#include <sstream>

Auxili::InvalidFileTypeException::InvalidFileTypeException() { }

Auxili::InvalidFileTypeException::InvalidFileTypeException(std::string & filename, std::string & expected) 
	: _filename(filename), _expected(expected) { }

Auxili::InvalidFileTypeException::InvalidFileTypeException(std::string & filename, const char * expected)
	: _filename(filename), _expected(expected) { }

const char * Auxili::InvalidFileTypeException::what() const {
	if (!_filename.empty()) {
		std::stringstream ss;
		ss << "Expected a '" << _expected << "' file, but received '" << _filename << "'.";
		return ss.str().c_str();
	}
	else {
		return "Unexpected file type received.";
	}
}
