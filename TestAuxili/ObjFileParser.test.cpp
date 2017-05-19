#include <GTest\gtest.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <memory>
#include <Auxili\ObjFileParser.hpp>
#include <Auxili\ObjFileData.hpp>

namespace {

	TEST(ObjFileParserTest, AddsErrorForBadNumberInVertex) {
		std::stringstream ss;
		ss << "v 1.0002 1.00bad23 2.32334\n";
		Auxili::ObjFileParser parser;
		auto data = parser.Parse(ss);
		auto & errors = parser.Errors();
		
		EXPECT_EQ(errors.size(), 1);
	}

	TEST(ObjFileParserTest, AddsErrorNotEnoughVertices) {
		std::stringstream ss;
		ss << "v 1.0002 1.0023\n";
		Auxili::ObjFileParser parser;
		auto data = parser.Parse(ss);
		auto & errors = parser.Errors();

		EXPECT_EQ(errors.size(), 1);
	}

	TEST(ObjFileParserTest, AddsErrorForBadNumberInNormal) {
		std::stringstream ss;
		ss << "vn 1.0002 1.00bad23 2.32334\n";
		Auxili::ObjFileParser parser;
		auto data = parser.Parse(ss);
		auto & errors = parser.Errors();

		EXPECT_EQ(errors.size(), 1);
	}

	TEST(ObjFileParserTest, AddsErrorForNotEnoughNormals) {
		std::stringstream ss;
		ss << "vn 1.0002 2.32334\n";
		Auxili::ObjFileParser parser;
		auto data = parser.Parse(ss);
		auto & errors = parser.Errors();

		EXPECT_EQ(errors.size(), 1);
	}

	TEST(ObjFileParserTest, AddsErrorForBadNumberInTexCoords) {
		std::stringstream ss;
		ss << "vt 1.0002 j1.00bad23\n";
		Auxili::ObjFileParser parser;
		auto data = parser.Parse(ss);
		auto & errors = parser.Errors();

		EXPECT_EQ(errors.size(), 1);
	}

	TEST(ObjFileParserTest, AddsErrorForNotEnoughTexCoords) {
		std::stringstream ss;
		ss << "vt 1.0002\n";
		Auxili::ObjFileParser parser;
		auto data = parser.Parse(ss);
		auto & errors = parser.Errors();

		EXPECT_EQ(errors.size(), 1);
	}

	TEST(ObjFileParserTest, AddsThreeIndicesForFaces) {
		std::stringstream ss;
		ss << "f 1/1/1 1/1/1 1/1/1";
		Auxili::ObjFileParser parser;
		auto data = parser.Parse(ss);
		auto & errors = parser.Errors();
		EXPECT_EQ(data->Faces().size(), 1);
		EXPECT_EQ(data->Faces()[0][0].Vertex, 1);
		EXPECT_EQ(data->Faces()[0][0].Normal, 1);
		EXPECT_EQ(data->Faces()[0][0].TexCoord, 1);
	}

	TEST(ObjFileParserTest, FacesHaveNoTexCoordSetToNegativeOne) {
		std::stringstream ss;
		ss << "f 1//1 1//1 1//1";
		Auxili::ObjFileParser parser;
		auto data = parser.Parse(ss);
		auto & errors = parser.Errors();
		EXPECT_EQ(data->Faces().size(), 1);
		EXPECT_EQ(data->Faces()[0][0].Vertex, 1);
		EXPECT_EQ(data->Faces()[0][0].Normal, 1);
		EXPECT_EQ(data->Faces()[0][0].TexCoord, -1);
	}

	TEST(ObjFileParserTest, FacesHaveNoNormalCoordsSetToNegativeOne) {
		std::stringstream ss;
		ss << "f 1/1 1/1 1/1";
		Auxili::ObjFileParser parser;
		auto data = parser.Parse(ss);
		auto & errors = parser.Errors();
		EXPECT_EQ(data->Faces().size(), 1);
		EXPECT_EQ(data->Faces()[0][0].Vertex, 1);
		EXPECT_EQ(data->Faces()[0][0].Normal, -1);
		EXPECT_EQ(data->Faces()[0][0].TexCoord, 1);
	}

	TEST(ObjFileParserTest, AddsParserErrorForBadFormat) {
		std::stringstream ss;
		ss << "f 1/1 asdasd";
		Auxili::ObjFileParser parser;
		auto data = parser.Parse(ss);
		auto & errors = parser.Errors();
		EXPECT_EQ(errors.size(), 1);
	}

	TEST(ObjFileParserTest, ParserBunnyObj) {
		std::ifstream file("Models/bunny.obj");
		Auxili::ObjFileParser parser;
		auto data = parser.Parse(file);	
	}

}