#pragma once

#include "attribute_variable.hpp"

namespace opengl {

	struct VertexAttributeDescriptor {
	public:
		void* pAttributes;
		int Size;
		AttributeVariable AttributeVariable;
	};

}