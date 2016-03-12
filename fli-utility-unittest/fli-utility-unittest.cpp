#include <fstream>

#include "gtest/gtest.h"
#include "inc/logger.hpp"
#include "inc/config_reader.hpp"


TEST(ConfigurationReaderTest, CanGetBoolean) {
	std::ifstream file("config.txt");
	ConfigurationReader rdr(file);
	bool reply;
	bool result = rdr.Read("testBool", reply);
	EXPECT_EQ(false, result);
	EXPECT_EQ(false, reply);
}

TEST(ConfigurationReaderTest, CanGetInt) {
	std::ifstream file("config.txt");
	ConfigurationReader rdr(file);
	bool reply;
	bool result = rdr.Read("testInt", reply);
	EXPECT_EQ(true, result);
	EXPECT_EQ(42, reply);
}