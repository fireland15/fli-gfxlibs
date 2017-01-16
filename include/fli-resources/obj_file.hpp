#pragma once

#include <fstream>
#include <string>

namespace gfx {
	namespace resources {

		class ObjFile {
		private:
			std::ifstream m_file;

			ObjFile(std::ifstream file);

		public:
			static ObjFile Open(std::string filepath);

			 
		};

	}
}