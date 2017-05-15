#pragma once

#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLEXT.h>

namespace OpenGL {

	enum class ProgramInterface : unsigned int {
		Uniform = GL_UNIFORM,
		UniformBlock = GL_UNIFORM_BLOCK,
		AtomicCounterBuffer = GL_ATOMIC_COUNTER_BUFFER,
		ProgramInput = GL_PROGRAM_INPUT,
		ProgramOutput = GL_PROGRAM_OUTPUT,
		TransformFeedbackVarying = GL_TRANSFORM_FEEDBACK_VARYING,
		TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
		BufferVariable = GL_BUFFER_VARIABLE,
		ShaderStorageBlock = GL_SHADER_STORAGE_BLOCK,
		VertexSubroutine = GL_VERTEX_SUBROUTINE,
		GeometrySubroutine = GL_GEOMETRY_SUBROUTINE,
		FragmentSubroutine = GL_FRAGMENT_SUBROUTINE,
		TessControlSubroutine = GL_TESS_CONTROL_SUBROUTINE,
		TessEvaluationSubroutine = GL_TESS_EVALUATION_SUBROUTINE,
		ComputeSubroutine = GL_COMPUTE_SUBROUTINE
	};

}