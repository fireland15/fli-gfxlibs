#pragma once

#define _WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include <GL\glew.h>
#include <GL\wglew.h>
#include <GL\GL.h>

#include <exception>
#include <memory>

#include <glm\glm.hpp>

#include "vertex_array.hpp"

namespace opengl {

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

		bool IsValid();

		void SwapBuffer();

		int MajorVersion();

		int MinorVersion();

		void ResizeViewport(const glm::uvec2& size);

	private:
		void InitializeGlew();

		void InitializeOpenGl();
	};

}