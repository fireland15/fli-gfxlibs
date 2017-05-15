#include "WindowsGLProvider.hpp"

#include <Windows.h>

bool OpenGL::WindowsGLProvider::MakeCurrent(HDC hdc, HGLRC hglrc) {
	return wglMakeCurrent(hdc, hglrc);
}

void OpenGL::WindowsGLProvider::DeleteContext(HGLRC hglrc) {
	wglDeleteContext(hglrc);
}

HGLRC OpenGL::WindowsGLProvider::CreateContext(HDC hdc) {
	return wglCreateContext(hdc);
}
