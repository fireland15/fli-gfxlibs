#pragma once

#include <glew\glew.h>
#include <GL\GL.h>

#include <glm\glm.hpp>

#include "opengl_error.hpp"

namespace opengl {

	namespace gl {

		enum ShaderType : GLenum {
			Vertex = GL_VERTEX_SHADER,
			TesselationControl = GL_TESS_CONTROL_SHADER,
			TesselationEvaluation = GL_TESS_EVALUATION_SHADER,
			Geometry = GL_GEOMETRY_SHADER,
			Fragment = GL_FRAGMENT_SHADER,
			Compute = GL_COMPUTE_SHADER
		};

		enum Buffers : GLbitfield {
			Color			= GL_COLOR_BUFFER_BIT,
			Depth			= GL_DEPTH_BUFFER_BIT,
			Accumulation	= GL_ACCUM_BUFFER_BIT,
			Stencil			= GL_STENCIL_BUFFER_BIT
		};

		enum BufferTarget : GLenum {
			ArrayBuffer = GL_ARRAY_BUFFER,
			AtomicCounterBuffer = GL_ATOMIC_COUNTER_BUFFER,
			CopyReadBuffer = GL_COPY_READ_BUFFER,
			CopyWriteBuffer = GL_COPY_WRITE_BUFFER,
			DispatchIndirectBuffer = GL_DISPATCH_INDIRECT_BUFFER,
			DrawIndirectBuffer = GL_DRAW_INDIRECT_BUFFER,
			ElementArrayBuffer = GL_ELEMENT_ARRAY_BUFFER,
			PixelPackBuffer = GL_PIXEL_PACK_BUFFER,
			PixelUnpackBuffer = GL_PIXEL_UNPACK_BUFFER,
			QueryBuffer = GL_QUERY_BUFFER,
			ShaderStorageBuffer = GL_SHADER_STORAGE_BUFFER,
			TextureBuffer = GL_TEXTURE_BUFFER,
			TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
			UniformBuffer = GL_UNIFORM_BUFFER
		};

		enum BufferUsage : GLenum {
			StreamDraw = GL_STREAM_DRAW,
			StreamRead = GL_STREAM_READ,
			StreamCopy = GL_STREAM_COPY,
			StaticDraw = GL_STATIC_DRAW,
			StaticRead = GL_STATIC_READ,
			StaticCopy = GL_STATIC_COPY,
			DynamicDraw = GL_DYNAMIC_DRAW,
			DynamicRead = GL_DYNAMIC_READ,
			DynamicCopy = GL_DYNAMIC_COPY
		};

		enum BufferDataType : GLenum {
			Byte = GL_BYTE,
			UnsignedByte = GL_UNSIGNED_BYTE,
			Short = GL_SHORT,
			UnsignedShort = GL_UNSIGNED_SHORT,
			Int = GL_INT,
			UnsignedInt = GL_UNSIGNED_INT,
			HalfFloat = GL_HALF_FLOAT,
			Float = GL_FLOAT,
			Double = GL_DOUBLE,
			Fixed = GL_FIXED
		};

		enum Normalize : GLboolean {
			Yes = GL_TRUE,
			No = GL_FALSE
		};

		enum BufferAttribSize : GLint {
			One = 1,
			Two = 2,
			Three = 3,
			Four = 4
		};
		
		OpenGlError GetErrors();

		void ClearColor(glm::vec4 color);

		void Clear(GLbitfield buffers);
		
	}

}