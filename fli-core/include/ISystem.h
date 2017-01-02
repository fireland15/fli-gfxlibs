#pragma once

#include <Scene.h>

namespace fli {
	namespace gfx {
		namespace core {
			class ISystem {
			public:
				virtual void Start() = 0;
				virtual void Update(Scene& scene, double time) = 0;
				virtual void Stop() = 0;
			};
		}
	}
}