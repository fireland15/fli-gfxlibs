#pragma once

#define _WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include <exception>
#include <memory>
#include <functional>

#include "IProgram.hpp"
#include "IShader.hpp"
#include "IVertexArray.hpp"
#include "IBuffer.hpp"
#include "ITexture.hpp"
#include "IProgramBuilder.hpp"
#include "IShaderBuilder.hpp"
#include "IBufferBuilder.hpp"

namespace OpenGL {

	class OpenGLWrapper;
	class IGlewProvider;
	class IWindowsGLProvider;
	class IWinUserWrapper;
	class IWinGdiWrapper;
	class IWindowsWrapper;
	class Win32Provider;

	class IBufferBuilder;
	class IProgramBuilder;
	class IShaderBuilder;
	class ITextureBuilder;

	class OpenGlContext {
	private:
		HDC m_hDc;
		HGLRC m_hRc;
		HWND m_hWnd;

		int _contextVersionMajor;
		int _contextVersionMinor;

		OpenGLWrapper& _opengl;
		IGlewProvider& _glew;
		IWindowsGLProvider& _wgl;
		IWinUserWrapper& _winUser;
		IWinGdiWrapper& _winGdi;
		IWindowsWrapper& _win;

	public:
		OpenGlContext(Win32Provider& win32, HWND hWnd);

		~OpenGlContext();

		bool IsValid();

		void SwapBuffer();

		int MajorVersion();

		int MinorVersion();

		void ResizeViewport(unsigned int width, unsigned int height);

		std::unique_ptr<IBuffer> NewBuffer(std::function<void(IBufferBuilder&)> func);

		std::unique_ptr<IShader> NewShader(std::function<void(IShaderBuilder&)> func);

		std::unique_ptr<IProgram> NewProgram(std::function<void(IProgramBuilder&)> func);

		std::unique_ptr<ITexture> NewTexture(std::function<void(ITextureBuilder&)> func);

		std::unique_ptr<IVertexArray> NewVertexArray();

	private:
		void InitializeGlew();

		void InitializeOpenGl();
	};

}