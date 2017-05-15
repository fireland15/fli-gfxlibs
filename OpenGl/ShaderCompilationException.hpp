#pragma once

#include <string>

#include "Exception.hpp"

namespace OpenGL {

	class ShaderCompilationException : public Exception {
	public:
		ShaderCompilationException();
		ShaderCompilationException(std::string errorLog);
		virtual std::string Message() override;

	private:
		std::string _errorLog;
	};

}