#pragma once

#include <OpenGLFacade/ShaderTypeEnum.hpp>

namespace OpenGL {

	class Handle;
	class ShaderSource;

	class IShader {
	public:
		virtual ~IShader() { }
		virtual const Handle& Handle() = 0; 
		virtual const ShaderSource& Source() = 0;
		virtual ShaderType Type() = 0;
	};

}