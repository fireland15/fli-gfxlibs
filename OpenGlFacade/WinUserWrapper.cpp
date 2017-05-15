#include "WinUserWrapper.hpp"

int OpenGL::WinUserWrapper::ReleaseDeviceContext(HWND hWnd, HDC hdc) {
	return ReleaseDC(hWnd, hdc);
}

void OpenGL::WinUserWrapper::RegisterWindow(WindowClassStyles windowClassStyle, HINSTANCE hInstance, const char * className, WNDPROC wndProc) {
	WNDCLASSEX windowClass;
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = (unsigned int)windowClassStyle;
	windowClass.lpfnWndProc = wndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = className;
	windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	RegisterClassExA(&windowClass);
}

HWND OpenGL::WinUserWrapper::CreateNewWindow(const char * className, const char * windowName, int posX, int posY, int width, int height, HINSTANCE hInstance, LPVOID plParam) {
	return CreateWindowExA(
		NULL,
		className,
		windowName,
		WS_VISIBLE | WS_SYSMENU | WS_THICKFRAME,
		posX,
		posY,
		width,
		height,
		NULL,
		NULL,
		hInstance,
		plParam
	);
}

HDC OpenGL::WinUserWrapper::GetDeviceContext(HWND hWnd) {
	return GetDC(hWnd);
}

bool OpenGL::WinUserWrapper::DestroyWnd(HWND hWnd) {
	return DestroyWindow(hWnd);
}
