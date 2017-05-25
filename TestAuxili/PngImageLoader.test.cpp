#include <GTest\gtest.h>

#include <Auxili\PngImageLoader.hpp>
#include <Auxili\ImageData.hpp>
#include <vector>
#include <memory>

namespace {

	TEST(PngImageLoaderTests, SavesAndLoadsImage) {
		std::vector<glm::u8vec4> pixels;
		glm::uvec2 dim(100, 100);
		pixels.reserve(dim.x * dim.y);
		for (unsigned int i = 0; i < dim.x * dim.y; i++) {
			pixels.emplace_back(150, 150, 255, 255);
		}

		Auxili::ImageData imageData(pixels, dim);

		Auxili::PngImageLoader loader;
		loader.Save("PngImageLoaderTests_SavesAndLoadsImage.png", imageData);

		auto image = loader.Load(std::string("PngImageLoaderTests_SavesAndLoadsImage.png"));
		EXPECT_EQ(image->Dimensions, dim);
	}

}