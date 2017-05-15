#pragma once

#include <Windows.h>
#include <string>
#include <glm/glm.hpp>
#include <memory>
#include <OpenGlContext.hpp>
#include <Win32Provider.hpp>

class OpenGL::IWinUserWrapper;

namespace Window {

	class Window {
	public:
		Window(HINSTANCE hInstance, std::string title, glm::uvec2 screenPosition, glm::uvec2 size, OpenGL::Win32Provider& win32);

		void ProcessMessages();

		OpenGL::OpenGlContext& CreateOpenGLContext();

		void WindowsMessageHandler(UINT msg, WPARAM wParam, LPARAM lParam);

		static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		HWND _hWnd;
		glm::uvec2 _size;
		glm::uvec2 _screenPosition;
		std::string _title;

		OpenGL::Win32Provider& _win32;

		std::unique_ptr<OpenGL::OpenGlContext> _openGL;

		void Create(HINSTANCE hInstance);
	};

}