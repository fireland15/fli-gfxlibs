#include <gtest.h>

#include <BufferDataFormatter.hpp>
#include <BufferDataBuilder.hpp>

namespace {

	TEST(BufferDataBuildingIntegrationTest, DifferentInterleaveGroupsHaveCorrectOffset) {
		unsigned char data[4]{ 'a', 'b', 'c', 'd' };

		OpenGL::BufferDataPointer bufferDataPtrs[2] = {
			OpenGL::BufferDataPointer(1, OpenGL::DataType::Byte),
			OpenGL::BufferDataPointer(1, OpenGL::DataType::Byte)
		};

		OpenGL::BufferDataFormatter formatter;
		OpenGL::BufferDataBuilder b;
		b.Data(data, sizeof(unsigned char), 4, bufferDataPtrs[0])
			.And(data, sizeof(unsigned char), 4, bufferDataPtrs[1]);

		auto res = b.BuildData(formatter);
		auto ptrs = b.Layout();

		EXPECT_EQ(ptrs.Count(), 2);
		EXPECT_EQ(ptrs[0].Offset(), 0);
		EXPECT_EQ(ptrs[1].Offset(), 4);
	}

	TEST(BufferDataBuildingIntegrationTest, InterleaveGroupsHaveCorrectOffset) {
		unsigned char data[4]{ 'a', 'b', 'c', 'd' };

		OpenGL::BufferDataPointer bufferDataPtrs[3] = {
			OpenGL::BufferDataPointer(1, OpenGL::DataType::Byte),
			OpenGL::BufferDataPointer(1, OpenGL::DataType::Byte),
			OpenGL::BufferDataPointer(1, OpenGL::DataType::Byte)
		};

		OpenGL::BufferDataFormatter formatter;
		OpenGL::BufferDataBuilder b;
		b.Data(data, sizeof(unsigned char), 4, bufferDataPtrs[0])
			.InterleavedWith(data, sizeof(unsigned char), 4, bufferDataPtrs[1])
			.And(data, sizeof(unsigned char), 4, bufferDataPtrs[2]);

		auto res = b.BuildData(formatter);
		auto ptrs = b.Layout();

		EXPECT_EQ(ptrs.Count(), 3);
		EXPECT_EQ(ptrs[0].Offset(), 0);
		EXPECT_EQ(ptrs[1].Offset(), 1);
		EXPECT_EQ(ptrs[2].Offset(), 8);
	}

	TEST(BufferDataBuildingIntegrationTest, DifferentInterleaveGroupsHaveCorrectStride) {
		unsigned char data[4]{ 'a', 'b', 'c', 'd' };

		OpenGL::BufferDataFormatter formatter;
		OpenGL::BufferDataBuilder b;
		b.Data(data, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(1, OpenGL::DataType::Byte))
			.And(data, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(1, OpenGL::DataType::Byte));

		auto res = b.BuildData(formatter);
		auto ptrs = b.Layout();

		EXPECT_EQ(ptrs.Count(), 2);
		EXPECT_EQ(ptrs[0].Stride(), 0);
		EXPECT_EQ(ptrs[1].Stride(), 0);
	}

	TEST(BufferDataBuildingIntegrationTest, InterleaveGroupsHaveCorrectStride) {
		unsigned char data[4]{ 'a', 'b', 'c', 'd' };

		OpenGL::BufferDataPointer bufferDataPtrs[3] = {
			OpenGL::BufferDataPointer(1, OpenGL::DataType::Byte),
			OpenGL::BufferDataPointer(1, OpenGL::DataType::Byte),
			OpenGL::BufferDataPointer(1, OpenGL::DataType::Byte)
		};

		OpenGL::BufferDataFormatter formatter;
		OpenGL::BufferDataBuilder b;
		b.Data(data, sizeof(unsigned char), 4, bufferDataPtrs[0])
			.InterleavedWith(data, sizeof(unsigned char), 4, bufferDataPtrs[1])
			.And(data, sizeof(unsigned char), 4, bufferDataPtrs[2]);

		auto res = b.BuildData(formatter);
		auto ptrs = b.Layout();

		EXPECT_EQ(ptrs.Count(), 3);
		EXPECT_EQ(ptrs[0].Stride(), 2U);
		EXPECT_EQ(ptrs[1].Stride(), 2U);
		EXPECT_EQ(ptrs[2].Stride(), 0U);
	}

}