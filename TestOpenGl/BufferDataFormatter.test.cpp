#include <gtest.h>
#include <gmock.h>

#include <vector>
#include <list>

#include <BufferDataFormatter.hpp>
#include <BufferDataDescriptor.hpp>

namespace {

	TEST(BufferDataFormatterTest, FormatsSingleArrayFromBeginning) {
		char c[4]{ 'A', 'B', 'C', 'D' };

		std::list<std::pair<OpenGL::BufferDataDescriptor, std::reference_wrapper<OpenGL::BufferDataPointer>>> descs;

		OpenGL::BufferDataDescriptor bdd1((unsigned char*)c, sizeof(char), 4);
		OpenGL::BufferDataPointer bdp1(0, OpenGL::DataType::Float);

		descs.push_back(std::make_pair(bdd1, std::ref(bdp1)));

		std::vector<unsigned char> out(4 * sizeof(char));

		OpenGL::BufferDataFormatter f;
		f.InterleaveSubData(out, 0, descs);

		EXPECT_EQ((char)out[0], c[0]);
		EXPECT_EQ((char)out[1], c[1]);
		EXPECT_EQ((char)out[2], c[2]);
		EXPECT_EQ((char)out[3], c[3]);
	}

	TEST(BufferDataFormatterTest, FormatsTwoArraysFromBeginning) {
		char c[4]{ 'A', 'B', 'C', 'D' };
		char d[4]{ 'a', 'b', 'c', 'd' };

		std::list<std::pair<OpenGL::BufferDataDescriptor, std::reference_wrapper<OpenGL::BufferDataPointer>>> descs;

		OpenGL::BufferDataDescriptor bdd1((unsigned char*)c, sizeof(char), 4);
		OpenGL::BufferDataPointer bdp1(0, OpenGL::DataType::Float);

		OpenGL::BufferDataDescriptor bdd2((unsigned char*)d, sizeof(char), 4);
		OpenGL::BufferDataPointer bdp2(0, OpenGL::DataType::Float);

		descs.push_back(std::make_pair(bdd1, std::ref(bdp1)));
		descs.push_back(std::make_pair(bdd2, std::ref(bdp2)));
		std::vector<unsigned char> out(8 * sizeof(char));

		OpenGL::BufferDataFormatter f;
		f.InterleaveSubData(out, 0, descs);

		EXPECT_EQ((char)out[0], c[0]);
		EXPECT_EQ((char)out[1], d[0]);

		EXPECT_EQ((char)out[2], c[1]);
		EXPECT_EQ((char)out[3], d[1]);

		EXPECT_EQ((char)out[4], c[2]);
		EXPECT_EQ((char)out[5], d[2]);

		EXPECT_EQ((char)out[6], c[3]);
		EXPECT_EQ((char)out[7], d[3]);
	}

	TEST(BufferDataFormatterTest, FormatsArrayOfFloats) {
		float c[4]{ 1.5f, 2.5f, 3.5f, 4.5f };
		unsigned char* d;
		d = new unsigned char[16];
		memcpy(d, c, 16);

		std::list<std::pair<OpenGL::BufferDataDescriptor, std::reference_wrapper<OpenGL::BufferDataPointer>>> descs;

		OpenGL::BufferDataDescriptor bdd1(c, sizeof(float), 4);
		OpenGL::BufferDataPointer bdp1(0, OpenGL::DataType::Float);

		descs.push_back(std::make_pair(bdd1, std::ref(bdp1)));

		std::vector<unsigned char> out(4 * sizeof(float));

		OpenGL::BufferDataFormatter f;
		f.InterleaveSubData(out, 0, descs);
		delete [] d;

		float r[4];
		memcpy(r, &out[0], 16);

		EXPECT_EQ(r[0], c[0]);
		EXPECT_EQ(r[1], c[1]);
		EXPECT_EQ(r[2], c[2]);
		EXPECT_EQ(r[3], c[3]);
	}

