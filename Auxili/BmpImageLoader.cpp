#include "BmpImageLoader.hpp"
#include "FileIOException.hpp"
#include "InvalidFileTypeException.hpp"
#include "InvalidArgumentException.hpp"
#include "ImageData.hpp"
#include <vector>
#include <glm\glm.hpp>
#include <iterator>
#include <fstream>

std::unique_ptr<Auxili::ImageData> Auxili::BmpImageLoader::Load(const char * file) {
	return Load(std::string(file));
}

std::unique_ptr<Auxili::ImageData> Auxili::BmpImageLoader::Load(std::string & file) {
	size_t index = file.find_last_of('.');
	std::string extension = file.substr(index + 1);
	if (extension != "bmp") {
		throw Auxili::InvalidFileTypeException(file, "bmp");
	}

	unsigned char header[54];
	unsigned int dataPos;
	unsigned int width;
	unsigned int height;
	unsigned int imageSize;
	unsigned char* data;

	FILE* f = fopen(file.c_str(), "rb");
	if (!f) {
		throw Auxili::FileIOException(file);
	}

	if (fread(header, 1, 54, f) != 54) {
		throw Auxili::InvalidFileTypeException(file, "bmp");
	}

	if (header[0] != 'B' && header[1] != 'M') {
		throw Auxili::InvalidFileTypeException(file, "bmp");
	}

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	if (imageSize == 0) {
		imageSize = width * height * 3;
	}

	if (dataPos == 0) {
		dataPos = 54;
	}

	data = new unsigned char[imageSize];
	fread(data, 1, imageSize, f);
	fclose(f);

	std::vector<glm::u8vec4> pixels;
	pixels.reserve(width * height);

	for (unsigned int i = 0; i < width * height; i++) {
		// reverse order since bitmaps are BGR
		pixels.emplace_back(data[3 * i + 2], data[3 * i + 1], data[3 * i], 255);
	}

	glm::uvec2 dim(width, height);

	return std::unique_ptr<Auxili::ImageData>(new ImageData(pixels, dim));
}

void saveImage(std::string& filename, unsigned int width, unsigned int height, unsigned char* data) {
	int dataPos = 54;
	unsigned int imageSize = width * height * 3;
	unsigned char header[54];
	header[0] = 'B';
	header[1] = 'M';
	*(int*)(&header[0x0A]) = dataPos;
	*(int*)(&header[0x22]) = imageSize;
	*(int*)(&header[0x12]) = width;
	*(int*)(&header[0x16]) = height;

	std::fstream f(filename, std::ios::binary);
	if (!f.is_open()) {
		throw Auxili::FileIOException(filename);
	}

	f.write(reinterpret_cast<const char*>(header), 54);
	f.write(reinterpret_cast<const char*>(data), imageSize);
	f.close();
}

void Auxili::BmpImageLoader::Save(const char * file, Auxili::ImageData & image) {
	unsigned int width;
	unsigned int height;

	width = image.Dimensions.x;
	height = image.Dimensions.y;

	if (width == 0) {
		throw Auxili::InvalidArgumentException(std::string("Image Width"), std::string("Cannot save image with 0 width"));
	}
	if (height == 0) {
		throw Auxili::InvalidArgumentException(std::string("Image Height"), std::string("Cannot save image with 0 height"));
	}
	
	std::vector<unsigned char> pixels(image.Pixels.size() * 3);

	for (unsigned int i = 0; i < image.Pixels.size(); i++) {
		unsigned int x = i * 3;
		pixels[x + 2] = image.Pixels[i].r;
		pixels[x + 1] = image.Pixels[i].g;
		pixels[x] = image.Pixels[i].b;
	}

	saveImage(std::string(file), width, height, pixels.data());
}

void Auxili::BmpImageLoader::Save(std::string & file, Auxili::ImageData & image) {

}
