#include <iostream>

#include "Glfw.integration.hpp"
#include "OpenGL.integration.hpp"
#include "ShaderLoader.integration.hpp"
#include "Camera.integration.hpp"
#include "UserInputMapper.integration.hpp"

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
		UsesShadersFromFile();
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
	case 9:
		UsesTexturesFromPngFile();
		break;
	case 10:
		UsesTexturesFromBmpFile();
		break;
	case 11:
		UsesCamera();
		break;
	case 12:
		UsesCameraWithObjBunny();
		break;
	case 13:
		TokenizesFile();
		break;
	case 14:
		ParsesTokens();
		break;
	case 15:
		ParsesTokensFromFile();
		break;
	case 16:
		VisualTest();
		break;
	case 17:
		UsesKeyState();
		break;
	}

	return 0;
}