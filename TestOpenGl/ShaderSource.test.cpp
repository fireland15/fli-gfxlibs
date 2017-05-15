#include <gtest.h>

#include <sstream>

#include <ShaderSource.hpp>

namespace {

	TEST(ShaderSourceTest, ReadsSourceFromFileStream) {
		std::string code = "Here is some glsl shader code, but not really. Don't compile me!";

		std::stringstream ss(code);

		OpenGL::ShaderSource source(ss);

		EXPECT_EQ(code, source.Code());
	}

}