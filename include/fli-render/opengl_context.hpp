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

#include "opengl_resource_manager.hpp"

namespace gfx {
	namespace render {
		class OpenGlContext {
		private:
			HDC m_hDc;
			HGLRC m_hRc;
			HWND m_hWnd;

			OpenGlResourceManager m_resources;

			int m_contextVersionMajor;
			int m_contextVersionMinor;

		public:
			OpenGlContext() { }

			OpenGlContext(HWND hWnd);

			~OpenGlContext();

			bool IsValid();

			void SwapBuffer();

			int MajorVersion();

			int MinorVersion();

			void ResizeViewport(const glm::uvec2& size);

			OpenGlResourceManager& ResourceManager();

		private:
			void InitializeGlew();

			void InitializeOpenGl();
		};
	}
}