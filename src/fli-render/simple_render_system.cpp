#include "simple_render_system.hpp"

namespace gfx {
	namespace render {

		RenderSystem::RenderSystem(OpenGlContext* context)
			: mp_context(context) {

		}

		void RenderSystem::SetLogger(LoggerBase* pLogger) {
			m_pLogger = pLogger;
		}

		void RenderSystem::SetConfig(Configuration* pConfig) {
			m_pConfig = pConfig;
		}

		void RenderSystem::Setup(core::Scene& scene, config::Configuration & config) {
			if (!scene.IsComponentInScene<core::TransformComponent>()) {
				scene.AddComponent<core::TransformComponent>();
			}
		}

		void RenderSystem::Initialize() {

		}

		void RenderSystem::Update(core::Scene& worldState, double time) {

		}

		void RenderSystem::Render(core::Scene& scene, double time) {
			glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glPushMatrix();
			glRotatef(theta, 0.0f, 0.0f, 1.0f);
			glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(0.0f, 1.0f);
			glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.87f, -0.5f);
			glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(-0.87f, -0.5f);
			glEnd();
			glPopMatrix();

			theta += 0.05f;

			mp_context->SwapBuffer();
		}

		void RenderSystem::Stop() {

		}

	}
}