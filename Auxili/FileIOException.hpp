#pragma once

#include <exception>
#include <string>

namespace Auxili {

	class FileIOException : std::exception {
	public:
		FileIOException();
		FileIOException(std::string& filename);
		virtual ~FileIOException() { }
		virtual const char* what() const override;

	protected:
		std::string _filename;
	};

}