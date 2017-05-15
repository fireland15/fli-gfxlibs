#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLEXT.h>

namespace OpenGL {

	enum class TextureParameter : unsigned int {
		DepthStencilTextureMode = GL_DEPTH_STENCIL_TEXTURE_MODE,
		TextureBaseLevel = GL_TEXTURE_BASE_LEVEL,
		TextureCompareFunc = GL_TEXTURE_COMPARE_FUNC,
		TextureCompareMode = GL_TEXTURE_COMPARE_MODE,
		TextureLodBias = GL_TEXTURE_LOD_BIAS,
		TextureMinFilter = GL_TEXTURE_MIN_FILTER,
		TextureMagFilter = GL_TEXTURE_MAG_FILTER,
		TextureMinLod = GL_TEXTURE_MIN_LOD,
		TextureMaxLod = GL_TEXTURE_MAX_LOD,
		TextureMaxLevel = GL_TEXTURE_MAX_LEVEL,
		TextureSwizzleR = GL_TEXTURE_SWIZZLE_R,
		TextureSwizzleG = GL_TEXTURE_SWIZZLE_G,
		TextureSwizzleB = GL_TEXTURE_SWIZZLE_B,
		TextureSwizzleA = GL_TEXTURE_SWIZZLE_A,
		TextureWrapS = GL_TEXTURE_WRAP_S,
		TextureWrapT = GL_TEXTURE_WRAP_T,
		TextureWrapR = GL_TEXTURE_WRAP_R
	};

}