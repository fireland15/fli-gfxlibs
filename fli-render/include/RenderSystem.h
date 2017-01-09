#pragma once

#include <IRenderer.h>
#include <OpenGlContext.h>
#include <Scene.h>
#include <logger_base.hpp>
#include <configuration.hpp>

#include <TransformComponent.h>

typedef fli::util::log::LoggerBase LoggerBase;
typedef fli::util::config::Configuration Configuration;

namespace fli {
	namespace gfx {
		namespace render {
			class RenderSystem : public core::IRenderer {
			private:
				LoggerBase* m_pLogger;
				Configuration* m_pConfig;

				OpenGlContext m_context;

			public:
				RenderSystem(OpenGlContext context)
					: m_context(context) { }

				void SetLogger(LoggerBase* pLogger);
				void SetConfig(Configuration* pConfig);

				virtual void Setup(core::Scene& scene, util::config::Configuration & config) override {
					if (!scene.IsComponentInScene<core::TransformComponent>()) {
						scene.AddComponent<core::TransformComponent>();
					}
					if (!scene.IsComponentInScene<core::DynamicRenderMeshComponent>()) {
						scene.AddComponent<core::DynamicRenderMeshComponent>();
					}
					if (!scene.IsComponentInScene<core::StaticRenderMeshComponent>()) {
						scene.AddComponent<core::StaticRenderMeshComponent>();
					}
				}

				virtual void Initialize() override;
				virtual void Update(core::Scene& scene, double time) override;
				virtual void Render(core::Scene& scene, double time) override;
				virtual void Stop() override;
			};
		}
	}
}