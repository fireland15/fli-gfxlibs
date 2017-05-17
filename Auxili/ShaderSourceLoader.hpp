#pragma once

#include <string>
#include <memory>

namespace OpenGL {

	class ShaderSource;

	namespace Auxili {

		class ShaderSourceLoader {
		public:
			ShaderSourceLoader();
			std::unique_ptr<ShaderSource> Load(std::string & filename);
		};

	}
}