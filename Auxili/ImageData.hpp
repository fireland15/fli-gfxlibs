#pragma once

#include <vector>
#include <glm\glm.hpp>

namespace Auxili {

	class ImageData {
	public:
		ImageData(std::vector<glm::u8vec4>& pixels, glm::uvec2 & dim) 
			: Pixels(pixels), Dimensions(dim) { }
		ImageData(unsigned char * pixels, glm::uvec2 & dim);
		~ImageData() { }

		std::vector<glm::u8vec4> Pixels;
		glm::uvec2 Dimensions;
	};

}