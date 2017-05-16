#pragma once

#include <string>

namespace Fenestram {

	class GlfwInitializationException {
	public:
		GlfwInitializationException();
		virtual std::string Message();
	private:
		std::string _message;
	};

}