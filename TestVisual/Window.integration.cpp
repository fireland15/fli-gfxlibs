#include "Window.integration.hpp"

#include <Win32Provider.hpp>
#include <WinUserWrapper.hpp>
#include <WindowsWrapper.hpp>
#include <GlewProvider.hpp>
#include <WinGdiWrapper.hpp>
#include <RealOpenGL.hpp>
#include <WindowsGLProvider.hpp>
#include <OpenGLWrapper.hpp>

#include <Window.hpp>

void WindowCreation() {
	OpenGL::WindowsWrapper windows;
	OpenGL::WinUserWrapper winUser;
	OpenGL::GlewProvider glew;
	OpenGL::WinGdiWrapper gdi;
	OpenGL::WindowsGLProvider winGl;
	OpenGL::RealOpenGL realGl;
	OpenGL::OpenGLWrapper gl(realGl);

	OpenGL::Win32Provider win32(gl, glew, winGl, winUser, gdi, windows);

	Window::Window w((HINSTANCE)(GetModuleHandle(NULL)), std::string("Create Window"), glm::uvec2(0.0f, 0.0f), glm::uvec2(300, 300), win32);

	Sleep(1000);
}
