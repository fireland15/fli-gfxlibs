#include "dynamic_buffer.hpp"

namespace opengl {

	/*************************************************************
	* Constructors
	**************************************************************/

	DynamicBuffer::DynamicBuffer(BufferDescriptor desc) 
		: Buffer(desc) {

	}

	DynamicBuffer::DynamicBuffer(DynamicBuffer&& other) 
		: Buffer(std::move(other)) {

	}

	DynamicBuffer& DynamicBuffer::operator=(DynamicBuffer&& other) {

	}

	/*************************************************************
	* Destructor
	**************************************************************/

	DynamicBuffer::~DynamicBuffer() {

	}

	/*************************************************************
	* Dynamic Buffer Update Policies
	**************************************************************/

	void DynamicBuffer::SimpleUpdatePolicy::Update(void* pData, unsigned int size, BufferDescriptor desc) {
		if (pData == nullptr) {
			throw std::exception("nullptr buffer data");
		}

		if (size == 0) {
			throw std::exception("no buffer data supplied");
		}

		glBufferData(desc.Target, size, pData, desc.Usage);
	}

	void DynamicBuffer::OrphanUpdatePolicy::Update(void* pData, unsigned int size, BufferDescriptor desc) {
		if (pData == nullptr) {
			throw std::exception("nullptr buffer data");
		}

		if (size == 0) {
			throw std::exception("no buffer data supplied");
		}

		glBufferData(desc.Target, size, nullptr, desc.Usage);
		glBufferData(desc.Target, size, pData, desc.Usage);
	}

	void DynamicBuffer::MapUnsynchronizedUpdatePolicy::Update(void* pData, unsigned int size, BufferDescriptor desc) {
		throw std::exception("Not implemented");
	}

}