#pragma once

#include "Exception.hpp"
#include <string>

namespace OpenGL {

	class InvalidTextureDataException : Exception {
	public:
		InvalidTextureDataException();
		InvalidTextureDataException(std::string& message);
		virtual std::string Message() override;

	private:
		std::string _message;
	};

}