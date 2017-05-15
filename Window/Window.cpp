#include "Window.hpp"

#include <IWinUserWrapper.hpp>
#include <WindowClassStylesEnum.hpp>

Window::Window::Window(HINSTANCE hInstance, std::string title, glm::uvec2 screenPosition, glm::uvec2 size, OpenGL::Win32Provider& win32) 
	: _title(title), _size(size), _screenPosition(screenPosition), _win32(win32) {
	Create(hInstance);
}

void Window::Window::ProcessMessages() {
	MSG msg;
	while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}

OpenGL::OpenGlContext & Window::Window::CreateOpenGLContext() {
	_openGL = std::unique_ptr<OpenGL::OpenGlContext>(new OpenGL::OpenGlContext(_win32, _hWnd));

	return *_openGL;
}

void Window::Window::WindowsMessageHandler(UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_KEYDOWN:
	case WM_KEYUP:
		//DispatchKeyboardInputMessages(msg, wParam);
		break;
	case WM_ACTIVATE:
	case WM_ENABLE:
		//DispatchEnableMessages(wParam);
		break;
	case WM_SIZE:
		//DispatchResizeMessages(wParam, lParam);
		break;
	case WM_CLOSE:
	case WM_DESTROY:
		_win32.WinUser().DestroyWnd(_hWnd);
		break;
	default:
		break;
	}
}

LRESULT Window::Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	Window* pThis = nullptr;

	if (msg == WM_CREATE) {
		CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
		pThis = (Window*)pCreate->lpCreateParams;
		SetWindowLongPtrA(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
		(pThis->_hWnd) = hwnd;
	}
	else {
		pThis = (Window*)GetWindowLongPtrA(hwnd, GWLP_USERDATA);
	}
	if (pThis) {
		pThis->WindowsMessageHandler(msg, wParam, lParam);
	}

	return DefWindowProcA(hwnd, msg, wParam, lParam);
}

void Window::Window::Create(HINSTANCE hInstance) {
	if (!hInstance)
		throw std::exception("HINSTANCE not provided");

	_win32.WinUser().RegisterWindow(OpenGL::WindowClassStyles::OwnDc, hInstance, _title.c_str(), WndProc);

	HWND hWnd = _win32.WinUser().CreateNewWindow(_title.c_str(), _title.c_str(), _screenPosition.x, _screenPosition.y, _size.x, _size.y, hInstance, this);

	if (!hWnd)
		throw std::exception("Failed to create Window");
	_hWnd = hWnd;
}
