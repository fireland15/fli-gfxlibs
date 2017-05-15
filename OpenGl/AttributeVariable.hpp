#pragma once

#include <string>

#include <AttributeTypeEnum.hpp>

namespace OpenGL {

	class AttributeVariable {
	public:
		AttributeVariable(int location, std::string name, AttributeType type);
		AttributeType Type() const;
		std::string Name() const;
		int Location() const;
		bool operator<(const AttributeVariable & other) const;

	private:
		AttributeType _type;
		std::string _name;
		int _location;
	};

}