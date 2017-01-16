#pragma once

#include "vertex.hpp"

namespace gfx {
	namespace resources {
		
		template<typename TVertex>
		struct Triangle {
			TVertex vertex[3];
		};

	}
}