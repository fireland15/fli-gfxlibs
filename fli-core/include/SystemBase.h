#pragma once

#include <Scene.h>

namespace fli {
	namespace gfx {
		namespace core {
			class SystemBase {
			public:
				virtual void Start() = 0;
				virtual void Update(Scene& worldState, double time) = 0;
				virtual void Stop() = 0;
			};
		}
	}
}