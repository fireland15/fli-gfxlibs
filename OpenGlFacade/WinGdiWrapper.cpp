#include "WinGdiWrapper.hpp"

#include <wingdi.h>

bool OpenGL::WinGdiWrapper::SwapBuffer(HDC hdc) {
	return SwapBuffers(hdc);
}

int OpenGL::WinGdiWrapper::SelectPixelFormat(
	HDC hdc, 
	unsigned long flags, 
	unsigned char pixelType, 
	unsigned char colorBits, 
	unsigned char alphaBits, 
	unsigned char accumBits, 
	unsigned char depthBits, 
	unsigned char stencilBits, 
	unsigned char auxBuffers, 
	unsigned char layerType) {

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = colorBits;
	pfd.cAlphaBits = alphaBits;
	pfd.cAccumBits = accumBits;
	pfd.cDepthBits = depthBits;
	pfd.cStencilBits = stencilBits;
	pfd.cAuxBuffers = auxBuffers;
	pfd.iLayerType = PFD_MAIN_PLANE;

	return ChoosePixelFormat(hdc, &pfd);
}

bool OpenGL::WinGdiWrapper::AssignPixelFormat(
	HDC hdc, 
	int pixelFormat, 
	unsigned long flags, 
	unsigned char pixelType, 
	unsigned char colorBits, 
	unsigned char alphaBits, 
	unsigned char accumBits, 
	unsigned char depthBits, 
	unsigned char stencilBits, 
	unsigned char auxBuffers, 
	unsigned char layerType) {

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = colorBits;
	pfd.cAlphaBits = alphaBits;
	pfd.cAccumBits = accumBits;
	pfd.cDepthBits = depthBits;
	pfd.cStencilBits = stencilBits;
	pfd.cAuxBuffers = auxBuffers;
	pfd.iLayerType = PFD_MAIN_PLANE;

	return SetPixelFormat(hdc, pixelFormat, &pfd);
}
