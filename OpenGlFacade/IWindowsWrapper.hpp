#pragma once

#include <Windows.h>

namespace OpenGL {

	class IWindowsWrapper {
	public:
		virtual HINSTANCE RetrieveModuleHandle(const char* moduleName) = 0;
	};

}