#pragma once

#include <memory>
#include <string>
#include <fstream>

namespace Auxili {

	class ImageData;

	class BmpImageLoader {
	public:
		std::unique_ptr<ImageData> Load(const char * file);
		std::unique_ptr<ImageData> Load(std::string & file);

		void Save(const char * file, ImageData & image);
		void Save(std::string & file, ImageData & image);
	};

}