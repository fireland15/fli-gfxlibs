#pragma once

#define _WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include <string>
#include <functional>
#include <glm.hpp>

namespace fli {
	namespace gfx {
		namespace render {
			class Window {
			private:
				glm::uvec2 m_screenPosition;
				glm::uvec2 m_size;
				std::string m_title;

				HWND m_hWnd;

				std::function<void(UINT, WPARAM, LPARAM)>* mp_msgCallback;
				bool m_shouldClose = false;

			public:
				Window(HINSTANCE hInstance, std::string title, glm::uvec2 screenPosition, glm::uvec2 size)
					: m_screenPosition(screenPosition)
					, m_size(size)
					, m_title(title)
					, mp_msgCallback(nullptr) {
				}

				void Create(HINSTANCE hInstance) {
					if (!hInstance) {
						throw std::exception("Could not get instance handle");
					}

					WNDCLASSEX windowClass;
					windowClass.cbSize = sizeof(WNDCLASSEX);
					windowClass.style = CS_OWNDC;
					windowClass.lpfnWndProc = WndProc;
					windowClass.cbClsExtra = 0;
					windowClass.cbWndExtra = 0;
					windowClass.hInstance = hInstance;
					windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
					windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
					windowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
					windowClass.lpszMenuName = NULL;
					windowClass.lpszClassName = m_title.c_str();
					windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

					RegisterClassEx(&windowClass);

					HWND hWnd = CreateWindowExA(
						NULL,
						m_title.c_str(),
						m_title.c_str(),
						WS_VISIBLE | WS_SYSMENU | WS_THICKFRAME,
						m_screenPosition.x, m_screenPosition.y,
						m_size.x, m_size.y,
						NULL,
						NULL,
						hInstance,
						this);

					if (!hWnd) {
						throw std::exception("Failed to create window");
					}

					m_hWnd = hWnd;
				}

				void Show() {
					ShowWindow(m_hWnd, SW_SHOW);
				}

				HWND GetHWnd() {
					return m_hWnd;
				}

				bool ShouldClose() {
					return m_shouldClose;
				}

				/*************************************************************
				* Windows Message Handling Methods
				**************************************************************/

				void SetMsgCallback(std::function<void(UINT, WPARAM, LPARAM)>* callback) {
					mp_msgCallback = callback;
				}

				void ProcessMessages() {
					MSG msg;
					while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
				}

				void WindowsMessageHandler(UINT msg, WPARAM wParam, LPARAM lParam) {
					if (mp_msgCallback != nullptr) {
						(*mp_msgCallback)(msg, wParam, lParam);
					}
					else {
						switch (msg)
						{
						case WM_CLOSE:
							DestroyWindow(m_hWnd);
							m_shouldClose = true;
							break;
						case WM_DESTROY:
							DestroyWindow(m_hWnd);
							m_shouldClose = true;
							break;
						default:
							break;
						}
					}
				}

				static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
					Window* pThis = nullptr;

					if (msg == WM_CREATE) {
						CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
						pThis = (Window*)pCreate->lpCreateParams;
						SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR) pThis);
						(pThis->m_hWnd) = hWnd;
					}
					else {
						pThis = (Window*) GetWindowLongPtr(hWnd, GWLP_USERDATA);
					}
					if (pThis) {
						pThis->WindowsMessageHandler(msg, wParam, lParam);
					}

					return DefWindowProc(hWnd, msg, wParam, lParam);
				}
			};
		}
	}
}