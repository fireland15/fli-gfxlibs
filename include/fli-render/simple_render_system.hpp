#pragma once

#include <string>
#include <memory>
#include <sstream>

#include <fli-core\irenderer.hpp>
#include <fli-core\system_base.hpp>
#include <fli-core\scene.hpp>
#include <fli-core\transform_component.hpp>
#include <fli-utility\logger_base.hpp>
#include <fli-utility\configuration.hpp>

#include "opengl_context.hpp"
#include "opengl_error.hpp"

typedef logging::LoggerBase LoggerBase;
typedef config::Configuration Configuration;

namespace gfx {
	namespace render {

		class SimpleRenderSystem : public core::IRenderer, public core::SystemBase {

		private:
			Configuration* m_pConfig;

			OpenGlContext* m_pContext;

			float theta = 0.0f;

			bool m_shouldRender = true;

		public:
			SimpleRenderSystem(OpenGlContext* context);

			void SetConfig(Configuration* pConfig);

			virtual void Setup(core::Scene& scene) override;

			virtual void Initialize() override;
			virtual void Update(core::Scene& scene, double time) override;
			virtual void Render(core::Scene& scene, double time) override;
			virtual void Stop() override;

			/*************************************************************
			* Configuration Methods
			**************************************************************/

		private:

			void Configure();

		};

	}
}