#include "WindowsWrapper.hpp"

#include <Windows.h>

HINSTANCE OpenGL::WindowsWrapper::RetrieveModuleHandle(const char * moduleName) {
	return (HINSTANCE)GetModuleHandleA(NULL);
}
