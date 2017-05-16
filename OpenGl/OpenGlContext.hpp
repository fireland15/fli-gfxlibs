#pragma once

#define _WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include <exception>
#include <memory>
#include <functional>

namespace OpenGL {

	class OpenGLWrapper;

	class IBufferBuilder;
	class IProgramBuilder;
	class IShaderBuilder;
	class ITextureBuilder;

	class IBuffer;
	class IShader;
	class IProgram;
	class ITexture;
	class IVertexArray;

	class OpenGlContext {
	private:
		int _contextVersionMajor;
		int _contextVersionMinor;

		OpenGLWrapper& _opengl;

	public:
		OpenGlContext(OpenGLWrapper& gl);

		~OpenGlContext();

		int MajorVersion();

		int MinorVersion();

		void ResizeViewport(unsigned int width, unsigned int height);

		std::unique_ptr<IBuffer> NewBuffer(std::function<void(IBufferBuilder&)> func);

		std::unique_ptr<IShader> NewShader(std::function<void(IShaderBuilder&)> func);

		std::unique_ptr<IProgram> NewProgram(std::function<void(IProgramBuilder&)> func);

		std::unique_ptr<ITexture> NewTexture(std::function<void(ITextureBuilder&)> func);

		std::unique_ptr<IVertexArray> NewVertexArray();
	};

}