#pragma once

#include "IWindowsWrapper.hpp"

namespace OpenGL {

	class WindowsWrapper : public IWindowsWrapper {
	public:
		virtual HINSTANCE RetrieveModuleHandle(const char* moduleName);
	};

}