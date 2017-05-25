#pragma once

#include <vector>
#include <memory>


namespace Auxili {

	struct ImageData;

	class PngImageLoader {
	public:
		std::unique_ptr<ImageData> Load(std::string& file);
		std::unique_ptr<ImageData> Load(const char * file);

		void Save(const char* file, ImageData & image);
		void Save(const std::string & file, ImageData & image);
	};

}