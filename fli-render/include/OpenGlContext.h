#pragma once

#define _WIN32_LEAN_AND_MEAN
#define GLEW_STATIC

#include <Windows.h>
#include <assert.h>

#include <gl/glew.h>
#include <gl/wglew.h>
#include <gl/GL.h>

#include "Window.h"

#pragma comment(lib, "opengl32.lib") 

namespace fli {
	namespace gfx {
		namespace render {
			class OpenGlContext {
			private:
				HDC m_hDc;
				HGLRC m_hRc;

				Window& m_window;

			public:
				OpenGlContext(Window& window);

				~OpenGlContext();

				void Present();

			private:
				void InitializeGlew();

				void InitializeOpenGl();
			};
		}
	}
}