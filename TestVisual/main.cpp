#include <iostream>

#include "Glfw.integration.hpp"
#include "Window.integration.hpp"
#include "OpenGL.integration.hpp"

int main(int argc, char* argv[]) {
	int testNum;
	if (argc < 2) {
		std::cout << "Run test : ";
		std::cin >> testNum;
	}
	else {
		testNum = std::atoi(argv[1]);
	}

	switch (testNum) {
	case 1:
		WindowCreation();
		break;
	case 2:
		CreateOpenGLContext();
		break;
	case 3:
		DrawTriangle();
		break;
	case 4:
		DrawColoredTriangle();
		break;
	case 5:
		UsesUniforms();
		break;
	case 6:
		UpdateBufferData();
		break;
	case 7:
		UsesTextures();
		break;
	case 8:
		GlfwTest();
		break;
	}

	return 0;
}