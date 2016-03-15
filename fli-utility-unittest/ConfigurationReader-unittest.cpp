#include <fstream>

#include "gtest/gtest.h"
#include "inc/logger.hpp"
#include "inc/config_reader.hpp"
#include "inc/configuration.hpp"

class ConfigurationReaderTest : public ::testing::Test {
protected:
	std::ifstream file;
	fli::util::config::Configuration config;
	bool result;

	virtual void SetUp() {
		file.open("config.txt");
		fli::util::config::ConfigurationReader rdr(file);
		config = fli::util::config::ConfigurationReader(rdr);
		result = false;
	}

	virtual void TearDown() {
		file.close();
	}
};

TEST_F(ConfigurationReaderTest, BoolExist) {
	bool reply;
	result = config.Get("testBool", reply);
	EXPECT_EQ(true, result);
	EXPECT_EQ(true, reply);
}

TEST_F(ConfigurationReaderTest, BoolNotExist) {
	bool reply;
	result = config.Get("testBoolNExist", reply);
	EXPECT_EQ(false, result);
}

TEST_F(ConfigurationReaderTest, IntExist) {
	int reply = -1;
	result = config.Get("testInt", reply);
	EXPECT_EQ(true, result);
	EXPECT_EQ(42, reply);
}

TEST_F(ConfigurationReaderTest, IntNotExist) {
	int reply = -1;
	result = config.Get("testIntNExist", reply);
	EXPECT_EQ(false, result);
}

TEST_F(ConfigurationReaderTest, UIntExist) {
	int reply = -1;
	result = config.Get("testUInt", reply);
	EXPECT_EQ(true, result);
	EXPECT_EQ(15616, reply);
}

TEST_F(ConfigurationReaderTest, UIntNotExist) {
	int reply = -1;
	result = config.Get("testUIntNExist", reply);
	EXPECT_EQ(false, result);
}

TEST_F(ConfigurationReaderTest, StringExist) {
	std::string reply;
	result = config.Get("testString", reply);
	EXPECT_EQ(true, result);
	EXPECT_EQ(std::string("test"), reply);
}

TEST_F(ConfigurationReaderTest, StringNotExist) {
	std::string reply;
	result = config.Get("testStringNExist", reply);
	EXPECT_EQ(false, result);
}

TEST_F(ConfigurationReaderTest, CharExist) {
	char reply;
	result = config.Get("testChar", reply);
	EXPECT_EQ(true, result);
	EXPECT_EQ('t', reply);
}

TEST_F(ConfigurationReaderTest, CharNotExist) {
	char reply;
	result = config.Get("testCharNExist", reply);
	EXPECT_EQ(false, result);
}

TEST_F(ConfigurationReaderTest, UCharExist) {
	unsigned char reply;
	result = config.Get("testUChar", reply);
	EXPECT_EQ(true, result);
	EXPECT_EQ(15, reply);
}

TEST_F(ConfigurationReaderTest, UCharNotExist) {
	unsigned char reply;
	result = config.Get("testUCharNExist", reply);
	EXPECT_EQ(false, result);
}

TEST_F(ConfigurationReaderTest, ShortExist) {
	short reply;
	result = config.Get("testShort", reply);
	EXPECT_EQ(true, result);
	EXPECT_EQ(32767, reply);
}

TEST_F(ConfigurationReaderTest, ShortNotExist) {
	short reply;
	result = config.Get("testShortNExist", reply);
	EXPECT_EQ(false, result);
}

TEST_F(ConfigurationReaderTest, UShortExist) {
	unsigned short reply;
	result = config.Get("testUShort", reply);
	EXPECT_EQ(true, result);
	EXPECT_EQ(65535, reply);
}

TEST_F(ConfigurationReaderTest, UShortNotExist) {
	unsigned short reply;
	result = config.Get("testUShortNExist", reply);
	EXPECT_EQ(false, result);
}

TEST_F(ConfigurationReaderTest, LongExist) {
	long reply;
	result = config.Get("testLong", reply);
	EXPECT_EQ(true, result);
	EXPECT_EQ(156166453, reply);
}

TEST_F(ConfigurationReaderTest, LongNotExist) {
	long reply;
	result = config.Get("testLongNExist", reply);
	EXPECT_EQ(false, result);
}

TEST_F(ConfigurationReaderTest, ULongExist) {
	unsigned long reply;
	result = config.Get("testULong", reply);
	EXPECT_EQ(true, result);
	EXPECT_EQ(156166453, reply);
}

TEST_F(ConfigurationReaderTest, ULongNotExist) {
	unsigned long reply;
	result = config.Get("testULongNExist", reply);
	EXPECT_EQ(false, result);
}

TEST_F(ConfigurationReaderTest, DoubleExist) {
	double reply;
	result = config.Get("testDouble", reply);
	EXPECT_EQ(true, result);
	EXPECT_EQ(3.14159, reply);
}

TEST_F(ConfigurationReaderTest, DoubleNotExist) {
	double reply;
	result = config.Get("testDoubleNExist", reply);
	EXPECT_EQ(false, result);
}

TEST_F(ConfigurationReaderTest, FloatExist) {
	float reply;
	result = config.Get("testFloat", reply);
	EXPECT_EQ(true, result);
	EXPECT_EQ(3.141592f, reply);
}

TEST_F(ConfigurationReaderTest, FloatNotExist) {
	float reply;
	result = config.Get("testFloatNExist", reply);
	EXPECT_EQ(false, result);
}