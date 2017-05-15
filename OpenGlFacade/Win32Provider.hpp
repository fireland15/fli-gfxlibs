#pragma once

namespace OpenGL {

	class OpenGLWrapper;
	class IGlewProvider;
	class IWindowsGLProvider;
	class IWinUserWrapper;
	class IWinGdiWrapper;
	class IWindowsWrapper;

	class Win32Provider {
	public:
		Win32Provider(OpenGLWrapper&, IGlewProvider&, IWindowsGLProvider&, IWinUserWrapper&, IWinGdiWrapper&, IWindowsWrapper&);

		OpenGLWrapper& OpenGL();
		IGlewProvider& Glew();
		IWindowsGLProvider& WindowsGl();
		IWinUserWrapper& WinUser();
		IWinGdiWrapper& WinGDI();
		IWindowsWrapper& Windows();

	private:
		OpenGLWrapper& _gl;
		IGlewProvider& _glew;
		IWindowsGLProvider& _windowsGl;
		IWinUserWrapper& _winUser;
		IWinGdiWrapper& _winGdi;
		IWindowsWrapper& _windows;
	};

}