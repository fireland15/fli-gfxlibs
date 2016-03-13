#include <fstream>

#include "gtest/gtest.h"
#include "inc/logger.hpp"
#include "inc/config_reader.hpp"
#include "inc/configuration.hpp"

class ConfigurationReaderTest : public ::testing::Test {
protected:
	std::ifstream file;
	Configuration config;
	bool result;

	virtual void SetUp() {
		file.open("config.txt");
		ConfigurationReader rdr(file);
		config = ConfigurationReader(rdr);
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