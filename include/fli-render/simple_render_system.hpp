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
#include <fli-opengl\context.hpp>

typedef logging::LoggerBase LoggerBase;
typedef config::Configuration Configuration;

namespace gfx {
	namespace render {

		class SimpleRenderSystem : public core::IRenderer, public core::SystemBase {

		private:
			Configuration* m_pConfig;

			opengl::OpenGlContext* m_pContext;

			bool m_shouldRender = true;

		public:
			SimpleRenderSystem(opengl::OpenGlContext* context);

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