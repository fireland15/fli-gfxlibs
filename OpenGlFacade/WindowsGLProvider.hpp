#pragma once

#include "IWindowsGLProvider.hpp"

namespace OpenGL {

	class WindowsGLProvider : public IWindowsGLProvider {
	public:
		virtual bool MakeCurrent(HDC hdc, HGLRC hglrc) override;
		virtual void DeleteContext(HGLRC hglrc) override;
		virtual HGLRC CreateContext(HDC hdc) override;

	};

}