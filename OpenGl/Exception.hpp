#pragma once

#include <string>

namespace OpenGL {

	class Exception {
	public:
		virtual std::string Message() = 0;
	};

}