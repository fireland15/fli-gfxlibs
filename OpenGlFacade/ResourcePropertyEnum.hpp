#pragma once

#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLEXT.h>

namespace OpenGL {

	enum class ResourceProperty : unsigned int {
		ActiveResources = GL_ACTIVE_RESOURCES,
		NameLength = GL_NAME_LENGTH,
		Type = GL_TYPE,
		ArraySize = GL_ARRAY_SIZE,
		Offset = GL_OFFSET,
		BlockIndex = GL_BLOCK_INDEX,
		ArrayStride = GL_ARRAY_STRIDE,
		MatrixStride = GL_MATRIX_STRIDE,
		IsRowMajor = GL_IS_ROW_MAJOR,
		AtomicCounterBufferIndex = GL_ATOMIC_COUNTER_BUFFER_INDEX,
		BufferBinding = GL_BUFFER_BINDING,
		BufferDataSize = GL_BUFFER_DATA_SIZE,
		NumActiveVariables = GL_NUM_ACTIVE_VARIABLES,
		ActiveVariables = GL_ACTIVE_VARIABLES,
		ReferencedByVertexShader = GL_REFERENCED_BY_VERTEX_SHADER,
		ReferencedByTessControlShader = GL_REFERENCED_BY_TESS_CONTROL_SHADER,
		ReferencedByTessEvaluationShader = GL_REFERENCED_BY_TESS_EVALUATION_SHADER,
		ReferencedByGeometryShader = GL_REFERENCED_BY_GEOMETRY_SHADER,
		ReferencedByFragmentShader = GL_REFERENCED_BY_FRAGMENT_SHADER,
		ReferencedByComputeShader = GL_REFERENCED_BY_COMPUTE_SHADER,
		NumCompatibleSubroutines = GL_NUM_COMPATIBLE_SUBROUTINES,
		CompatibleSubroutines = GL_COMPATIBLE_SUBROUTINES,
		TopLevelArraySize = GL_TOP_LEVEL_ARRAY_SIZE,
		TopLevelArrayStride = GL_TOP_LEVEL_ARRAY_STRIDE,
		Location = GL_LOCATION,
		LocationIndex = GL_LOCATION_INDEX,
		IsPerPatch = GL_IS_PER_PATCH,
		LocationComponent = GL_LOCATION_COMPONENT,
		TransformFeedbackBufferIndex = GL_TRANSFORM_FEEDBACK_BUFFER_INDEX,
		TransformFeedbackBufferStride = GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE
	};

}
