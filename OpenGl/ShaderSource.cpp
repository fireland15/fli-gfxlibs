#include "ShaderSource.hpp"

#include <sstream>

OpenGL::ShaderSource::ShaderSource() {

}

OpenGL::ShaderSource::ShaderSource(const std::string & source) 
	: _source(source) {

}

OpenGL::ShaderSource::ShaderSource(std::istream & stream) {
	std::stringstream ss;
	if (stream) {
		ss << stream.rdbuf();
	}
	_source = ss.str();
}

const std::string & OpenGL::ShaderSource::Code() {
	return _source;
}
