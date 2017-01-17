#include "shader_source.hpp"

namespace opengl {

	ShaderSource::ShaderSource() { }

	ShaderSource::ShaderSource(std::string source) {
		m_source.push_back(source);
	}

	ShaderSource::ShaderSource(std::ifstream& stream) {
		std::string line;
		while (std::getline(stream, line)) {
			m_source.push_back(line);
		}
	}

	void ShaderSource::AddSource(std::string source) {
		m_source.push_back(source);
	}

	std::string ShaderSource::Code() {
		std::stringstream ss;

		for (std::string src : m_source) {
			ss << src;
		}

		return ss.str();
	}

}