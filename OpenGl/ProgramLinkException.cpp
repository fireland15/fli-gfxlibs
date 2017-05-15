#include "ProgramLinkException.hpp"

OpenGL::ProgramLinkException::ProgramLinkException() : _errorLog("Error Linking program") { }

OpenGL::ProgramLinkException::ProgramLinkException(std::string errorLog) 
	: _errorLog(errorLog) { }

std::string OpenGL::ProgramLinkException::Message() {
	return _errorLog;
}
