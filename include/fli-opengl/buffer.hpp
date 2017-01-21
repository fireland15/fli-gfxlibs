#pragma once

#include <vector>

#include <glew\glew.h>
#include <gl\GL.h>

#include "attribute_variable.hpp"

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

		enum Usages : GLenum {
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

		enum DataType : GLenum {
			Byte			= GL_BYTE,
			UnsignedByte	= GL_UNSIGNED_BYTE,
			Short			= GL_SHORT,
			UnsignedShort	= GL_UNSIGNED_SHORT,
			Int				= GL_INT,
			UnsignedInt		= GL_UNSIGNED_INT,
			HalfFloat		= GL_HALF_FLOAT,
			Float			= GL_FLOAT,
			Double			= GL_DOUBLE,
			Fixed			= GL_FIXED
		};

		enum Normalize : GLboolean {
			Yes	= GL_TRUE,
			No	= GL_FALSE
		};

		enum AttribSize : GLint {
			One		= 1,
			Two		= 2,
			Three	= 3,
			Four	= 4
		};

		struct DataDescriptor {
		public:
			AttribSize AttributeSize;
			DataType Type;
			Normalize Normalize;
			GLsizei Stride;
			GLvoid* Offset;
		};

		struct Descriptor {
		public:
			Targets Target;
			void* pData;
			GLsizeiptr Size;
			Usages Usage;
			std::vector<DataDescriptor> DataDescriptions;
		};

	private:

		Buffer(GLuint obj, Targets target);

		GLuint Obj();

		void Obj(GLuint obj);
		
	public:

		Buffer();

		void Bind();

		void Unbind();

		void SetData(const Descriptor& desc);

		bool IsBound();

		Targets Target();

		Usages Usage();

		const Descriptor& Description();

	private:
		GLuint m_obj;

		Targets m_target;

		bool m_isBound;

		Descriptor m_description;

		friend class GL;

	};

}