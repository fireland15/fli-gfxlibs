#include "gtest/gtest.h"
#include "inc/logger.hpp"


TEST(testLogger, test) {
	EXPECT_EQ(true, Logger::Instance()->Open("file"));
}