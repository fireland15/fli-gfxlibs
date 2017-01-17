#pragma once

#include <gl\glew.h>
#include <gl\wglew.h>
#include <gl\GL.h>

namespace opengl {

	class Buffer {
	public:

		enum Targets : GLenum {
			ArrayBuffer				= GL_ARRAY_BUFFER,
			AtomicCounterBuffer		= GL_ATOMIC_COUNTER_BUFFER,
			CopyReadBuffer			= GL_COPY_READ_BUFFER,
			CopyWriteBuffer			= GL_COPY_WRITE_BUFFER,
			DispatchIndirectBuffer	= GL_DISPATCH_INDIRECT_BUFFER,
			DrawIndirectBuffer		= GL_DRAW_INDIRECT_BUFFER,
			ElementArrayBuffer		= GL_ELEMENT_ARRAY_BUFFER,
			PixelPackBuffer			= GL_PIXEL_PACK_BUFFER,
			PixelUnpackBuffer		= GL_PIXEL_UNPACK_BUFFER,
			QueryBuffer				= GL_QUERY_BUFFER,
			ShaderStorageBuffer		= GL_SHADER_STORAGE_BUFFER,
			TextureBuffer			= GL_TEXTURE_BUFFER,
			TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
			UniformBuffer			= GL_UNIFORM_BUFFER
		};

		enum Usage : GLenum {
			StreamDraw	= GL_STREAM_DRAW,
			StreamRead	= GL_STREAM_READ,
			StreamCopy	= GL_STREAM_COPY,
			StaticDraw	= GL_STATIC_DRAW,
			StaticRead	= GL_STATIC_READ,
			StaticCopy	= GL_STATIC_COPY,
			DynamicDraw = GL_DYNAMIC_DRAW,
			DynamicRead = GL_DYNAMIC_READ,
			DynamicCopy = GL_DYNAMIC_COPY
		};

	private:

		Buffer(GLuint obj, Targets target);

		GLuint Obj();

		void Obj(GLuint obj);
		
	public:

		Buffer();

		void Bind();

		void Unbind();

		void Data(Targets target, GLsizeiptr size, void* data, Usage usage);

		bool IsBound();

	private:
		GLuint m_obj;

		Targets m_target;

		bool m_isBound;

		friend class GL;

	};

}