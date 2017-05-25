#include "PngImageLoader.hpp"

#include <sstream>
#include <LibPng\png.h>
#include <iostream>
#include <glm\gtc\type_ptr.hpp>

#include "InvalidFileTypeException.hpp"
#include "FileIOException.hpp"
#include "ImageData.hpp"

std::unique_ptr<Auxili::ImageData> Auxili::PngImageLoader::Load(std::string & file) {
	return Load(file.c_str());
}

std::unique_ptr<Auxili::ImageData> Auxili::PngImageLoader::Load(const char * file) {
	std::vector<glm::u8vec4> pixels;
	png_image image;
	memset(&image, 0, sizeof(image));
	image.version = PNG_IMAGE_VERSION;

	if (png_image_begin_read_from_file(&image, file)) {
		png_byte* buffer;

		image.format = PNG_FORMAT_RGBA;

		unsigned int size = PNG_IMAGE_SIZE(image);
		buffer = (png_bytep)malloc(size);

		if (buffer != nullptr) {
			if (png_image_finish_read(&image, NULL, buffer, 0, NULL)) {
				pixels.reserve(size / 4);
				for (unsigned int i = 0; i < image.width * image.height; i++) {
					pixels.emplace_back(buffer[(i * 4) + 0], buffer[(i * 4) + 1], buffer[(i * 4) + 2], buffer[(i * 4) + 3]);
				}
			}
		}
	}

	return std::unique_ptr<Auxili::ImageData>(new Auxili::ImageData(pixels, glm::uvec2(static_cast<unsigned int>(image.width), static_cast<unsigned int>(image.height))));
}

void Auxili::PngImageLoader::Save(const std::string & file, ImageData & image) {
	Save(file.c_str(), image);
}

void Auxili::PngImageLoader::Save(const char * file, ImageData & image) {
	png_image pngImage;
	memset(&pngImage, 0, sizeof(image));
	pngImage.version = PNG_IMAGE_VERSION;
	pngImage.width = image.Dimensions.x;
	pngImage.height = image.Dimensions.y;
	pngImage.format = PNG_FORMAT_RGBA;
	pngImage.flags = 0;
	pngImage.colormap_entries = 0;

	png_image_write_to_file(&pngImage, file, 0, glm::value_ptr(image.Pixels.front()), 0, NULL);
}

