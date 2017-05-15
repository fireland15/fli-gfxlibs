#include "ShaderCompilationException.hpp"

#include <sstream>

OpenGL::ShaderCompilationException::ShaderCompilationException() {

}

OpenGL::ShaderCompilationException::ShaderCompilationException(std::string errorLog) 
	: _errorLog(errorLog) {

}

std::string OpenGL::ShaderCompilationException::Message() {
	if (_errorLog.empty()) {
		return "The compilation of a shader failed";
	}
	else {
		std::stringstream ss;
		ss << "The compilation of a shader failed" << std::endl;
		ss << "Error Log" << std::endl;
		ss << _errorLog << std::endl;
		return ss.str();
	}
}