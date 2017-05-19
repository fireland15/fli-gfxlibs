#include "ShaderLoader.integration.hpp"

#include <iostream>
#include <Auxili\ShaderSourceLoader.hpp>
#include <OpenGl\ShaderSource.hpp>

void UsesShadersFromFile() {
	OpenGL::Auxili::ShaderSourceLoader loader;

	try {
		auto vsSource = loader.Load(std::string("Shaders/vs_color.glsl"));
		std::cout << "Vertex Source\n" << vsSource->Code() << std::endl;

		auto fsSource = loader.Load(std::string("Shaders/fs_color.glsl"));
		std::cout << "Fragment Source\n" << fsSource->Code() << std::endl;
	}
	catch (std::exception ex) {
		std::cout << ex.what() << std::endl;
	}
}