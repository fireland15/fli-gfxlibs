#include <iostream>
#include <functional>

#define _WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <fli-core\clock.hpp>
#include <fli-render\window.hpp>
#include <fli-render\opengl_context.hpp>
#include <fli-render\simple_render_system.hpp>
#include <fli-render\opengl_error.hpp>
#include <fli-utility\config_reader.hpp>
#include <fli-utility\logger_base.hpp>
#include <fli-utility\logger_simple.hpp>
#include <glm\glm.hpp>

void Render() {
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.87f, -0.5f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(-0.87f, -0.5f);
	glEnd();
	glPopMatrix();
}

int main() {
	std::cout.sync_with_stdio(false);
	HINSTANCE hInstance = GetModuleHandle(0);
	gfx::render::Window w(hInstance, "fli-app-1", glm::uvec2(100, 100), glm::uvec2(300, 300));

	gfx::render::OpenGlContext* c = w.GetOpenGlContext();

	logging::SimpleLogger l(std::cout, logging::LogLvl::inf);

	gfx::render::SimpleRenderSystem r(c);
	r.SetLogger(&l);
	//r.Setup(*((gfx::core::Scene*)(nullptr)));
	r.Initialize();

	gfx::core::Clock clock;
	gfx::core::Clock::Timepoint t = clock.Now();
	gfx::core::Clock::Duration d = clock.TimeFromEpoch(t);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	int i = 0;
	gfx::core::Scene scene;

	while (i++, !w.ShouldClose()) {
		w.ProcessMessages();
		try {
			r.Update(scene, 30.0);
			r.Render(scene, 30.0);

			d = clock.TimeFromNow(t);
			if (i % 1000 == 0) {
				float s = d.Seconds();
				std::cout << 1000 / s << std::endl;
			}
			t = clock.Now();
		}
		catch (std::exception) {
			break;
		}
	}

	r.Stop();

}