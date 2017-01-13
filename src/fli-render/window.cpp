#include "window.hpp"

namespace gfx {
	namespace render {

		Window::Window(HINSTANCE hInstance, std::string title, glm::uvec2 screenPosition, glm::uvec2 size)
			: m_screenPosition(screenPosition)
			, m_size(size)
			, m_title(title)
			, mp_msgCallback(nullptr)
			, mp_context(nullptr) {
			Create(hInstance);
		}

		Window::~Window() {
			if (mp_msgCallback) {
				delete mp_msgCallback;
			}
			if (mp_context) {
				delete mp_context;
			}
		}

		void 
		Window::Create(HINSTANCE hInstance) {
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

		HWND 
		Window::GetHWnd() {
			return m_hWnd;
		}

		glm::uvec2 
		Window::Dimensions() {
			return m_size;
		}

		bool 
		Window::ShouldClose() {
			return m_shouldClose;
		}

		OpenGlContext* 
		Window::GetOpenGlContext() {
			CreateOpenGlContext();
			return mp_context;
		}
		
		void 
		Window::SetMsgCallback(std::function<void(UINT, WPARAM, LPARAM)>* callback) {
			mp_msgCallback = callback;
		}

		void 
		Window::ProcessMessages() {
			MSG msg;
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		void 
		Window::WindowsMessageHandler(UINT msg, WPARAM wParam, LPARAM lParam) {
			if (mp_msgCallback != nullptr) {
				(*mp_msgCallback)(msg, wParam, lParam);
			}
			else {
				switch (msg)
				{
				case WM_SIZE:
					m_size.x = LOWORD(lParam);
					m_size.y = HIWORD(lParam);
					mp_context->ResizeViewport(m_size);
					break;
				case WM_CLOSE:
					if (mp_context) {
						delete mp_context;
						mp_context = nullptr;
					}
					DestroyWindow(m_hWnd);
					m_shouldClose = true;
					break;
				case WM_DESTROY:
					if (mp_context) {
						delete mp_context;
						mp_context = nullptr;
					}
					DestroyWindow(m_hWnd);
					m_shouldClose = true;
					break;
				default:
					break;
				}
			}
		}

		LRESULT CALLBACK 
		Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
			Window* pThis = nullptr;

			if (msg == WM_CREATE) {
				CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
				pThis = (Window*)pCreate->lpCreateParams;
				SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
				(pThis->m_hWnd) = hWnd;
			}
			else {
				pThis = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			}
			if (pThis) {
				pThis->WindowsMessageHandler(msg, wParam, lParam);
			}

			return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		void 
		Window::CreateOpenGlContext() {
			mp_context = new OpenGlContext(m_hWnd);
		}

	}
}