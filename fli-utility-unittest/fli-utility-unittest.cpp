#include <fstream>

#include "gtest/gtest.h"
#include "inc/logger.hpp"
#include "inc/config_reader.hpp"


TEST(testLogger, test) {
	EXPECT_EQ(true, Logger::Instance()->Open("file"));
}

TEST(ConfigurationReaderTest, CopyConstructorTest) {
	std::ifstream file;
	ConfigurationReader rdr1(file);
	ConfigurationReader rdr2 = rdr1;
	ASSERT_EQ(rdr1, rdr2);
}