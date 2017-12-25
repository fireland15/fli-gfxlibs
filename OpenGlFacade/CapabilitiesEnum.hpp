#pragma once

#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLEXT.h>

namespace OpenGL {

	enum class Capabilities : unsigned int {
		Blend = GL_BLEND,
		ClipDistance0 = GL_CLIP_DISTANCE0,
		ClipDistance1 = GL_CLIP_DISTANCE1,
		ClipDistance2 = GL_CLIP_DISTANCE2,
		ClipDistance3 = GL_CLIP_DISTANCE3,
		ClipDistance4 = GL_CLIP_DISTANCE4,
		ClipDistance5 = GL_CLIP_DISTANCE5,
		ColorLogicOp = GL_COLOR_LOGIC_OP,
		CullFace = GL_CULL_FACE,
		DebugOutput = GL_DEBUG_OUTPUT,
		DebugOutputSynchronous = GL_DEBUG_OUTPUT_SYNCHRONOUS,
		DepthClamp = GL_DEPTH_CLAMP,
		DepthTest = GL_DEPTH_TEST,
		Dither = GL_DITHER,
		FramebufferSRGB = GL_FRAMEBUFFER_SRGB,
		LineSmooth = GL_LINE_SMOOTH,
		Multisample = GL_MULTISAMPLE,
		PolygonOffsetFill = GL_POLYGON_OFFSET_FILL,
		PolygonOffsetLine = GL_POLYGON_OFFSET_LINE,
		PolygonOffsetPoint = GL_POLYGON_OFFSET_POINT,
		PolygonSmooth = GL_POLYGON_SMOOTH,
		PrimitiveRestart = GL_PRIMITIVE_RESTART,
		PrimitiveRestartFixedIndex = GL_PRIMITIVE_RESTART_FIXED_INDEX,
		RasterizerDiscard = GL_RASTERIZER_DISCARD,
		SampleAlphaToCoverage = GL_SAMPLE_ALPHA_TO_COVERAGE,
		SampleAlphaToOne = GL_SAMPLE_ALPHA_TO_ONE,
		SampleCoverage = GL_SAMPLE_COVERAGE,
		SampleMask = GL_SAMPLE_MASK,
		ScissorTest = GL_SCISSOR_TEST,
		StencilTest = GL_STENCIL_TEST,
		TextureCubeMapSeamless = GL_TEXTURE_CUBE_MAP_SEAMLESS,
		ProrgamPointSize = GL_PROGRAM_POINT_SIZE
	};

}