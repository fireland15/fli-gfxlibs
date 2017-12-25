#pragma once

#include <exception>
#include <string>

namespace Auxili {

	class InvalidArgumentException : std::exception {
	public:
		InvalidArgumentException();
		InvalidArgumentException(std::string& name, std::string& message);
		virtual ~InvalidArgumentException() { }
		virtual const char* what() const override;

	protected:
		std::string _name;
		std::string _message;
	};

}