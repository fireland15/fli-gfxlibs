#include <gtest.h>

#include <BufferDataBuilder.hpp>

#include "MockBufferDataFormatter.hpp"
#include <BufferDataPointer.hpp>
#include <BufferDataLayout.hpp>

using ::testing::_;

namespace {

	TEST(BufferDataBuilderTest, BuildDataCallsDataFormatterWithOneDataArray) {
		MockBufferDataFormatter formatter;
		EXPECT_CALL(formatter, InterleaveSubData(_, 0, _)).Times(1);

		unsigned char a[4]{ 'a', 'b', 'c', 'd' };

		OpenGL::BufferDataBuilder b;
		OpenGL::BufferDataPointer bdp(0, OpenGL::DataType::Float);

		b.Data(a, sizeof(unsigned char), 4, bdp);
		auto res = b.BuildData(formatter);
	}

	TEST(BufferDataBuilderTest, BuildDataReturnsCorrectSizeVectorForDataArray) {
		MockBufferDataFormatter formatter;
		EXPECT_CALL(formatter, InterleaveSubData(_, _, _)).Times(1);

		unsigned char a[4]{ 'a', 'b', 'c', 'd' };

		OpenGL::BufferDataBuilder b;
		auto res = b.Data(a, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(0, OpenGL::DataType::Float))
			.BuildData(formatter);

		EXPECT_EQ(res.size(), 4);
	}

	TEST(BufferDataBuilderTest, BuildDataReturnsCorrectSizeVectorForTwoDataArrays) {
		MockBufferDataFormatter formatter;
		EXPECT_CALL(formatter, InterleaveSubData(_, _, _)).Times(2);

		unsigned char a[4]{ 'a', 'b', 'c', 'd' };

		OpenGL::BufferDataBuilder b;
		auto res = b.Data(a, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(0, OpenGL::DataType::Float))
			.And(a, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(0, OpenGL::DataType::Float))
			.BuildData(formatter);

		EXPECT_EQ(res.size(), 8);
	}

	TEST(BufferDataBuilderTest, AndAddsCallToFormatter) {
		MockBufferDataFormatter formatter;
		EXPECT_CALL(formatter, InterleaveSubData(_, _, _)).Times(2);

		unsigned char a[4]{ 'a', 'b', 'c', 'd' };

		OpenGL::BufferDataBuilder b;
		auto res = b.Data(a, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(0, OpenGL::DataType::Float))
			.And(a, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(0, OpenGL::DataType::Float))
			.BuildData(formatter);
	}

	TEST(BufferDataBuilderTest, AndIncreasesSizeOfVector) {
		MockBufferDataFormatter formatter;
		EXPECT_CALL(formatter, InterleaveSubData(_, _, _)).Times(2);

		unsigned char a[4]{ 'a', 'b', 'c', 'd' };

		OpenGL::BufferDataBuilder b;
		auto res = b.Data(a, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(0, OpenGL::DataType::Float))
			.And(a, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(0, OpenGL::DataType::Float))
			.BuildData(formatter);

		EXPECT_EQ(res.size(), 8);
	}

	TEST(BufferDataBuilderTest, AndIncreasesOffsetToSecondArray) {
		MockBufferDataFormatter formatter;
		EXPECT_CALL(formatter, InterleaveSubData(_, 0, _)).Times(1);
		EXPECT_CALL(formatter, InterleaveSubData(_, 4, _)).Times(1);

		unsigned char a[4]{ 'a', 'b', 'c', 'd' };

		OpenGL::BufferDataBuilder b;
		auto res = b.Data(a, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(0, OpenGL::DataType::Float))
			.And(a, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(0, OpenGL::DataType::Float))
			.BuildData(formatter);
	}

	TEST(BufferDataBuilderTest, InterleavedWithDoesNotAddCallToFormatter) {
		MockBufferDataFormatter formatter;
		EXPECT_CALL(formatter, InterleaveSubData(_, _, _)).Times(2);

		unsigned char a[4]{ 'a', 'b', 'c', 'd' };

		OpenGL::BufferDataBuilder b;
		auto res = b.Data(a, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(0, OpenGL::DataType::Float))
			.Data(a, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(0, OpenGL::DataType::Float))
			.InterleavedWith(a, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(0, OpenGL::DataType::Float))
			.BuildData(formatter);
	}

