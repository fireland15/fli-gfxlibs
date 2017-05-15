#pragma once

#include "IWinUserWrapper.hpp"

#include <WinUser.h>
#include <wingdi.h>

namespace OpenGL {

	class WinUserWrapper : public IWinUserWrapper {
	public:
		virtual ~WinUserWrapper() { }
		virtual int ReleaseDeviceContext(HWND hWnd, HDC hdc) override;
		virtual void RegisterWindow(WindowClassStyles windowClassStyle, HINSTANCE hInstance, const char * className, WNDPROC wndProc) override;
		virtual HWND CreateNewWindow(const char * className, const char * windowName, int posX, int posY, int width, int height, HINSTANCE hInstance, LPVOID plParam) override;
		virtual HDC GetDeviceContext(HWND hWnd) override;
		virtual bool DestroyWnd(HWND hWnd) override;
	};

}