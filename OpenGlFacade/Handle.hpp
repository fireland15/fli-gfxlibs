#pragma once

#include "ObjectTypeEnum.hpp"

namespace OpenGL {

	class Handle {
	public:
		Handle(ObjectType type, unsigned int h);
		bool operator==(const Handle& other);
		bool operator!=(const Handle& other);
		ObjectType Type() const;
		unsigned int Value() const;

		static Handle Default();

	private:
		unsigned int _value;
		ObjectType _type;
	};

}