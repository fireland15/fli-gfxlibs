#include "BufferDataBuilder.hpp"
#include "BufferDataDescriptor.hpp"
#include "BufferDataFormatter.hpp"

unsigned int CalculateGroupOffset(std::map<int, std::list<std::pair<OpenGL::BufferDataDescriptor, std::reference_wrapper<OpenGL::BufferDataPointer>>>>& groups, int group);

OpenGL::BufferDataBuilder::BufferDataBuilder() : _interleaveCount(0) {

}

OpenGL::IBufferDataBuilder & OpenGL::BufferDataBuilder::Data(const void * data, unsigned int size, unsigned int count, BufferDataPointer& pointer) {
	_interleaveCount++;
	BufferDataDescriptor desc(data, size, count);
	InsertData(_interleaveCount, desc, pointer);

	return *this;
}

OpenGL::IBufferDataBuilder & OpenGL::BufferDataBuilder::InterleavedWith(const void * data, unsigned int size, unsigned int count, BufferDataPointer& pointer) {
	BufferDataDescriptor desc(data, size, count);
	InsertData(_interleaveCount, desc, pointer);

	return *this;
}

OpenGL::IBufferDataBuilder & OpenGL::BufferDataBuilder::And(const void * data, unsigned int size, unsigned int count, BufferDataPointer& pointer) {
	_interleaveCount++;
	BufferDataDescriptor desc(data, size, count);
	InsertData(_interleaveCount, desc, pointer);

	return *this;
}

 std::vector<unsigned char> OpenGL::BufferDataBuilder::BuildData(BufferDataFormatter& formatter) {
	VerifyInterleaveGroupCounts();
	auto bytes = CalculateSpaceRequirement();
	std::vector<byte> data(bytes);
	for (auto & pair : _data) {
		unsigned int offset = CalculateGroupOffset(_data, pair.first);
		formatter.InterleaveSubData(data, offset, pair.second);
	}
	return data;
}

OpenGL::BufferDataLayout OpenGL::BufferDataBuilder::Layout() {
	OpenGL::BufferDataLayout layouts;

	for (auto & interleaveGroup : _data) {
		for (auto & desc : interleaveGroup.second) {
			layouts.Add(desc.second);
		}
	}

	return layouts;
}

void OpenGL::BufferDataBuilder::InsertData(int group, const BufferDataDescriptor & desc, BufferDataPointer & ptr) {
	if (_data.count(group))
		_data.insert(std::make_pair(group, std::list<std::pair<BufferDataDescriptor, std::reference_wrapper<BufferDataPointer>>>()));
	_data[group].emplace_back(desc, ptr);
}

inline void OpenGL::BufferDataBuilder::VerifyInterleaveGroupCounts() {
	for (auto & group : _data) {
		unsigned int count = group.second.front().first.Count;
		for (auto & item : group.second) {
			if (item.first.Count != count)
				throw std::exception("interleaved data must have the same number of elements");
		}
	}
}

inline unsigned int OpenGL::BufferDataBuilder::CalculateSpaceRequirement() {
	unsigned int bytes = 0;
	for (auto & group : _data) {
		for (auto & item : group.second)
			bytes += item.first.Size * item.first.Count;
	}
	return bytes;
}

unsigned int CalculateGroupOffset(std::map<int, std::list<std::pair<OpenGL::BufferDataDescriptor, std::reference_wrapper<OpenGL::BufferDataPointer>>>>& groups, int group) {
	unsigned int offset = 0;

	auto it = groups.begin();
	while ((*it).first < group) {
		for (auto & d : (*it).second) {
			offset += d.first.Count * d.first.Size;
		}

		it++;
	}

	return offset;;
}
