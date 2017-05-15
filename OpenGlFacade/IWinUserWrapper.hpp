#pragma once

#include "WindowClassStylesEnum.hpp"

#include <Windows.h>

namespace OpenGL {

	class IWinUserWrapper {
	public:
		virtual ~IWinUserWrapper() { }
		/// <summary>
		/// Releases a device context (DC), freeing it for use by other applications
		/// </summary>
		/// <param name="hWnd">A handle to the window whose DC is to be released</param>
		/// <param name="hdc">A handle to the DC to be released</param>
		/// <returns>Indicates whether the DC was released. If released it returns 1, otherwise 0</returns>
		virtual int ReleaseDeviceContext(HWND hWnd, HDC hdc) = 0;

		virtual void RegisterWindow(WindowClassStyles windowClassStyle, HINSTANCE hInstance, const char* className, WNDPROC wndProc) = 0;

		virtual HWND CreateNewWindow(const char* className, const char* windowName, int posX, int posY, int width, int height, HINSTANCE hInstance, LPVOID plParam) = 0;

		virtual HDC GetDeviceContext(HWND hWnd) = 0;

		virtual bool DestroyWnd(HWND hWnd) = 0;
	};

}