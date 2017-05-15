#pragma once

#include <map>
#include <list>

#include <vector>
#include <map>
#include <list>

#include "IBufferDataBuilder.hpp"
#include "BufferDataDescriptor.hpp"
#include "BufferDataFormatter.hpp"
#include "BufferDataPointer.hpp"

namespace OpenGL {

	class BufferDataBuilder : public IBufferDataBuilder {
	public:
		BufferDataBuilder();
		virtual ~BufferDataBuilder() { }
		virtual IBufferDataBuilder & Data(const void * data, unsigned int size, unsigned int count, BufferDataPointer& pointer) override;
		virtual IBufferDataBuilder & InterleavedWith(const void * data, unsigned int size, unsigned int count, BufferDataPointer& pointer) override;
		virtual IBufferDataBuilder & And(const void * data, unsigned int size, unsigned int count, BufferDataPointer& pointer) override;
		virtual std::vector<byte> BuildData(BufferDataFormatter& formatter) override;
		virtual BufferDataLayout Layout() override;

	private:
		std::map<int, std::list<std::pair<BufferDataDescriptor, std::reference_wrapper<BufferDataPointer>>>> _data;
		int _interleaveCount;

		void InsertData(int group, const BufferDataDescriptor& desc, BufferDataPointer& ptr);
		void VerifyInterleaveGroupCounts();
		unsigned int CalculateSpaceRequirement();
	};

}