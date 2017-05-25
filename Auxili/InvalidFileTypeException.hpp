#pragma once

#include <exception>
#include <string>

namespace Auxili {

	class InvalidFileTypeException : std::exception {
	public:
		InvalidFileTypeException();
		InvalidFileTypeException(std::string& filename, std::string& expected);
		InvalidFileTypeException(std::string& filename, const char* expected);
		virtual ~InvalidFileTypeException() { }
		virtual const char* what() const override;

	protected:
		std::string _filename;
		std::string _expected;
	};

}