#pragma once

#include <memory>
#include <vector>

#include "opengl.hpp"
#include "attribute_variable.hpp"

namespace opengl {

	class Buffer {
	public:

		struct DataDescriptor {
			/// <summary>
			/// The number of elements in the attribute. Can be 1, 2, 3 or 4.
			/// </summary>
			gl::BufferAttribSize AttributeSize = gl::BufferAttribSize::Four;

			/// <summary>
			/// Tells OpenGL the type of the data in the buffer.
			/// </summary>
			gl::BufferDataType Type = gl::BufferDataType::Float;

			/// <summary>
			/// Tells OpenGL whether normalize the data in the buffer.
			/// </summary>
			gl::Normalize Normalize = gl::Normalize::No;

			/// <summary>
			/// The stride, or width, of the vertex attributes.
			/// </summary>
			GLsizei Stride = 0;

			/// <summary>
			/// The offset of a vertex attribute from the beginning of the data.
			/// </summary>
			GLvoid* Offset = 0;
		};

		/// <summary>
		/// A struct for storing information about a buffer and its data.
		/// </summary>
		struct Descriptor {
			/// <summary>
			/// The binding target for the buffer.
			/// </summary>
			gl::BufferTarget Target;

			/// <summary>
			/// A pointer to the beginning of the data to be stored in the buffer.
			/// </summary>
			void* pData = nullptr;
			
			/// <summary>
			/// The size of pData in bytes.
			/// </summary>
			GLsizeiptr Size = 0;

			/// <summary>
			/// The buffers usage.
			/// </summary>
			gl::BufferUsage Usage;

			/// <summary>
			/// An array of DataDescriptors for each type of data in the buffer.
			/// </summary>
			std::vector<DataDescriptor> DataDescriptions;
		};

		/*************************************************************
		* Constructors
		**************************************************************/

		/// <summary>
		/// Creates a new OpenGL buffer object.
		/// </summary>
		Buffer(const Descriptor& desc);
		
		/// <summary>
		/// Copy Constructor is deleted.
		/// </summary>
		/// <param name="other"></param>
		Buffer(const Buffer& other) = delete;

		/// <summary>
		/// Copy Assignment Constructor is deleted.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Buffer& operator=(const Buffer& other) = delete;

		/// <summary>
		/// Move Constructor.
		/// </summary>
		/// <param name="other">The buffer object to move into the new instance.</param>
		Buffer(Buffer&& other);

		/// <summary>
		/// Move Assignment Constructor.
		/// </summary>
		/// <param name="other">The buffer object to move into the lhs of the operator.</param>
		/// <returns>Reference to a Buffer object.</returns>
		Buffer& operator=(Buffer&& other);

		/*************************************************************
		* Destructor
		**************************************************************/

		/// <summary>
		/// Destructor. Releases the OpenGL buffer object.
		/// </summary>
		~Buffer();

		/*************************************************************
		* OpenGL Buffer Functions
		**************************************************************/

		/// <summary>
		/// Binds the buffer to the current OpenGL context. Usually must be called before performing any operations on the buffer.
		/// </summary>
		void Bind();

		/// <summary>
		/// Unbinds the buffer from the current OpenGL context. Sets current buffer to 0.
		/// </summary>
		void Unbind();

		/// <summary>
		/// Sets the data stored in the buffer as well as any target and usage flags. Buffer must be bound before calling.
		/// </summary>
		/// <param name="desc">A Descriptor object describing the buffer usage, binding targets, data, and data structure.</param>
		void SetData(const Descriptor& desc);

		/// <summary>
		/// Updates the data stored in the buffer on the GPU. The buffer target and usage remain unchanged. Data format must match that used in the original call to <code>SetData()</code>. Buffer must be bound before calling.
		/// </summary>
		/// <param name="pData">Pointer to the beginning of the array of data.</param>
		/// <param name="size">The size of the data to be uploaded in bytes.</param>
		void UpdateData(void* pData, unsigned int size);

		/*************************************************************
		* Getter Methods
		**************************************************************/

		/// <summary>
		/// Checks if the buffer is currently bound
		/// </summary>
		/// <returns>True is the buffer is bound. False if the buffer is not bound.</returns>
		bool IsBound();

		/// <summary>
		/// Returns the binding target of the buffer.
		/// </summary>
		/// <returns>The binding target.</returns>
		gl::BufferTarget Target();

		/// <summary>
		/// Returns the usage of the buffer.
		/// </summary>
		/// <returns>The buffer usage.</returns>
		gl::BufferUsage Usage();

		/// <summary>
		/// Returns a const reference to the Descriptor object of the buffer.
		/// </summary>
		/// <returns>Const Reference to the buffers descriptor.</returns>
		const Descriptor& Description();

		/// <summary>
		/// Checks if the current internal OpenGL Buffer object is valid for use.
		/// </summary>
		/// <returns>True if the internal Buffer is usable; false otherwise.</returns>
		bool IsValid();

	private:
		GLuint m_obj;

		bool m_isBound;

		Descriptor m_description;

	};

	typedef std::unique_ptr<Buffer> up_Buffer;
}