#pragma once

#include <string>
#include <list>
#include <fstream>
#include <sstream>

#include <GL\glew.h>
#include <GL\GL.h>

namespace opengl {

	class ShaderSource {
	public:
		ShaderSource();

		ShaderSource(std::string source);

		// Reads all lines and adds to source
		ShaderSource(std::ifstream& stream);

		// When  compiling source, it is evaluated in the order added
		void AddSource(std::string source);

		std::string Code();

	private:
		std::list<std::string> m_source;

	};

}