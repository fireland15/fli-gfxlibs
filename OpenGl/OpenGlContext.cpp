#include <glew.h>
#include "OpenGlContext.hpp"

#include <wglew.h>
#include <GL\GL.h>
#include <GL/GLEXT.h>

#include <Win32Provider.hpp>
#include <OpenGLWrapper.hpp>
#include <IWindowsGLProvider.hpp>
#include <IWinUserWrapper.hpp>
#include <IWinGdiWrapper.hpp>
#include <IWindowsWrapper.hpp>
#include <IGlewProvider.hpp>

#include "BufferBuilder.hpp"
#include "BufferDataBuilder.hpp"
#include <StateVariableEnum.hpp>
#include "ShaderBuilder.hpp"
#include "ProgramBuilder.hpp"
#include "VertexArray.hpp"
#include "TextureBuilder.hpp"

OpenGL::OpenGlContext::OpenGlContext(OpenGL::Win32Provider& win32, HWND hWnd)
	: m_hWnd(hWnd), _opengl(win32.OpenGL()), _glew(win32.Glew()), _wgl(win32.WindowsGl()), _winUser(win32.WinUser()), _winGdi(win32.WinGDI()), _win(win32.Windows()) {
	InitializeGlew();
	InitializeOpenGl();
}

OpenGL::OpenGlContext::~OpenGlContext() {
	_wgl.MakeCurrent(m_hDc, 0);
	_wgl.DeleteContext(m_hRc);
	_winUser.ReleaseDeviceContext(m_hWnd, m_hDc);

	m_hRc = 0;
	m_hDc = 0;
}

std::unique_ptr<OpenGL::IBuffer> OpenGL::OpenGlContext::NewBuffer(std::function<void(OpenGL::IBufferBuilder&)> func) {
	OpenGL::BufferDataBuilder dataBuilder;
	OpenGL::BufferBuilder builder(_opengl, dataBuilder);

	func(builder);

	return builder.Build();
}

bool OpenGL::OpenGlContext::IsValid() {
	if (m_hRc == 0 || m_hDc == 0) {
		return false;
	}
	return true;
}

void OpenGL::OpenGlContext::SwapBuffer() {
	_winGdi.SwapBuffer(m_hDc);
}

int OpenGL::OpenGlContext::MajorVersion() {
	return _contextVersionMajor;
}

int OpenGL::OpenGlContext::MinorVersion() {
	return _contextVersionMinor;
}

void OpenGL::OpenGlContext::ResizeViewport(unsigned int width, unsigned int height) {
	_opengl.Viewport(glm::uvec2(0, 0), glm::uvec2(width, height));
}

std::unique_ptr<OpenGL::IShader> OpenGL::OpenGlContext::NewShader(std::function<void(OpenGL::IShaderBuilder&)> func) {
	ShaderBuilder builder(_opengl);

	func(builder);

	return builder.Compile().Build();
}

std::unique_ptr<OpenGL::IProgram> OpenGL::OpenGlContext::NewProgram(std::function<void(OpenGL::IProgramBuilder&)> func) {
	ProgramBuilder builder(_opengl);

	func(builder);
		
	return builder.Build();
}

std::unique_ptr<OpenGL::IVertexArray> OpenGL::OpenGlContext::NewVertexArray() {
	return std::unique_ptr<IVertexArray>(new VertexArray(_opengl, std::move(_opengl.GenVertexArray())));
}

std::unique_ptr<OpenGL::ITexture> OpenGL::OpenGlContext::NewTexture(std::function<void(OpenGL::ITextureBuilder&)> func) {
	TextureBuilder builder(_opengl);

	func(builder);

	return builder.Build();
}

void OpenGL::OpenGlContext::InitializeGlew() {
	HINSTANCE hInstance = _win.RetrieveModuleHandle(nullptr);

	if (!hInstance) {
		throw std::exception("Could not get instance handle");
	}

	_winUser.RegisterWindow(WindowClassStyles::OwnDc, hInstance, "fake", DefWindowProc);

	HWND hWndFake = _winUser.CreateNewWindow("fake", "FAKE", 0, 0, 100, 100, hInstance, nullptr);

	if (!hWndFake) {
		throw std::exception("Unable to create window for GLEW initialization");
	}

	HDC tempDc = _winUser.GetDeviceContext(hWndFake);

	int iPixelFormat = _winGdi.SelectPixelFormat(tempDc, 0, 0, 24, 8, 0, 16, 0, 0, 0);

	if (iPixelFormat == 0) {
		throw std::exception("Unable to choose pixel format GLEW initialization");
	}

	if (!_winGdi.AssignPixelFormat(tempDc, iPixelFormat, 0, 0, 24, 8, 0, 16, 0, 0, 0)) {
		throw std::exception("Unable to set pixel format for GLEW initialization");
	}

	HGLRC hRCFake = _wgl.CreateContext(tempDc);
	_wgl.MakeCurrent(tempDc, hRCFake);

	if (_glew.Init() != _glew.Ok())
	{
		throw std::exception("GLEW initialization failed");
	}

	_wgl.MakeCurrent(NULL, NULL);
	_wgl.DeleteContext(hRCFake);
	_winUser.ReleaseDeviceContext(hWndFake, tempDc);
	_winUser.DestroyWnd(hWndFake);
}

void OpenGL::OpenGlContext::InitializeOpenGl() {
	m_hDc = _winUser.GetDeviceContext(m_hWnd);

	int pixelFormat;

	pixelFormat = _winGdi.SelectPixelFormat(m_hDc, 0, 0, 24, 0, 0, 16, 0, 0, 0);

	if (pixelFormat == 0) {
		throw std::exception("Unable to get pixel format to create context");
	}

	if (!_winGdi.AssignPixelFormat(m_hDc, pixelFormat, 0, 0, 24, 0, 0, 16, 0, 0, 0)) {
		throw std::exception("Failed to set pixel format");
	}

	int attribs[]{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 0
		//WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		//0
	};

	m_hRc = _wgl.CreateContext(m_hDc);
	//m_hRc = wglCreateContextAttribsARB(m_hDc, 0, attribs);
	if (!_wgl.MakeCurrent(m_hDc, m_hRc)) {
		throw std::exception("Failed to make render context current.");
	}

	_contextVersionMajor = _opengl.GetInteger(OpenGL::StateVariable::MajorVersion);
	_contextVersionMinor = _opengl.GetInteger(OpenGL::StateVariable::MinorVersion);
}