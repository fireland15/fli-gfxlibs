#pragma once

#include <string>

namespace Fenestram {

	class WindowCreationException {
	public:
		WindowCreationException();
		WindowCreationException(std::string message);
		virtual std::string Message();
	private:
		std::string _message;
	};

}