#pragma once

#include "Exception.hpp"

namespace OpenGL {

	class UniformNotFoundException : public Exception {
	public:
		UniformNotFoundException();
		UniformNotFoundException(const std::string & name);
		virtual std::string Message() override;

	private:
		std::string _uniformName;
	};

}