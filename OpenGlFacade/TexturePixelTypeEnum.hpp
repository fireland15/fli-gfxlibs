#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLEXT.h>

namespace OpenGL {

	enum class TexturePixelType : unsigned int {
		Red = GL_RED,
		RG = GL_RG,
		RGB = GL_RGB,
		BGR = GL_BGR,
		RGBA = GL_RGBA,
		BGRA = GL_BGRA,
		RedInteger = GL_RED_INTEGER,
		RGInteger = GL_RG_INTEGER,
		RGBInteger = GL_RGB_INTEGER,
		BGRInteger = GL_BGR_INTEGER,
		RGBAInteger = GL_RGBA_INTEGER,
		BGRAInteger = GL_BGRA_INTEGER,
		StencilIndex = GL_STENCIL_INDEX,
		DepthComponent = GL_DEPTH_COMPONENT,
		DepthStencil = GL_DEPTH_STENCIL
	};

}