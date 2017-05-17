#include "ShaderSourceLoader.hpp"

#include <fstream>
#include <OpenGl\ShaderSource.hpp>

OpenGL::Auxili::ShaderSourceLoader::ShaderSourceLoader() { }

std::unique_ptr<OpenGL::ShaderSource> OpenGL::Auxili::ShaderSourceLoader::Load(std::string & filename) {
	if (filename.empty())
		throw std::exception("Filename was empty");
	
	std::ifstream file(filename);
	if (!file.is_open())
		throw std::exception("Could not open file");

	OpenGL::ShaderSource* source = new OpenGL::ShaderSource(file);

	file.close();

	return std::unique_ptr<ShaderSource>(source);
}
