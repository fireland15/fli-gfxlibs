#pragma once

#include <memory>

#include "IShader.hpp"
#include "Handle.hpp"
#include <ShaderTypeEnum.hpp>

namespace OpenGL {

	class ShaderSource;
	class OpenGLWrapper;

	class Shader : public IShader {
	public:
		Shader(OpenGLWrapper& gl, std::unique_ptr<OpenGL::Handle> handle, ShaderType type);
		virtual ~Shader();
		virtual const OpenGL::Handle& Handle() override;
		virtual const ShaderSource& Source() override;
		virtual ShaderType Type() override;
	private:
		OpenGLWrapper& _gl;

		std::unique_ptr<OpenGL::Handle> _handle;
		ShaderType _type;
	};

}