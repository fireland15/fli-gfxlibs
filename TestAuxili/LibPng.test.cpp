#include <GTest\gtest.h>

#include <LibPng\png.h>

namespace {

	float dist(unsigned int x, unsigned int y, unsigned int a, unsigned int b) {
		return std::sqrtf((((float)x - a) * ((float)x - a) + ((float)y - b) * ((float)y - b)));
	}

	TEST(LibPngTests, WriteAndReadImage) {
		unsigned int dim = 256;

		png_image image;
		memset(&image, 0, sizeof(image));
		image.version = PNG_IMAGE_VERSION;
		image.width = dim;
		image.height = dim;
		image.format = PNG_FORMAT_RGBA;
		image.flags = 0;
		image.colormap_entries = 0;

		png_byte* buffer = (png_byte*)malloc(sizeof(png_byte) * 4 * dim * dim);

		for (unsigned int y = 0; y < dim; y++) {
			for (unsigned int x = 0; x < dim; x++) {
				buffer[x * 4 + y * (dim * 4)] = 255;
				buffer[x * 4 + 1 + y * (dim * 4)] = 255;
				buffer[x * 4 + 2 + y * (dim * 4)] = 150;
				buffer[x * 4 + 3 + y * (dim * 4)] = 255;
			}
		}

		auto v = png_image_write_to_file(&image, "LibPngTests_CreatePngImage.png", 0, buffer, 0, NULL);

		png_image readImage;
		memset(&readImage, 0, sizeof(readImage));
		readImage.version = PNG_IMAGE_VERSION;

		if (png_image_begin_read_from_file(&readImage, "LibPngTests_CreatePngImage.png")) {
			readImage.format = PNG_FORMAT_RGBA;

			unsigned int size = PNG_IMAGE_SIZE(readImage);
			
			if (png_image_finish_read(&readImage, NULL, buffer, 0, NULL)) {
				for (unsigned int y = 0; y < dim; y++) {
					for (unsigned int x = 0; x < dim; x++) {
						if (dist(x, y, 100, 100) < 30.0f || dist(x, y, 100, 100) > 50.0f) {
							buffer[x * 4 + y * (dim * 4)] = 10;
							buffer[x * 4 + 1 + y * (dim * 4)] = 90;
							buffer[x * 4 + 2 + y * (dim * 4)] = 70;
							buffer[x * 4 + 3 + y * (dim * 4)] = 255;
						}
					}
				}

				png_image_write_to_file(&readImage, "LibPngTests_CreatePngImage2.png", 0, buffer, 0, NULL);
			}
		}

		free(buffer);
	}

}