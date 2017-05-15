#include "Win32Provider.hpp"

#include "OpenGLWrapper.hpp"
#include "IWindowsGLProvider.hpp"
#include "IWinUserWrapper.hpp"
#include "IWinGdiWrapper.hpp"
#include "IWindowsWrapper.hpp"
#include "IGlewProvider.hpp"

OpenGL::Win32Provider::Win32Provider(OpenGL::OpenGLWrapper & gl, OpenGL::IGlewProvider & glew, OpenGL::IWindowsGLProvider & windowsGl, OpenGL::IWinUserWrapper & winUser, OpenGL::IWinGdiWrapper & winGdi, OpenGL::IWindowsWrapper & windows)
	: _gl(gl), _glew(glew), _windowsGl(windowsGl), _winUser(winUser), _winGdi(winGdi), _windows(windows) { }

OpenGL::OpenGLWrapper & OpenGL::Win32Provider::OpenGL() {
	return _gl;
}

OpenGL::IGlewProvider & OpenGL::Win32Provider::Glew() {
	return _glew;
}

OpenGL::IWindowsGLProvider & OpenGL::Win32Provider::WindowsGl() {
	return _windowsGl;
}

OpenGL::IWinUserWrapper & OpenGL::Win32Provider::WinUser() {
	return _winUser;
}

OpenGL::IWinGdiWrapper & OpenGL::Win32Provider::WinGDI() {
	return _winGdi;
}

OpenGL::IWindowsWrapper & OpenGL::Win32Provider::Windows() {
	return _windows;
}

