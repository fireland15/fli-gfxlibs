#pragma once

#include <configuration.hpp>

#include "Scene.h"

namespace fli {
	namespace gfx {
		namespace core {
			class ISystem {
			public:
				virtual void Setup(Scene& scene, util::config::Configuration& config) = 0;
				virtual void Initialize() = 0;
				virtual void Update(Scene& scene, double time) = 0;
				virtual void Stop() = 0;
			};
		}
	}
}