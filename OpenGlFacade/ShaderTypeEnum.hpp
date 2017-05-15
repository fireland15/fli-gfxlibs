#pragma once

#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLEXT.h>

namespace OpenGL {

	enum class ShaderType : GLenum {
		Vertex					= GL_VERTEX_SHADER,
		TesselationControl		= GL_TESS_CONTROL_SHADER,
		TesselationEvaluation	= GL_TESS_EVALUATION_SHADER,
		Geometry				= GL_GEOMETRY_SHADER,
		Fragment				= GL_FRAGMENT_SHADER,
		Compute					= GL_COMPUTE_SHADER
	};

}