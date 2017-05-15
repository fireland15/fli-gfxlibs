#pragma once

#include "Exception.hpp"

namespace OpenGL {

	class AttributeNotFoundException : public Exception {
	public:
		AttributeNotFoundException();
		AttributeNotFoundException(const std::string & name);
		virtual std::string Message() override;

	private:
		std::string _attributeName;
	};

}