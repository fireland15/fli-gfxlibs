#pragma once

#include "Exception.hpp"

namespace OpenGL {

	class BufferDataException : public Exception {
	public:
		BufferDataException(std::string message);
		virtual ~BufferDataException();
		virtual std::string Message() override;
	private:
		std::string _message;
	};

}