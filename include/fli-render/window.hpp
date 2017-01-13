#pragma once

#define _WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include <string>
#include <functional>
#include <glm\glm.hpp>

#include "opengl_context.hpp"

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

			OpenGlContext* mp_context;

		public:
			enum class Size {
				MaxHide,
				MaxShow,
				Maximize,
				Minimized,
				Restored
			};

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

			OpenGlContext* GetOpenGlContext();

			/*************************************************************
			* Windows Message Handling Methods
			**************************************************************/

			// Handles WM_CLOSE & WM_DESTROY
			void CloseWindowHandler(std::function<void()> callback);

			void ResizeWindowHandler(std::function<void(Size, glm::uvec2)> callback);

			void KeyboardInputHandler(std::function<void()> callback);

			/*************************************************************
			* Windows Message Handling Methods
			**************************************************************/

			void SetMsgCallback(std::function<void(UINT, WPARAM, LPARAM)>* callback);

			void ProcessMessages();

			void WindowsMessageHandler(UINT msg, WPARAM wParam, LPARAM lParam);

			static LRESULT CALLBACK WndProc(
				HWND hWnd, 
				UINT msg, 
				WPARAM wParam, 
				LPARAM lParam);

		private:
			void CreateOpenGlContext();
		};
	}
}