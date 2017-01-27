#pragma once

#include "attribute_variable.hpp"

namespace opengl {

	struct VertexAttributeDescriptor {
	public:
		void* pAttributes;
		unsigned int Size;
		AttributeVariable AttributeVariable;
	};

}