	TEST(BufferDataFormatterTest, FormatsTwoArraysOfFloats) {
		float c[4]{ 1.5f, 2.5f, 3.5f, 4.5f };
		float e[4]{ 1.6f, 2.6f, 3.6f, 4.6f };
		unsigned char* d;
		unsigned char* f;
		d = new unsigned char[16];
		f = new unsigned char[16];
		memcpy(d, c, 16);
		memcpy(f, e, 16);

		std::list<std::pair<OpenGL::BufferDataDescriptor, std::reference_wrapper<OpenGL::BufferDataPointer>>> descs;

		OpenGL::BufferDataDescriptor bdd1(d, sizeof(float), 4);
		OpenGL::BufferDataPointer bdp1(0, OpenGL::DataType::Float);

		OpenGL::BufferDataDescriptor bdd2(f, sizeof(float), 4);
		OpenGL::BufferDataPointer bdp2(0, OpenGL::DataType::Float);

		descs.push_back(std::make_pair(bdd1, std::ref(bdp1)));
		descs.push_back(std::make_pair(bdd2, std::ref(bdp2)));

		std::vector<unsigned char> out(8 * sizeof(float));

		OpenGL::BufferDataFormatter form;
		form.InterleaveSubData(out, 0, descs);
		delete[] d;
		delete[] f;

		float r[8];
		memcpy(r, &out[0], 32);

		EXPECT_EQ(r[0], c[0]);
		EXPECT_EQ(r[2], c[1]);
		EXPECT_EQ(r[4], c[2]);
		EXPECT_EQ(r[6], c[3]);
		EXPECT_EQ(r[1], e[0]);
		EXPECT_EQ(r[3], e[1]);
		EXPECT_EQ(r[5], e[2]);
		EXPECT_EQ(r[7], e[3]);
	}

	TEST(BufferDataFormatterTest, FormatsThreeThings) {
		int a[2]{ 1, 212 };
		int b[2]{ 4, 43 };
		int c[2]{ 8, 12 };

		unsigned char* d, *e, *f;
		d = new unsigned char[8];
		e = new unsigned char[8];
		f = new unsigned char[8];

		memcpy(d, a, 8);
		memcpy(e, b, 8);
		memcpy(f, c, 8);

		std::list<std::pair<OpenGL::BufferDataDescriptor, std::reference_wrapper<OpenGL::BufferDataPointer>>> descs;
		
		OpenGL::BufferDataDescriptor bdd1(d, sizeof(int), 2);
		OpenGL::BufferDataPointer bdp1(0, OpenGL::DataType::Float);

		OpenGL::BufferDataDescriptor bdd2(e, sizeof(int), 2);
		OpenGL::BufferDataPointer bdp2(0, OpenGL::DataType::Float);

		OpenGL::BufferDataDescriptor bdd3(f, sizeof(int), 2);
		OpenGL::BufferDataPointer bdp3(0, OpenGL::DataType::Float);

		descs.push_back(std::make_pair(bdd1, std::ref(bdp1)));
		descs.push_back(std::make_pair(bdd2, std::ref(bdp2)));
		descs.push_back(std::make_pair(bdd3, std::ref(bdp3)));
		std::vector<unsigned char> out(6 * sizeof(int));

		OpenGL::BufferDataFormatter form;
		form.InterleaveSubData(out, 0, descs);
		delete[] d;
		delete[] e;
		delete[] f;

		int r[6];
		memcpy(r, &out[0], 6 * sizeof(int));

		EXPECT_EQ(r[0], a[0]);
		EXPECT_EQ(r[1], b[0]);
		EXPECT_EQ(r[2], c[0]);
		EXPECT_EQ(r[3], a[1]);
		EXPECT_EQ(r[4], b[1]);
		EXPECT_EQ(r[5], c[1]);
	}

