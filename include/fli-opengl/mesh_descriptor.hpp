#pragma once

#include <vector>

#include <glm\glm.hpp>

#include "vertex_attribute_descriptor.hpp"
#include "attribute_variable.hpp"

namespace opengl {

	struct MeshDescriptor {
	public:
		std::vector<glm::vec3> Vertices;
		AttributeVariable PositionVariable;
		std::vector<VertexAttributeDescriptor> AttributeDescriptors;
	};

}