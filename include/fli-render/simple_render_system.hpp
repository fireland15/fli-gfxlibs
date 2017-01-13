#pragma once

#include <fli-core\irenderer.hpp>
#include <fli-core\scene.hpp>
#include <fli-core\transform_component.hpp>
#include <fli-utility\logger_base.hpp>
#include <fli-utility\configuration.hpp>

#include "opengl_context.hpp"

typedef logging::LoggerBase LoggerBase;
typedef config::Configuration Configuration;

namespace gfx {
	namespace render {

		class RenderSystem : public core::IRenderer {

		private:
			LoggerBase* m_pLogger;
			Configuration* m_pConfig;
			float theta = 0.0f;
			OpenGlContext* mp_context;

		public:
			RenderSystem(OpenGlContext* context);

			void SetLogger(LoggerBase* pLogger);
			void SetConfig(Configuration* pConfig);

			virtual void Setup(core::Scene& scene, config::Configuration & config) override;

			virtual void Initialize() override;
			virtual void Update(core::Scene& scene, double time) override;
			virtual void Render(core::Scene& scene, double time) override;
			virtual void Stop() override;

		};

	}
}