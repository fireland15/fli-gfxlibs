#pragma once

#include <glm\glm.hpp>

namespace gfx {
	namespace resources {

		struct NormalTexturedVertex {
			glm::vec3 Position;
			glm::vec3 Normal;
			glm::vec2 TexCord;
		};

	}
}