	TEST(BufferDataFormatterTest, FormatsDifferentTypes) {
		int a[2]{ 1, 212 };
		char b[2]{ 'a', 'b' };

		unsigned char* c, *d;
		c = new unsigned char[2 * sizeof(int)];
		d = new unsigned char[2 * sizeof(char)];

		memcpy(c, a, 2 * sizeof(int));
		memcpy(d, b, 2 * sizeof(char));

		std::list<std::pair<OpenGL::BufferDataDescriptor, std::reference_wrapper<OpenGL::BufferDataPointer>>> descs;

		OpenGL::BufferDataDescriptor bdd1(c, sizeof(int), 2);
		OpenGL::BufferDataPointer bdp1(0, OpenGL::DataType::Float);

		OpenGL::BufferDataDescriptor bdd2(d, sizeof(char), 2);
		OpenGL::BufferDataPointer bdp2(0, OpenGL::DataType::Float);

		descs.push_back(std::make_pair(bdd1, std::ref(bdp1)));
		descs.push_back(std::make_pair(bdd2, std::ref(bdp2)));

		std::vector<unsigned char> out(2 * sizeof(int) + 2 * sizeof(char));

		OpenGL::BufferDataFormatter form;
		form.InterleaveSubData(out, 0, descs);
		delete[] c;
		delete[] d;

		int ri[2];
		char rc[2];
		memcpy(&ri[0], &out[0], sizeof(int));
		memcpy(&ri[1], &out[sizeof(int) + sizeof(char)], sizeof(int));
		memcpy(&rc[0], &out[sizeof(int)], sizeof(char));
		memcpy(&rc[1], &out[2 * sizeof(int) + sizeof(char)], sizeof(char));

		EXPECT_EQ(ri[0], a[0]);
		EXPECT_EQ(ri[1], a[1]);
		EXPECT_EQ(rc[0], b[0]);
		EXPECT_EQ(rc[1], b[1]);
	}

	TEST(BufferDataFormatterTest, OffsetsFromBeginning) {
		int a[2]{ 1, 2 };
		unsigned char* b;
		b = new unsigned char[2 * sizeof(int)];

		memcpy(b, a, 2 * sizeof(int));

		std::list<std::pair<OpenGL::BufferDataDescriptor, std::reference_wrapper<OpenGL::BufferDataPointer>>> descs;

		OpenGL::BufferDataDescriptor bdd1(b, sizeof(int), 2);
		OpenGL::BufferDataPointer bdp1(0, OpenGL::DataType::Float);

		descs.push_back(std::make_pair(bdd1, std::ref(bdp1)));

		std::vector<unsigned char> out(4 * sizeof(int));

		OpenGL::BufferDataFormatter form;
		form.InterleaveSubData(out, 2 * sizeof(int), descs);
		delete[] b;

		int r[4];
		memcpy(r, &out[0], 4 * sizeof(int));

		EXPECT_EQ(r[2], a[0]);
		EXPECT_EQ(r[3], a[1]);
	}

	std::vector<OpenGL::BufferDataPointer> ConvertToVectorOfPointers(std::list<std::pair<OpenGL::BufferDataDescriptor, std::reference_wrapper<OpenGL::BufferDataPointer>>>& descs) {
		std::vector<OpenGL::BufferDataPointer> ptrs;
		for (auto & p : descs) {
			ptrs.push_back(p.second);
		}
		return ptrs;
	}

	TEST(BufferDataFormatterTest, AssignsOffsetToSingleData) {
		char c[4]{ 'A', 'B', 'C', 'D' };

		std::list<std::pair<OpenGL::BufferDataDescriptor, std::reference_wrapper<OpenGL::BufferDataPointer>>> descs;

		OpenGL::BufferDataDescriptor bdd1(c, sizeof(char), 4);
		OpenGL::BufferDataPointer bdp1(0, OpenGL::DataType::Float);

		descs.push_back(std::make_pair(bdd1, std::ref(bdp1)));

		std::vector<unsigned char> out(4 * sizeof(char));

		OpenGL::BufferDataFormatter f;
		f.InterleaveSubData(out, 0, descs);

		auto ptrs = ConvertToVectorOfPointers(descs);

		EXPECT_EQ(ptrs.size(), 1);
		EXPECT_EQ(ptrs[0].Offset(), 0);
	}

