#include "simple_render_system.hpp"

namespace gfx {
	namespace render {

		SimpleRenderSystem::SimpleRenderSystem(OpenGlContext* context)
			: m_pContext(context)
			, SystemBase() {
			m_systemName = "render";
		}

		void 
		SimpleRenderSystem::SetConfig(Configuration* pConfig) {
			m_pConfig = pConfig;
		}

		void 
		SimpleRenderSystem::Setup(core::Scene& scene) {
			if (!scene.IsComponentInScene<core::TransformComponent>()) {
				scene.AddComponent<core::TransformComponent>();
			}

			Log(std::string("setup complete"), logging::LogLvl::inf);
		}

		void 
		SimpleRenderSystem::Initialize() {
			std::stringstream ss;
			ss << "OpenGL Version: " << m_pContext->MajorVersion() << "." << m_pContext->MinorVersion();
			std::string version = ss.str();
			Log("Initialized with OpenGL", version, logging::LogLvl::inf);

			Log(std::string("initialization complete"), logging::LogLvl::inf);
		}

		void 
		SimpleRenderSystem::Update(core::Scene& scene, double time) {

		}

		void 
		SimpleRenderSystem::Render(core::Scene& scene, double time) {
			if (m_shouldRender) {
				glClear(GL_COLOR_BUFFER_BIT);
				glPushMatrix();
				glRotatef(theta, 0.0f, 0.0f, 1.0f);
				glBegin(GL_TRIANGLES);
				glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(0.0f, 1.0f);
				glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.87f, -0.5f);
				glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(-0.87f, -0.5f);
				glEnd();
				glPopMatrix();

				theta += 0.005f;

				m_pContext->SwapBuffer();
			}
		}

		void 
		SimpleRenderSystem::Stop() {
			Log(std::string("stopping"), logging::LogLvl::inf);
		}

		void
		SimpleRenderSystem::Configure() {

		}

	}
}