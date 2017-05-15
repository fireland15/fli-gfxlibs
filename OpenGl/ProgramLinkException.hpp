#pragma once

#include "Exception.hpp"

namespace OpenGL {

	class ProgramLinkException : public Exception {
	public:
		ProgramLinkException();
		ProgramLinkException(std::string errorLog);
		virtual std::string Message();
	private:
		std::string _errorLog;
	};

}