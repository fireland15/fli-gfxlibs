#include "RenderSystem.h"

namespace fli {
	namespace gfx {
		namespace render {
			void RenderSystem::SetLogger(LoggerBase* pLogger) {
				m_pLogger = pLogger;
			}

			void RenderSystem::SetConfig(Configuration* pConfig) {
				m_pConfig = pConfig;
			}

			void RenderSystem::Setup(core::Scene& scene, util::config::Configuration & config) {

			}

			void RenderSystem::Initialize() {

			}

			void RenderSystem::Update(core::Scene& worldState, double time) {

			}

			void RenderSystem::Render(core::Scene& scene, double time) {

			}

			void RenderSystem::Stop() {

			}
		}
	}
}