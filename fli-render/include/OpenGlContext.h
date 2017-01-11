#pragma once

#define _WIN32_LEAN_AND_MEAN
#define GLEW_STATIC

#include <Windows.h>
#include <assert.h>
#include <exception>

#include <gl/glew.h>
#include <gl/wglew.h>
#include <gl/GL.h>

#pragma comment(lib, "opengl32.lib") 

namespace fli {
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
				OpenGlContext(HWND hWnd);

				~OpenGlContext();

				void Present();

				int MajorVersion();

				int MinorVersion();

			private:
				void InitializeGlew();

				void InitializeOpenGl();
			};
		}
	}
}