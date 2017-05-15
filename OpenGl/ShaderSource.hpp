#pragma once

#include <string>
#include <fstream>

namespace OpenGL {

	class ShaderSource {
	public:
		ShaderSource();
		ShaderSource(const std::string& source);
		ShaderSource(std::istream& stream);
		const std::string & Code();

	private:
		std::string _source;
	};

}