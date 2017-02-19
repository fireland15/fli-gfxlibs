#pragma once

#include "buffer.hpp"

namespace opengl {

	class DynamicBuffer : public Buffer {
	public:

		class SimpleUpdatePolicy;

		class OrphanUpdatePolicy;

		class MapUnsynchronizedUpdatePolicy;

		/*************************************************************
		* Constructors
		**************************************************************/

		DynamicBuffer(BufferDescriptor desc);

		DynamicBuffer(const DynamicBuffer& other) = delete;

		DynamicBuffer& operator=(const DynamicBuffer& other) = delete;

		DynamicBuffer(DynamicBuffer&& other);

		DynamicBuffer& operator=(DynamicBuffer&& other);

		/*************************************************************
		* Destructor
		**************************************************************/

		~DynamicBuffer();

		/*************************************************************
		* OpenGL Buffer Functions
		**************************************************************/

		/// <summary>
		/// Updates the data stored in the buffer on the GPU. The buffer target and usage remain unchanged. Data format must match that used in the original call to <code>SetData()</code>. Buffer must be bound before calling.
		/// </summary>
		/// <param name="pData">Pointer to the beginning of the array of data.</param>
		/// <param name="size">The size of the data to be uploaded in bytes.</param>
		template <typename UpdatePolicy>
		void UpdateData(void* pData, unsigned int size) {
			UpdatePolicy::Update(pData, size, m_description);
		}

	private:

	};

	class DynamicBuffer::SimpleUpdatePolicy {
	public:
		static void Update(void* pData, unsigned int size, BufferDescriptor desc);
	};

	class DynamicBuffer::OrphanUpdatePolicy {
	public:
		static void Update(void* pData, unsigned int size, BufferDescriptor desc);
	};

	class DynamicBuffer::MapUnsynchronizedUpdatePolicy {
	public:
		static void Update(void* pData, unsigned int size, BufferDescriptor desc);
	};

}