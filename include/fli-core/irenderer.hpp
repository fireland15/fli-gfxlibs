#pragma once

#include <fli-utility\configuration.hpp>

#include "isystem.hpp"
#include "scene.hpp"

namespace core {

	class IRenderer : public ISystem {

	public:
		virtual void Setup(Scene& scene) = 0;
		virtual void Initialize() = 0;
		virtual void Update(Scene& scene, double time) = 0;
		virtual void Render(Scene& scene, double time) = 0;
		virtual void Stop() = 0;
	};

}