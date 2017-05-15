#pragma once

#include <string>
#include <UniformTypeEnum.hpp>

namespace OpenGL {

	class UniformVariable {
	public:
		UniformVariable(int location, std::string name, UniformType type);
		UniformType Type() const;
		int Location() const;
		std::string Name() const;
		bool operator<(const UniformVariable other) const;

	private:
		UniformType _type;
		int _location;
		std::string _name;
	};

}