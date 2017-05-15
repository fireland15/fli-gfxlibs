#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLEXT.h>

namespace OpenGL {

	enum class TextureParameterValue : int {
		// Used with GL_DEPTH_STENCIL_TEXTURE_MODE
		DepthComponent = GL_DEPTH_COMPONENT,
		StencilComponent = GL_STENCIL_COMPONENTS,

		// Used with GL_TEXTURE_COMPARE_FUNC
		LessThanOrEqual = GL_LEQUAL,
		GreaterThanOrEqual = GL_GEQUAL,
		LessThan = GL_LESS,
		GreaterThan = GL_GREATER,
		Equal = GL_EQUAL,
		NotEqual = GL_NOTEQUAL,
		Always = GL_ALWAYS,
		Never = GL_NEVER,

		// Used with GL_TEXTURE_COMPARE_REF
		CompareRefToTexture = GL_COMPARE_REF_TO_TEXTURE,
		None = GL_NONE,

		// Used with GL_TEXTURE_MIN_FILTER
		Nearest = GL_NEAREST,
		Linear = GL_LINEAR,
		NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
		LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
		NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
		LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR,
		
		// Used with GL_TEXTURE_MAG_FILTER
		//Nearest
		//Linear

		// Used with GL_TEXTURE_SWIZZLE_R
		// Used with GL_TEXTURE_SWIZZLE_G
		// Used with GL_TEXTURE_SWIZZLE_B
		// Used with GL_TEXTURE_SWIZZLE_A
		Red = GL_RED,
		Green = GL_GREEN,
		Blue = GL_BLUE,
		Alpha = GL_ALPHA,
		Zero = GL_ZERO,
		One = GL_ONE,

		// Used with GL_TEXTURE_WRAP_S
		ClampToEdge = GL_CLAMP_TO_EDGE,
		ClampToBorder = GL_CLAMP_TO_BORDER,
		MirroredRepeat = GL_MIRRORED_REPEAT,
		Repeat = GL_REPEAT,
		MirrorClampToEdge = GL_MIRROR_CLAMP_TO_EDGE,

	};

}