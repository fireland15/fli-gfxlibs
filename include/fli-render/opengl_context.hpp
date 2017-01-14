#pragma once

#define _WIN32_LEAN_AND_MEAN
#define GLEW_STATIC

#include <Windows.h>
#include <assert.h>
#include <exception>

#include <GL\glew.h>
#include <GL\wglew.h>
#include <gl\GL.h>
#include <glm\glm.hpp>

namespace gfx {
	namespace render {
		class OpenGlContext {
		private:
			HDC m_hDc;
			HGLRC m_hRc;
			HWND m_hWnd;

			int m_contextVersionMajor;
			int m_contextVersionMinor;

		public:
			OpenGlContext() { }

			OpenGlContext(HWND hWnd);

			~OpenGlContext();

			void SwapBuffer();

			void MakeCurrent();

			int MajorVersion();

			int MinorVersion();

			void ResizeViewport(const glm::uvec2& size);

		private:
			void InitializeGlew();

			void InitializeOpenGl();
		};
	}
}