	TEST(BufferDataFormatterTest, AssignsOffsetToMultipleData) {
		char c[4]{ 'A', 'B', 'C', 'D' };

		std::list<std::pair<OpenGL::BufferDataDescriptor, std::reference_wrapper<OpenGL::BufferDataPointer>>> descs;

		OpenGL::BufferDataDescriptor bdd1(c, sizeof(char), 4);
		OpenGL::BufferDataPointer bdp1(0, OpenGL::DataType::Float);

		OpenGL::BufferDataDescriptor bdd2(c, sizeof(char), 4);
		OpenGL::BufferDataPointer bdp2(0, OpenGL::DataType::Float);

		OpenGL::BufferDataDescriptor bdd3(c, sizeof(char), 4);
		OpenGL::BufferDataPointer bdp3(0, OpenGL::DataType::Float);

		descs.push_back(std::make_pair(bdd1, std::ref(bdp1)));
		descs.push_back(std::make_pair(bdd2, std::ref(bdp2)));
		descs.push_back(std::make_pair(bdd3, std::ref(bdp3)));

		std::vector<unsigned char> out(12 * sizeof(char));

		OpenGL::BufferDataFormatter f;
		f.InterleaveSubData(out, 0, descs);

		auto ptrs = ConvertToVectorOfPointers(descs);

		EXPECT_EQ(ptrs.size(), 3);
		EXPECT_EQ(ptrs[0].Offset(), 0);
		EXPECT_EQ(ptrs[1].Offset(), 1);
		EXPECT_EQ(ptrs[2].Offset(), 2);
	}

	TEST(BufferDataFormatterTest, AssignsStrideToSingleData) {
		char c[4]{ 'A', 'B', 'C', 'D' };

		std::list<std::pair<OpenGL::BufferDataDescriptor, std::reference_wrapper<OpenGL::BufferDataPointer>>> descs;

		OpenGL::BufferDataDescriptor bdd1(c, sizeof(char), 4);
		OpenGL::BufferDataPointer bdp1(0, OpenGL::DataType::Float);

		descs.push_back(std::make_pair(bdd1, std::ref(bdp1)));

		std::vector<unsigned char> out(4 * sizeof(char));

		OpenGL::BufferDataFormatter f;
		f.InterleaveSubData(out, 0, descs);

		auto ptrs = ConvertToVectorOfPointers(descs);

		EXPECT_EQ(ptrs.size(), 1);
		EXPECT_EQ(ptrs[0].Stride(), 0);
	}

	TEST(BufferDataFormatterTest, AssignsStrideToMultipleData) {
		char c[4]{ 'A', 'B', 'C', 'D' };

		std::list<std::pair<OpenGL::BufferDataDescriptor, std::reference_wrapper<OpenGL::BufferDataPointer>>> descs;

		OpenGL::BufferDataDescriptor bdd1(c, sizeof(char), 4);
		OpenGL::BufferDataPointer bdp1(0, OpenGL::DataType::Float);

		OpenGL::BufferDataDescriptor bdd2(c, sizeof(char), 4);
		OpenGL::BufferDataPointer bdp2(0, OpenGL::DataType::Float);

		OpenGL::BufferDataDescriptor bdd3(c, sizeof(char), 4);
		OpenGL::BufferDataPointer bdp3(0, OpenGL::DataType::Float);

		descs.push_back(std::make_pair(bdd1, std::ref(bdp1)));
		descs.push_back(std::make_pair(bdd2, std::ref(bdp2)));
		descs.push_back(std::make_pair(bdd3, std::ref(bdp3)));

		std::vector<unsigned char> out(12 * sizeof(char));

		OpenGL::BufferDataFormatter f;
		f.InterleaveSubData(out, 0, descs);

		auto ptrs = ConvertToVectorOfPointers(descs);

		EXPECT_EQ(ptrs.size(), 3);
		EXPECT_EQ(ptrs[0].Stride(), 3);
		EXPECT_EQ(ptrs[1].Stride(), 3);
		EXPECT_EQ(ptrs[2].Stride(), 3);
	}

}