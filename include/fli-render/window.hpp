#pragma once

#define _WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include <vector>
#include <string>
#include <vector>
#include <functional>
#include <glm\glm.hpp>

#include "window_resize_enum.hpp"
#include "keyboard_input_enum.hpp"
#include <fli-opengl\context.hpp>

namespace gfx {
	namespace render {
		class Window {
		public:
		private:
			glm::uvec2 m_screenPosition;
			glm::uvec2 m_size;
			std::string m_title;

			HWND m_hWnd;
			std::vector<std::function<void()>> m_closeMessageHandlers;
			std::vector<std::function<void(eWindowResize, glm::uvec2)>> m_resizeMessageHandlers;
			std::vector<std::function<void()>> m_enabledMessageHandlers;
			std::vector<std::function<void()>> m_disabledMessageHandlers;
			std::vector<std::function<void(eKeyboardInput, eKeyState)>> m_keyboardInputHandlers;

			bool m_shouldClose = false;

			opengl::OpenGlContext* mp_context;

		public:

			Window(
				HINSTANCE hInstance, 
				std::string title, 
				glm::uvec2 screenPosition, 
				glm::uvec2 size);

			~Window();

			void Create(HINSTANCE hInstance);

			HWND GetHWnd();

			glm::uvec2 Dimensions();

			bool ShouldClose();

			/*************************************************************
			* Rendering Context Creation
			**************************************************************/

			opengl::OpenGlContext* GetOpenGlContext();

			/*************************************************************
			* Windows Message Handling Methods
			**************************************************************/

			// Handles WM_CLOSE & WM_DESTROY
			void AddCloseWindowHandler(std::function<void()> callback);

			// Handle WM_SIZE
			void AddResizeWindowHandler(std::function<void(eWindowResize, glm::uvec2)> callback);

			// Handles WM_KEYDOWN, WM_KEYUP and virtual key codes
			void AddKeyboardInputHandler(std::function<void(eKeyboardInput, eKeyState)> callback);

			// Handles WM_ENABLE && wParam == true
			void AddEnableWindowHandler(std::function<void()> callback);

			// Handles WM_ENABLE && wParam == false
			void AddDisableWindowHandler(std::function<void()> callback);

			/*************************************************************
			* Windows Message Handling Methods
			**************************************************************/

			void ProcessMessages();

			void WindowsMessageHandler(UINT msg, WPARAM wParam, LPARAM lParam);

			static LRESULT CALLBACK WndProc(
				HWND hWnd, 
				UINT msg, 
				WPARAM wParam, 
				LPARAM lParam);

		private:
			void CreateOpenGlContext();
			
			/*************************************************************
			* Callback Calling Methods
			**************************************************************/

			void DispatchCloseMessages();

			void DispatchResizeMessages(WPARAM wParam, LPARAM lParam);

			void DispatchEnableMessages(WPARAM wParam);

			void DispatchKeyboardInputMessages(UINT msg, WPARAM wParam);

		};
	}
}