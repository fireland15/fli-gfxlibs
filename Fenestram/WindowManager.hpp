#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <string>

namespace Fenestram {

	class Window;

	class WindowManager {
	public:
		WindowManager();
		~WindowManager();

		std::unique_ptr<Window> GetNewWindow(glm::uvec2 windowDim, std::string windowTitle);

	private:
	};

}