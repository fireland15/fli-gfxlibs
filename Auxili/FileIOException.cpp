#include "FileIOException.hpp"

#include <sstream>

Auxili::FileIOException::FileIOException() { }

Auxili::FileIOException::FileIOException(std::string & filename) 
 : _filename(filename) { }

const char * Auxili::FileIOException::what() const {
	if (!_filename.empty()) {
		std::stringstream ss;
		ss << "Error reading or writing " << _filename << ".";
		return ss.str().c_str();
	}
	else {
		return "Error reading or writing to a file";
	}
}
