#include "window.hpp"

namespace gfx {
	namespace render {

		Window::Window(HINSTANCE hInstance, std::string title, glm::uvec2 screenPosition, glm::uvec2 size)
			: m_screenPosition(screenPosition)
			, m_size(size)
			, m_title(title)
			, mp_context(nullptr) {
			Create(hInstance);
		}

		Window::~Window() {
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

		opengl::OpenGlContext* 
		Window::GetOpenGlContext() {
			CreateOpenGlContext();
			return mp_context;
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
			switch (msg)
			{
			case WM_KEYDOWN:
			case WM_KEYUP:
				DispatchKeyboardInputMessages(msg, wParam);
				break;
			case WM_ACTIVATE:
			case WM_ENABLE:
				DispatchEnableMessages(wParam);
				break;
			case WM_SIZE:
				DispatchResizeMessages(wParam, lParam);
				break;
			case WM_CLOSE:
			case WM_DESTROY:
				DispatchCloseMessages();
				// Todo: Replace with a context disposal method
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
			mp_context = new opengl::OpenGlContext(m_hWnd);
		}

		/*************************************************************
		* Windows Message Handling Methods
		**************************************************************/

		void
		Window::AddCloseWindowHandler(std::function<void()> callback) {
			m_closeMessageHandlers.push_back(callback);
		}

		void
		Window::AddResizeWindowHandler(std::function<void(eWindowResize, glm::uvec2)> callback) {
			m_resizeMessageHandlers.push_back(callback);
		}

		void
		Window::AddKeyboardInputHandler(std::function<void(eKeyboardInput, eKeyState)> callback) {
			m_keyboardInputHandlers.push_back(callback);
		}

		void 
		Window::AddEnableWindowHandler(std::function<void()> callback) {
			m_enabledMessageHandlers.push_back(callback);
		}

		void 
		Window::AddDisableWindowHandler(std::function<void()> callback) {
			m_disabledMessageHandlers.push_back(callback);
		}

		/*************************************************************
		* Callback Calling Methods
		**************************************************************/

		void 
		Window::DispatchCloseMessages() {
			for (auto callback : m_closeMessageHandlers) {
				callback();
			}
		}

		void 
		Window::DispatchResizeMessages(WPARAM wParam, LPARAM lParam) {
			glm::uvec2 size(LOWORD(lParam), HIWORD(lParam));
			eWindowResize type;
			switch (wParam) {
			case SIZE_MAXHIDE:
				type = eWindowResize::MaxHide;
				break;
			case SIZE_MAXIMIZED:
				type = eWindowResize::Maximized;
				break;
			case SIZE_MAXSHOW:
				type = eWindowResize::MaxShow;
				break;
			case SIZE_MINIMIZED:
				type = eWindowResize::Minimized;
				break;
			case SIZE_RESTORED:
				type = eWindowResize::Restored;
				break;
			}

			for (auto callback : m_resizeMessageHandlers) {
				callback(type, size);
			}
		}

		void 
		Window::DispatchEnableMessages(WPARAM wParam) {
			if (BOOL(wParam) == true) {
				for (auto callback : m_enabledMessageHandlers) {
					callback();
				}
			}
			else {
				for (auto callback : m_disabledMessageHandlers) {
					callback();
				}
			}
		}

		void 
		Window::DispatchKeyboardInputMessages(UINT msg, WPARAM wParam){
			eKeyState state;
			if (msg == WM_KEYDOWN) {
				state = eKeyState::Down;
			}
			else if (msg == WM_KEYUP) {
				state = eKeyState::Up;
			}
			else {
				return;
			}

			eKeyboardInput vkCode = eKeyboardInput(wParam);

			for (auto callback : m_keyboardInputHandlers) {
				callback(vkCode, state);
			}
		}

	}
}