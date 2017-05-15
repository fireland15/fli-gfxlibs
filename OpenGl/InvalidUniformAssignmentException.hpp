#pragma once

#include "Exception.hpp"

#include <UniformTypeEnum.hpp>

namespace OpenGL {

	class InvalidUniformAssignmentException : public Exception {
	public:
		InvalidUniformAssignmentException();
		InvalidUniformAssignmentException(const std::string & name, OpenGL::UniformType uniformType, OpenGL::UniformType attemptedType);
		virtual std::string Message() override;

	private:
		UniformType _uniformType;
		UniformType _attemptedType;
		std::string _name;
	};

}