	TEST(BufferDataBuilderTest, InterleavedWithIncreasesOffsetSentToDataFormatter) {
		MockBufferDataFormatter formatter;
		EXPECT_CALL(formatter, InterleaveSubData(_, 0, _)).Times(1);
		EXPECT_CALL(formatter, InterleaveSubData(_, 8, _)).Times(1);

		unsigned char a[4]{ 'a', 'b', 'c', 'd' };

		OpenGL::BufferDataBuilder b;
		auto res = b.Data(a, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(0, OpenGL::DataType::Float))
			.InterleavedWith(a, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(0, OpenGL::DataType::Float))
			.Data(a, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(0, OpenGL::DataType::Float))
			.BuildData(formatter);
	}

	TEST(BufferDataBuilderTest, InterleavedWithAddsDataToVector) {
		MockBufferDataFormatter formatter;
		EXPECT_CALL(formatter, InterleaveSubData(_, _, _)).Times(1);

		unsigned char a[4]{ 'a', 'b', 'c', 'd' };

		OpenGL::BufferDataBuilder b;
		auto res = b.Data(a, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(0, OpenGL::DataType::Float))
			.InterleavedWith(a, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(0, OpenGL::DataType::Float))
			.BuildData(formatter);

		EXPECT_EQ(res.size(), 8);
	}

	TEST(BufferDataBuilderTest, DataPointersReturnsOneDataPointerWithZeroStrideAndOffset) {
		MockBufferDataFormatter formatter;
		EXPECT_CALL(formatter, InterleaveSubData(_, _, _));

		unsigned char a[4]{ 'a', 'b', 'c', 'd' };

		OpenGL::BufferDataBuilder b;
		auto res = b.Data(a, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(1, OpenGL::DataType::Byte))
			.BuildData(formatter);
		auto ptrs = b.Layout();

		EXPECT_EQ(ptrs.Count(), 1);
		EXPECT_EQ(ptrs[0].Offset(), 0);
		EXPECT_EQ(ptrs[0].Stride(), 0);
	}

	TEST(BufferDataBuilderTest, DataPointersReturnsTwoDataPointers) {
		MockBufferDataFormatter formatter;
		EXPECT_CALL(formatter, InterleaveSubData(_, _, _)).Times(2);

		unsigned char a[4]{ 'a', 'b', 'c', 'd' };

		OpenGL::BufferDataBuilder b;
		auto res = b.Data(a, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(1, OpenGL::DataType::Byte))
			.And(a, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(1, OpenGL::DataType::Byte))
			.BuildData(formatter);
		auto ptrs = b.Layout();

		EXPECT_EQ(ptrs.Count(), 2);
	}

	TEST(BufferDataBuilderTest, DataPointersReturnsThreeDataPointers) {
		MockBufferDataFormatter formatter;
		EXPECT_CALL(formatter, InterleaveSubData(_, _, _)).Times(2);

		unsigned char a[4]{ 'a', 'b', 'c', 'd' };

		OpenGL::BufferDataBuilder b;
		auto res = b.Data(a, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(1, OpenGL::DataType::Byte))
			.And(a, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(1, OpenGL::DataType::Byte))
			.InterleavedWith(a, sizeof(unsigned char), 4, OpenGL::BufferDataPointer(1, OpenGL::DataType::Byte))
			.BuildData(formatter);
		auto ptrs = b.Layout();

		EXPECT_EQ(ptrs.Count(), 3);
	}

	TEST(BufferDataBuilderTest, LayoutHasReferencesToDataPointers) {
		MockBufferDataFormatter formatter;
		EXPECT_CALL(formatter, InterleaveSubData(_, _, _)).Times(2);

		unsigned char a[4]{ 'a', 'b', 'c', 'd' };


		OpenGL::BufferDataPointer p1(1, OpenGL::DataType::Byte);
		OpenGL::BufferDataPointer p2(1, OpenGL::DataType::Byte);
		OpenGL::BufferDataPointer p3(1, OpenGL::DataType::Byte);

		OpenGL::BufferDataBuilder b;
		auto res = b.Data(a, sizeof(unsigned char), 4, p1)
			.And(a, sizeof(unsigned char), 4, p2)
			.InterleavedWith(a, sizeof(unsigned char), 4, p3)
			.BuildData(formatter);
		auto layout = b.Layout();

		p1.Offset(77);
		EXPECT_EQ(p1.Offset(), 77);
		EXPECT_EQ(layout[0].Offset(), p1.Offset());
	}

}